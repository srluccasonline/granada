/*
 * Window: nk_begin / nk_end with MRB_ENSURE so a Ruby raise still closes the window.
 */
#include "granada.h"

static mrb_value
do_begin(mrb_state *mrb, mrb_value self, const char *name, const char *title,
         struct nk_rect bounds, nk_flags flags, mrb_value blk)
{
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  nk_bool open;

  if (title) {
    open = nk_begin_titled(ctx, name, title, bounds, flags);
  } else {
    open = nk_begin(ctx, name, bounds, flags);
  }

  if (mrb_nil_p(blk)) {
    return mrb_bool_value(open);
  }

  if (open) {
    mrb_value result;
    mrb_value block = blk;
    MRB_ENSURE(mrb, result, granada_yield, &block) {
      nk_end(ctx);
    }
    return result;
  }

  nk_end(ctx);
  return mrb_false_value();
}

static mrb_value
ctx_begin(mrb_state *mrb, mrb_value self)
{
  char *title;
  mrb_value rect;
  mrb_int flags = 0;
  mrb_value blk = mrb_nil_value();

  mrb_get_args(mrb, "zo|i&", &title, &rect, &flags, &blk);
  return do_begin(mrb, self, title, NULL, granada_rect_get(mrb, rect), (nk_flags)flags, blk);
}

static mrb_value
ctx_begin_titled(mrb_state *mrb, mrb_value self)
{
  char *name, *title;
  mrb_value rect;
  mrb_int flags = 0;
  mrb_value blk = mrb_nil_value();

  mrb_get_args(mrb, "zzo|i&", &name, &title, &rect, &flags, &blk);
  return do_begin(mrb, self, name, title, granada_rect_get(mrb, rect), (nk_flags)flags, blk);
}

static mrb_value
ctx_end(mrb_state *mrb, mrb_value self)
{
  nk_end(granada_context_ptr(mrb, self));
  return self;
}

