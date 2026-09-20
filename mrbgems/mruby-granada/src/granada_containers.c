/*
 * Groups, tree, chart, popup, combo, contextual, tooltip, menu.
 * begin/end pairs take a block and always close via MRB_ENSURE when open.
 */
#include "granada.h"
#include <string.h>

static mrb_value
ctx_group_begin(mrb_state *mrb, mrb_value self)
{
  char *title;
  mrb_int flags = 0;
  mrb_value blk = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  mrb_get_args(mrb, "z|i&", &title, &flags, &blk);
  return granada_open_block(mrb, ctx, nk_group_begin(ctx, title, (nk_flags)flags), nk_group_end, blk);
}

static mrb_value
ctx_group_begin_titled(mrb_state *mrb, mrb_value self)
{
  char *name, *title;
  mrb_int flags = 0;
  mrb_value blk = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  mrb_get_args(mrb, "zz|i&", &name, &title, &flags, &blk);
  return granada_open_block(mrb, ctx, nk_group_begin_titled(ctx, name, title, (nk_flags)flags), nk_group_end, blk);
}

static mrb_value ctx_group_end(mrb_state *mrb, mrb_value self)
{ nk_group_end(granada_context_ptr(mrb, self)); return self; }

static mrb_value
ctx_group_get_scroll(mrb_state *mrb, mrb_value self)
{
  char *id;
  nk_uint x = 0, y = 0;
  mrb_value a;
  mrb_get_args(mrb, "z", &id);
  nk_group_get_scroll(granada_context_ptr(mrb, self), id, &x, &y);
  a = mrb_ary_new_capa(mrb, 2);
  mrb_ary_push(mrb, a, mrb_int_value(mrb, (mrb_int)x));
  mrb_ary_push(mrb, a, mrb_int_value(mrb, (mrb_int)y));
  return a;
}

static mrb_value
ctx_group_set_scroll(mrb_state *mrb, mrb_value self)
{
  char *id;
  mrb_int x, y;
  mrb_get_args(mrb, "zii", &id, &x, &y);
  nk_group_set_scroll(granada_context_ptr(mrb, self), id, (nk_uint)x, (nk_uint)y);
  return self;
}

static mrb_value
ctx_tree_push_hashed(mrb_state *mrb, mrb_value self)
{
  mrb_int type, state = NK_MAXIMIZED;
  char *title, *hash;
  mrb_int seed = 0;
  mrb_value blk = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  mrb_get_args(mrb, "izz|ii&", &type, &title, &hash, &state, &seed, &blk);
  return granada_open_block(mrb, ctx,
    nk_tree_push_hashed(ctx, (enum nk_tree_type)type, title, (enum nk_collapse_states)state, hash, (int)nk_strlen(hash), (int)seed),
    nk_tree_pop, blk);
}

static mrb_value
ctx_tree_image_push_hashed(mrb_state *mrb, mrb_value self)
{
  mrb_int type, state = NK_MAXIMIZED, seed = 0;
  mrb_value img;
  char *title, *hash;
  mrb_value blk = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  mrb_get_args(mrb, "iozz|ii&", &type, &img, &title, &hash, &state, &seed, &blk);
  return granada_open_block(mrb, ctx,
    nk_tree_image_push_hashed(ctx, (enum nk_tree_type)type, granada_image_get(mrb, img), title, (enum nk_collapse_states)state, hash, (int)nk_strlen(hash), (int)seed),
    nk_tree_pop, blk);
}

static mrb_value ctx_tree_pop(mrb_state *mrb, mrb_value self)
{ nk_tree_pop(granada_context_ptr(mrb, self)); return self; }

static mrb_value
ctx_tree_state_push(mrb_state *mrb, mrb_value self)
{
  mrb_int type, state;
  char *title;
  mrb_value blk = mrb_nil_value();
  enum nk_collapse_states st;
  nk_bool open;
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  mrb_value out;
  mrb_get_args(mrb, "izi&", &type, &title, &state, &blk);
  st = (enum nk_collapse_states)state;
  open = nk_tree_state_push(ctx, (enum nk_tree_type)type, title, &st);
  if (!mrb_nil_p(blk) && open) {
    mrb_value result;
    mrb_value block = blk;
    MRB_ENSURE(mrb, result, granada_yield, &block) {
      nk_tree_state_pop(ctx);
    }
    (void)result;
  }
  out = mrb_ary_new_capa(mrb, 2);
  mrb_ary_push(mrb, out, mrb_bool_value(open));
  mrb_ary_push(mrb, out, mrb_int_value(mrb, (mrb_int)st));
  return out;
}

static mrb_value ctx_tree_state_pop(mrb_state *mrb, mrb_value self)
{ nk_tree_state_pop(granada_context_ptr(mrb, self)); return self; }

