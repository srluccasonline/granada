/*
 * Style table, cursor, and named push/pop (button.rounding, window.padding, …).
 */
#include "granada.h"

#include <string.h>

enum slot_kind { SLOT_NONE, SLOT_COLOR, SLOT_FLOAT, SLOT_VEC2 };

static enum slot_kind
style_slot(struct nk_context *ctx, const char *name, struct nk_color **c, float **f, struct nk_vec2 **v)
{
  struct nk_style *s = &ctx->style;
  *c = 0; *f = 0; *v = 0;
  if (strcmp(name, "text.color") == 0) { *c = &s->text.color; return SLOT_COLOR; }
  if (strcmp(name, "text.padding") == 0) { *v = &s->text.padding; return SLOT_VEC2; }
  if (strcmp(name, "button.rounding") == 0) { *f = &s->button.rounding; return SLOT_FLOAT; }
  if (strcmp(name, "button.border") == 0) { *f = &s->button.border; return SLOT_FLOAT; }
  if (strcmp(name, "button.padding") == 0) { *v = &s->button.padding; return SLOT_VEC2; }
  if (strcmp(name, "button.text_normal") == 0) { *c = &s->button.text_normal; return SLOT_COLOR; }
  if (strcmp(name, "button.text_hover") == 0) { *c = &s->button.text_hover; return SLOT_COLOR; }
  if (strcmp(name, "button.text_active") == 0) { *c = &s->button.text_active; return SLOT_COLOR; }
  if (strcmp(name, "button.border_color") == 0) { *c = &s->button.border_color; return SLOT_COLOR; }
  if (strcmp(name, "window.rounding") == 0) { *f = &s->window.rounding; return SLOT_FLOAT; }
  if (strcmp(name, "window.border") == 0) { *f = &s->window.border; return SLOT_FLOAT; }
  if (strcmp(name, "window.padding") == 0) { *v = &s->window.padding; return SLOT_VEC2; }
  if (strcmp(name, "window.spacing") == 0) { *v = &s->window.spacing; return SLOT_VEC2; }
  if (strcmp(name, "window.background") == 0) { *c = &s->window.background; return SLOT_COLOR; }
  if (strcmp(name, "window.border_color") == 0) { *c = &s->window.border_color; return SLOT_COLOR; }
  if (strcmp(name, "edit.padding") == 0) { *v = &s->edit.padding; return SLOT_VEC2; }
  if (strcmp(name, "slider.padding") == 0) { *v = &s->slider.padding; return SLOT_VEC2; }
  if (strcmp(name, "slider.rounding") == 0) { *f = &s->slider.rounding; return SLOT_FLOAT; }
  if (strcmp(name, "checkbox.padding") == 0) { *v = &s->checkbox.padding; return SLOT_VEC2; }
  if (strcmp(name, "option.padding") == 0) { *v = &s->option.padding; return SLOT_VEC2; }
  return SLOT_NONE;
}

static const char *
slot_name(mrb_state *mrb, mrb_value name)
{
  if (mrb_symbol_p(name)) return mrb_sym_name(mrb, mrb_symbol(name));
  return mrb_string_cstr(mrb, name);
}

static mrb_value
ctx_style_from_table(mrb_state *mrb, mrb_value self)
{
  mrb_value table;
  struct nk_color colors[NK_COLOR_COUNT];
  mrb_int i, n;
  mrb_get_args(mrb, "A", &table);
  n = RARRAY_LEN(table);
  if (n == 0) {
    nk_style_from_table(granada_context_ptr(mrb, self), 0);
    return self;
  }
  if (n != NK_COLOR_COUNT) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "style_from_table needs %d colors (got %d)",
               (mrb_int)NK_COLOR_COUNT, n);
  }
  for (i = 0; i < n; i++) {
    colors[i] = granada_color_get(mrb, mrb_ary_entry(table, i));
  }
  nk_style_from_table(granada_context_ptr(mrb, self), colors);
  return self;
}

static mrb_value ctx_style_show_cursor(mrb_state *mrb, mrb_value self)
{ nk_style_show_cursor(granada_context_ptr(mrb, self)); return self; }
static mrb_value ctx_style_hide_cursor(mrb_state *mrb, mrb_value self)
{ nk_style_hide_cursor(granada_context_ptr(mrb, self)); return self; }

