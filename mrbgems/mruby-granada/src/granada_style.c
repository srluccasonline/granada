/*
 * Style table, cursor show/hide, color-by-name.
 * Pointer push/pop into nk_style fields stays unbound (too low-level for Native).
 */
#include "granada.h"

#include <string.h>

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
    0
  };
  mrb_define_method(mrb, ctx, "style_from_table", ctx_style_from_table, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "style_show_cursor", ctx_style_show_cursor, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "style_hide_cursor", ctx_style_hide_cursor, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "style_set_cursor", ctx_style_set_cursor, MRB_ARGS_REQ(1));
  granada_define_native_fwds(mrb, native, fwds);
  mrb_define_module_function(mrb, native, "style_get_color_by_name", native_style_get_color_by_name, MRB_ARGS_REQ(1));
}