static mrb_value
ctx_chart_begin(mrb_state *mrb, mrb_value self)
{
  mrb_int type, num;
  mrb_float min, max;
  mrb_value blk = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  mrb_get_args(mrb, "iiff&", &type, &num, &min, &max, &blk);
  return granada_open_block(mrb, ctx, nk_chart_begin(ctx, (enum nk_chart_type)type, (int)num, (float)min, (float)max), nk_chart_end, blk);
}

static mrb_value
ctx_chart_push(mrb_state *mrb, mrb_value self)
{
  mrb_float v;
  mrb_get_args(mrb, "f", &v);
  return mrb_int_value(mrb, (mrb_int)nk_chart_push(granada_context_ptr(mrb, self), (float)v));
}

static mrb_value ctx_chart_end(mrb_state *mrb, mrb_value self)
{ nk_chart_end(granada_context_ptr(mrb, self)); return self; }

static mrb_value
ctx_plot(mrb_state *mrb, mrb_value self)
{
  mrb_int type, i, n, offset = 0;
  mrb_value values;
  float *buf;
  mrb_get_args(mrb, "iA|i", &type, &values, &offset);
  n = RARRAY_LEN(values);
  if (n <= 0) mrb_raise(mrb, E_ARGUMENT_ERROR, "plot needs values");
  buf = granada_ctx_floats(mrb, self, (int)n);
  for (i = 0; i < n; i++) buf[i] = (float)mrb_as_float(mrb, mrb_ary_entry(values, i));
  nk_plot(granada_context_ptr(mrb, self), (enum nk_chart_type)type, buf, (int)n, (int)offset);
  return self;
}

static mrb_value
ctx_popup_begin(mrb_state *mrb, mrb_value self)
{
  mrb_int type, flags = 0;
  char *title;
  mrb_value bounds, blk = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  mrb_get_args(mrb, "izo|i&", &type, &title, &bounds, &flags, &blk);
  return granada_open_block(mrb, ctx,
    nk_popup_begin(ctx, (enum nk_popup_type)type, title, (nk_flags)flags, granada_rect_get(mrb, bounds)),
    nk_popup_end, blk);
}

static mrb_value ctx_popup_close(mrb_state *mrb, mrb_value self)
{ nk_popup_close(granada_context_ptr(mrb, self)); return self; }
static mrb_value ctx_popup_end(mrb_state *mrb, mrb_value self)
{ nk_popup_end(granada_context_ptr(mrb, self)); return self; }

static mrb_value
ctx_combo(mrb_state *mrb, mrb_value self)
{
  mrb_value items, size = mrb_nil_value();
  mrb_int selected, item_height, i, n;
  const char **citems;
  int sel;
  struct nk_vec2 sz;
  mrb_get_args(mrb, "Aii|o", &items, &selected, &item_height, &size);
  n = RARRAY_LEN(items);
  if (n <= 0) mrb_raise(mrb, E_ARGUMENT_ERROR, "combo needs items");
  sz = mrb_nil_p(size) ? nk_vec2(200, 200) : granada_vec2_get(mrb, size);
  citems = (const char **)mrb_malloc(mrb, sizeof(char *) * (size_t)n);
  for (i = 0; i < n; i++) citems[i] = mrb_string_cstr(mrb, mrb_ary_entry(items, i));
  sel = nk_combo(granada_context_ptr(mrb, self), citems, (int)n, (int)selected, (int)item_height, sz);
  mrb_free(mrb, citems);
  return mrb_int_value(mrb, sel);
}

static mrb_value
ctx_combo_begin_label(mrb_state *mrb, mrb_value self)
{
  char *selected;
  mrb_value size, blk = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  mrb_get_args(mrb, "zo&", &selected, &size, &blk);
  return granada_open_block(mrb, ctx, nk_combo_begin_label(ctx, selected, granada_vec2_get(mrb, size)), nk_combo_end, blk);
}

static mrb_value
ctx_combo_item_label(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_int align = NK_TEXT_LEFT;
  mrb_get_args(mrb, "z|i", &text, &align);
  return mrb_bool_value(nk_combo_item_label(granada_context_ptr(mrb, self), text, (nk_flags)align));
}

static mrb_value ctx_combo_close(mrb_state *mrb, mrb_value self)
{ nk_combo_close(granada_context_ptr(mrb, self)); return self; }
static mrb_value ctx_combo_end(mrb_state *mrb, mrb_value self)
{ nk_combo_end(granada_context_ptr(mrb, self)); return self; }