static mrb_value
ctx_window_bounds(mrb_state *mrb, mrb_value self)
{
  return granada_rect_wrap(mrb, nk_window_get_bounds(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_window_position(mrb_state *mrb, mrb_value self)
{
  return granada_vec2_wrap(mrb, nk_window_get_position(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_window_size(mrb_state *mrb, mrb_value self)
{
  return granada_vec2_wrap(mrb, nk_window_get_size(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_window_width(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, nk_window_get_width(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_window_height(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, nk_window_get_height(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_content_region(mrb_state *mrb, mrb_value self)
{
  return granada_rect_wrap(mrb, nk_window_get_content_region(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_content_region_min(mrb_state *mrb, mrb_value self)
{
  return granada_vec2_wrap(mrb, nk_window_get_content_region_min(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_content_region_max(mrb_state *mrb, mrb_value self)
{
  return granada_vec2_wrap(mrb, nk_window_get_content_region_max(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_content_region_size(mrb_state *mrb, mrb_value self)
{
  return granada_vec2_wrap(mrb, nk_window_get_content_region_size(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_window_scroll(mrb_state *mrb, mrb_value self)
{
  nk_uint x = 0, y = 0;
  mrb_value a;
  nk_window_get_scroll(granada_context_ptr(mrb, self), &x, &y);
  a = mrb_ary_new_capa(mrb, 2);
  mrb_ary_push(mrb, a, mrb_int_value(mrb, (mrb_int)x));
  mrb_ary_push(mrb, a, mrb_int_value(mrb, (mrb_int)y));
  return a;
}

static mrb_value
ctx_set_window_scroll(mrb_state *mrb, mrb_value self)
{
  mrb_int x, y;
  mrb_get_args(mrb, "ii", &x, &y);
  nk_window_set_scroll(granada_context_ptr(mrb, self), (nk_uint)x, (nk_uint)y);
  return self;
}

static mrb_value
ctx_window_has_focus(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(nk_window_has_focus(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_window_hovered(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(nk_window_is_hovered(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_window_collapsed(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_get_args(mrb, "z", &name);
  return mrb_bool_value(nk_window_is_collapsed(granada_context_ptr(mrb, self), name));
}

static mrb_value
ctx_window_closed(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_get_args(mrb, "z", &name);
  return mrb_bool_value(nk_window_is_closed(granada_context_ptr(mrb, self), name));
}

static mrb_value
ctx_window_hidden(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_get_args(mrb, "z", &name);
  return mrb_bool_value(nk_window_is_hidden(granada_context_ptr(mrb, self), name));
}

static mrb_value
ctx_window_active(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_get_args(mrb, "z", &name);
  return mrb_bool_value(nk_window_is_active(granada_context_ptr(mrb, self), name));
}

static mrb_value
ctx_any_window_hovered(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(nk_window_is_any_hovered(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_item_active(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(nk_item_is_any_active(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_set_window_bounds(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_value rect;
  mrb_get_args(mrb, "zo", &name, &rect);
  nk_window_set_bounds(granada_context_ptr(mrb, self), name, granada_rect_get(mrb, rect));
  return self;
}

static mrb_value
ctx_set_window_position(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_value pos;
  mrb_get_args(mrb, "zo", &name, &pos);
  nk_window_set_position(granada_context_ptr(mrb, self), name, granada_vec2_get(mrb, pos));
  return self;
}

static mrb_value
ctx_set_window_size(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_value size;
  mrb_get_args(mrb, "zo", &name, &size);
  nk_window_set_size(granada_context_ptr(mrb, self), name, granada_vec2_get(mrb, size));
  return self;
}

static mrb_value
ctx_set_window_focus(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_get_args(mrb, "z", &name);
  nk_window_set_focus(granada_context_ptr(mrb, self), name);
  return self;
}

static mrb_value
ctx_close_window(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_get_args(mrb, "z", &name);
  nk_window_close(granada_context_ptr(mrb, self), name);
  return self;
}

static mrb_value
ctx_collapse_window(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_int state;
  mrb_get_args(mrb, "zi", &name, &state);
  nk_window_collapse(granada_context_ptr(mrb, self), name, (enum nk_collapse_states)state);
  return self;
}

static mrb_value
ctx_show_window(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_int state;
  mrb_get_args(mrb, "zi", &name, &state);
  nk_window_show(granada_context_ptr(mrb, self), name, (enum nk_show_states)state);
  return self;
}

static mrb_value
ctx_window_exists(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_get_args(mrb, "z", &name);
  return mrb_bool_value(nk_window_find(granada_context_ptr(mrb, self), name) != NULL);
}

static mrb_value
ctx_rule_horizontal(mrb_state *mrb, mrb_value self)
{
  mrb_value color;
  mrb_bool rounding = FALSE;
  mrb_get_args(mrb, "o|b", &color, &rounding);
  nk_rule_horizontal(granada_context_ptr(mrb, self), granada_color_get(mrb, color), rounding ? nk_true : nk_false);
  return self;
}

void
mrb_granada_window_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native)
{
  mrb_define_method(mrb, ctx, "begin", ctx_begin, MRB_ARGS_ARG(2, 1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "window", ctx_begin, MRB_ARGS_ARG(2, 1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "begin_titled", ctx_begin_titled, MRB_ARGS_ARG(3, 1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "end", ctx_end, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "end_window", ctx_end, MRB_ARGS_NONE());

  mrb_define_method(mrb, ctx, "window_bounds", ctx_window_bounds, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "window_position", ctx_window_position, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "window_size", ctx_window_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "window_width", ctx_window_width, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "window_height", ctx_window_height, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "content_region", ctx_content_region, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "content_region_min", ctx_content_region_min, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "content_region_max", ctx_content_region_max, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "content_region_size", ctx_content_region_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "window_scroll", ctx_window_scroll, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "set_window_scroll", ctx_set_window_scroll, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "window_has_focus?", ctx_window_has_focus, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "window_hovered?", ctx_window_hovered, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "window_collapsed?", ctx_window_collapsed, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "window_closed?", ctx_window_closed, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "window_hidden?", ctx_window_hidden, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "window_active?", ctx_window_active, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "any_window_hovered?", ctx_any_window_hovered, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "item_active?", ctx_item_active, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "set_window_bounds", ctx_set_window_bounds, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "set_window_position", ctx_set_window_position, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "set_window_size", ctx_set_window_size, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "set_window_focus", ctx_set_window_focus, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "close_window", ctx_close_window, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "collapse_window", ctx_collapse_window, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "show_window", ctx_show_window, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "window_exists?", ctx_window_exists, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "rule_horizontal", ctx_rule_horizontal, MRB_ARGS_ARG(1, 1));

  granada_define_native_fwd(mrb, native, "begin", MRB_ARGS_ARG(3, 1) | MRB_ARGS_BLOCK());
  granada_define_native_fwd(mrb, native, "window", MRB_ARGS_ARG(3, 1) | MRB_ARGS_BLOCK());
  granada_define_native_fwd(mrb, native, "begin_titled", MRB_ARGS_ARG(4, 1) | MRB_ARGS_BLOCK());
  granada_define_native_fwd(mrb, native, "end", MRB_ARGS_REQ(1));
  granada_define_native_fwd(mrb, native, "end_window", MRB_ARGS_REQ(1));
  granada_define_native_fwd(mrb, native, "window_bounds", MRB_ARGS_REQ(1));
  granada_define_native_fwd(mrb, native, "window_position", MRB_ARGS_REQ(1));
  granada_define_native_fwd(mrb, native, "window_size", MRB_ARGS_REQ(1));
  granada_define_native_fwd(mrb, native, "window_width", MRB_ARGS_REQ(1));
  granada_define_native_fwd(mrb, native, "window_height", MRB_ARGS_REQ(1));
  granada_define_native_fwd(mrb, native, "content_region", MRB_ARGS_REQ(1));
}