static mrb_value
ctx_style_set_cursor(mrb_state *mrb, mrb_value self)
{
  mrb_int c;
  mrb_get_args(mrb, "i", &c);
  return mrb_bool_value(nk_style_set_cursor(granada_context_ptr(mrb, self), (enum nk_style_cursor)c));
}

typedef struct {
  struct nk_context *ctx;
  enum slot_kind kind;
  mrb_value blk;
} style_push_run;

static mrb_value
style_push_body(mrb_state *mrb, void *data)
{
  return granada_yield(mrb, &((style_push_run *)data)->blk);
}

static mrb_value
ctx_style_push(mrb_state *mrb, mrb_value self)
{
  mrb_value name, val, blk = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  struct nk_color *c;
  float *f;
  struct nk_vec2 *v;
  enum slot_kind kind;
  const char *n;
  nk_bool ok = nk_false;

  mrb_get_args(mrb, "oo&", &name, &val, &blk);
  n = slot_name(mrb, name);
  kind = style_slot(ctx, n, &c, &f, &v);
  if (kind == SLOT_NONE) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "unknown style slot '%s'", n);
  }
  if (kind == SLOT_COLOR) ok = nk_style_push_color(ctx, c, granada_color_get(mrb, val));
  else if (kind == SLOT_FLOAT) ok = nk_style_push_float(ctx, f, (float)mrb_as_float(mrb, val));
  else ok = nk_style_push_vec2(ctx, v, granada_vec2_get(mrb, val));
  if (!ok) return mrb_false_value();
  if (mrb_nil_p(blk)) return mrb_true_value();
  {
    style_push_run r;
    mrb_value result;
    r.ctx = ctx;
    r.kind = kind;
    r.blk = blk;
    MRB_ENSURE(mrb, result, style_push_body, &r) {
      if (r.kind == SLOT_COLOR) nk_style_pop_color(r.ctx);
      else if (r.kind == SLOT_FLOAT) nk_style_pop_float(r.ctx);
      else nk_style_pop_vec2(r.ctx);
    }
    return result;
  }
}

static mrb_value ctx_style_pop_color(mrb_state *mrb, mrb_value self)
{ return mrb_bool_value(nk_style_pop_color(granada_context_ptr(mrb, self))); }
static mrb_value ctx_style_pop_float(mrb_state *mrb, mrb_value self)
{ return mrb_bool_value(nk_style_pop_float(granada_context_ptr(mrb, self))); }
static mrb_value ctx_style_pop_vec2(mrb_state *mrb, mrb_value self)
{ return mrb_bool_value(nk_style_pop_vec2(granada_context_ptr(mrb, self))); }

static mrb_value
native_style_get_color_by_name(mrb_state *mrb, mrb_value self)
{
  mrb_int c;
  const char *name;
  (void)self;
  mrb_get_args(mrb, "i", &c);
  name = nk_style_get_color_by_name((enum nk_style_colors)c);
  return name ? mrb_str_new_cstr(mrb, name) : mrb_nil_value();
}

void
mrb_granada_style_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native)
{
  static const char *fwds[] = {
    "style_from_table", "style_show_cursor", "style_hide_cursor", "style_set_cursor",
    "style_push", "style_pop_color", "style_pop_float", "style_pop_vec2",
    0
  };
  mrb_define_method(mrb, ctx, "style_from_table", ctx_style_from_table, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "style_show_cursor", ctx_style_show_cursor, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "style_hide_cursor", ctx_style_hide_cursor, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "style_set_cursor", ctx_style_set_cursor, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "style_push", ctx_style_push, MRB_ARGS_REQ(2) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "style_pop_color", ctx_style_pop_color, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "style_pop_float", ctx_style_pop_float, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "style_pop_vec2", ctx_style_pop_vec2, MRB_ARGS_NONE());
  granada_define_native_fwds(mrb, native, fwds);
  mrb_define_module_function(mrb, native, "style_get_color_by_name", native_style_get_color_by_name, MRB_ARGS_REQ(1));
}