static mrb_value
ctx_contextual_begin(mrb_state *mrb, mrb_value self)
{
  mrb_int flags = 0;
  mrb_value size, bounds, blk = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  mrb_get_args(mrb, "ioo|&", &flags, &size, &bounds, &blk);
  return granada_open_block(mrb, ctx,
    nk_contextual_begin(ctx, (nk_flags)flags, granada_vec2_get(mrb, size), granada_rect_get(mrb, bounds)),
    nk_contextual_end, blk);
}

static mrb_value
ctx_contextual_item_label(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_int align = NK_TEXT_LEFT;
  mrb_get_args(mrb, "z|i", &text, &align);
  return mrb_bool_value(nk_contextual_item_label(granada_context_ptr(mrb, self), text, (nk_flags)align));
}

static mrb_value ctx_contextual_close(mrb_state *mrb, mrb_value self)
{ nk_contextual_close(granada_context_ptr(mrb, self)); return self; }
static mrb_value ctx_contextual_end(mrb_state *mrb, mrb_value self)
{ nk_contextual_end(granada_context_ptr(mrb, self)); return self; }

static mrb_value
ctx_tooltip(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_get_args(mrb, "z", &text);
  nk_tooltip(granada_context_ptr(mrb, self), text);
  return self;
}

static mrb_value
ctx_tooltip_begin(mrb_state *mrb, mrb_value self)
{
  mrb_float width;
  mrb_value blk = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  mrb_get_args(mrb, "f&", &width, &blk);
  return granada_open_block(mrb, ctx, nk_tooltip_begin(ctx, (float)width), nk_tooltip_end, blk);
}

static mrb_value ctx_tooltip_end(mrb_state *mrb, mrb_value self)
{ nk_tooltip_end(granada_context_ptr(mrb, self)); return self; }

static mrb_value
ctx_menubar_begin(mrb_state *mrb, mrb_value self)
{
  mrb_value blk = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  mrb_get_args(mrb, "&", &blk);
  nk_menubar_begin(ctx);
  if (mrb_nil_p(blk)) return self;
  {
    mrb_value result;
    mrb_value block = blk;
    MRB_ENSURE(mrb, result, granada_yield, &block) {
      nk_menubar_end(ctx);
    }
    return result;
  }
}

static mrb_value ctx_menubar_end(mrb_state *mrb, mrb_value self)
{ nk_menubar_end(granada_context_ptr(mrb, self)); return self; }

static mrb_value
ctx_menu_begin_label(mrb_state *mrb, mrb_value self)
{
  char *title;
  mrb_int align;
  mrb_value size, blk = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  mrb_get_args(mrb, "zio&", &title, &align, &size, &blk);
  return granada_open_block(mrb, ctx, nk_menu_begin_label(ctx, title, (nk_flags)align, granada_vec2_get(mrb, size)), nk_menu_end, blk);
}

static mrb_value
ctx_menu_item_label(mrb_state *mrb, mrb_value self)
{
  char *title;
  mrb_int align = NK_TEXT_LEFT;
  mrb_value blk = mrb_nil_value();
  nk_bool clicked;
  mrb_get_args(mrb, "z|i&", &title, &align, &blk);
  clicked = nk_menu_item_label(granada_context_ptr(mrb, self), title, (nk_flags)align);
  if (!mrb_nil_p(blk) && clicked) return mrb_yield_argv(mrb, blk, 0, NULL);
  return mrb_bool_value(clicked);
}

static mrb_value ctx_menu_close(mrb_state *mrb, mrb_value self)
{ nk_menu_close(granada_context_ptr(mrb, self)); return self; }
static mrb_value ctx_menu_end(mrb_state *mrb, mrb_value self)
{ nk_menu_end(granada_context_ptr(mrb, self)); return self; }

typedef struct {
  mrb_value blk;
  struct nk_list_view *view;
} list_run;

static mrb_value
list_run_body(mrb_state *mrb, void *data)
{
  list_run *r = (list_run *)data;
  int i;
  for (i = r->view->begin; i < r->view->end; i++) {
    mrb_value idx = mrb_int_value(mrb, i);
    mrb_yield_argv(mrb, r->blk, 1, &idx);
  }
  return mrb_true_value();
}

static mrb_value
ctx_list_view(mrb_state *mrb, mrb_value self)
{
  char *id;
  mrb_int row_h, count, flags = 0;
  mrb_value blk = mrb_nil_value();
  struct nk_list_view view;
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  nk_bool open;

  mrb_get_args(mrb, "zii|i&", &id, &row_h, &count, &flags, &blk);
  memset(&view, 0, sizeof(view));
  open = nk_list_view_begin(ctx, &view, id, (nk_flags)flags, (int)row_h, (int)count);
  if (mrb_nil_p(blk)) {
    mrb_value a = mrb_ary_new_capa(mrb, 4);
    mrb_ary_push(mrb, a, mrb_bool_value(open));
    mrb_ary_push(mrb, a, mrb_int_value(mrb, view.begin));
    mrb_ary_push(mrb, a, mrb_int_value(mrb, view.end));
    mrb_ary_push(mrb, a, mrb_int_value(mrb, view.count));
    if (open) nk_list_view_end(&view);
    return a;
  }
  if (!open) {
    return mrb_false_value();
  }
  {
    list_run r;
    mrb_value result;
    r.blk = blk;
    r.view = &view;
    MRB_ENSURE(mrb, result, list_run_body, &r) {
      nk_list_view_end(&view);
    }
    return result;
  }
}

void
mrb_granada_containers_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native)
{
  static const char *fwds[] = {
    "group_begin", "group", "group_begin_titled", "group_end",
    "group_get_scroll", "group_set_scroll",
    "tree_push_hashed", "tree_push", "tree_image_push_hashed", "tree_pop",
    "tree_state_push", "tree_state_pop",
    "chart_begin", "chart_push", "chart_end", "plot",
    "popup_begin", "popup_close", "popup_end",
    "combo", "combo_begin_label", "combo_item_label", "combo_close", "combo_end",
    "contextual_begin", "contextual_item_label", "contextual_close", "contextual_end",
    "tooltip", "tooltip_begin", "tooltip_end",
    "menubar_begin", "menubar_end", "menu_begin_label", "menu_item_label",
    "menu_close", "menu_end", "list_view",
    0
  };

  mrb_define_method(mrb, ctx, "group_begin", ctx_group_begin, MRB_ARGS_ARG(1, 1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "group", ctx_group_begin, MRB_ARGS_ARG(1, 1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "group_begin_titled", ctx_group_begin_titled, MRB_ARGS_ARG(2, 1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "group_end", ctx_group_end, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "group_get_scroll", ctx_group_get_scroll, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "group_set_scroll", ctx_group_set_scroll, MRB_ARGS_REQ(3));

  mrb_define_method(mrb, ctx, "tree_push_hashed", ctx_tree_push_hashed, MRB_ARGS_ARG(3, 2) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "tree_push", ctx_tree_push_hashed, MRB_ARGS_ARG(3, 2) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "tree_image_push_hashed", ctx_tree_image_push_hashed, MRB_ARGS_ARG(4, 2) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "tree_pop", ctx_tree_pop, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "tree_state_push", ctx_tree_state_push, MRB_ARGS_REQ(3) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "tree_state_pop", ctx_tree_state_pop, MRB_ARGS_NONE());

  mrb_define_method(mrb, ctx, "chart_begin", ctx_chart_begin, MRB_ARGS_REQ(4) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "chart_push", ctx_chart_push, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "chart_end", ctx_chart_end, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "plot", ctx_plot, MRB_ARGS_ARG(2, 1));

  mrb_define_method(mrb, ctx, "popup_begin", ctx_popup_begin, MRB_ARGS_ARG(3, 1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "popup_close", ctx_popup_close, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "popup_end", ctx_popup_end, MRB_ARGS_NONE());

  mrb_define_method(mrb, ctx, "combo", ctx_combo, MRB_ARGS_ARG(3, 1));
  mrb_define_method(mrb, ctx, "combo_begin_label", ctx_combo_begin_label, MRB_ARGS_REQ(2) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "combo_item_label", ctx_combo_item_label, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, ctx, "combo_close", ctx_combo_close, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "combo_end", ctx_combo_end, MRB_ARGS_NONE());

  mrb_define_method(mrb, ctx, "contextual_begin", ctx_contextual_begin, MRB_ARGS_REQ(3) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "contextual_item_label", ctx_contextual_item_label, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, ctx, "contextual_close", ctx_contextual_close, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "contextual_end", ctx_contextual_end, MRB_ARGS_NONE());

  mrb_define_method(mrb, ctx, "tooltip", ctx_tooltip, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "tooltip_begin", ctx_tooltip_begin, MRB_ARGS_REQ(1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "tooltip_end", ctx_tooltip_end, MRB_ARGS_NONE());

  mrb_define_method(mrb, ctx, "menubar_begin", ctx_menubar_begin, MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "menubar_end", ctx_menubar_end, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "menu_begin_label", ctx_menu_begin_label, MRB_ARGS_REQ(3) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "menu_item_label", ctx_menu_item_label, MRB_ARGS_ARG(1, 1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "menu_close", ctx_menu_close, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "menu_end", ctx_menu_end, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "list_view", ctx_list_view, MRB_ARGS_ARG(3, 1) | MRB_ARGS_BLOCK());

  granada_define_native_fwds(mrb, native, fwds);
}
