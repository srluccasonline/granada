/*
 * Layout rows / space / spacer. Ratio arrays live on granada_ctx because
 * nk_layout_row keeps the float* for the rest of the row.
 */
#include "granada.h"

static mrb_value
ctx_layout_row_dynamic(mrb_state *mrb, mrb_value self)
{
  mrb_float height;
  mrb_int cols = 1;
  mrb_get_args(mrb, "f|i", &height, &cols);
  if (cols <= 0) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "cols must be positive");
  }
  nk_layout_row_dynamic(granada_context_ptr(mrb, self), (float)height, (int)cols);
  return self;
}

static mrb_value
ctx_layout_row_static(mrb_state *mrb, mrb_value self)
{
  mrb_float height;
  mrb_int item_width, cols = 1;
  mrb_get_args(mrb, "fi|i", &height, &item_width, &cols);
  if (cols <= 0 || item_width <= 0) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "item_width and cols must be positive");
  }
  nk_layout_row_static(granada_context_ptr(mrb, self), (float)height, (int)item_width, (int)cols);
  return self;
}

static mrb_value
ctx_layout_row_begin(mrb_state *mrb, mrb_value self)
{
  mrb_int fmt, cols;
  mrb_float height;
  mrb_get_args(mrb, "ifi", &fmt, &height, &cols);
  nk_layout_row_begin(granada_context_ptr(mrb, self), (enum nk_layout_format)fmt, (float)height, (int)cols);
  return self;
}

static mrb_value
ctx_layout_row_push(mrb_state *mrb, mrb_value self)
{
  mrb_float value;
  mrb_get_args(mrb, "f", &value);
  nk_layout_row_push(granada_context_ptr(mrb, self), (float)value);
  return self;
}

static mrb_value
ctx_layout_row_end(mrb_state *mrb, mrb_value self)
{
  nk_layout_row_end(granada_context_ptr(mrb, self));
  return self;
}

static mrb_value
ctx_layout_row(mrb_state *mrb, mrb_value self)
{
  mrb_int fmt, i, n;
  mrb_float height;
  mrb_value ratios;
  float *buf;

  mrb_get_args(mrb, "ifo", &fmt, &height, &ratios);
  if (!mrb_array_p(ratios)) {
    mrb_raise(mrb, E_TYPE_ERROR, "ratios must be an Array");
  }
  n = RARRAY_LEN(ratios);
  if (n <= 0) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "ratios must not be empty");
  }
  buf = granada_ctx_floats(mrb, self, (int)n);
  for (i = 0; i < n; i++) {
    buf[i] = (float)mrb_as_float(mrb, mrb_ary_entry(ratios, i));
  }
  nk_layout_row(granada_context_ptr(mrb, self), (enum nk_layout_format)fmt, (float)height, (int)n, buf);
  return self;
}

static mrb_value
ctx_layout_row_template_begin(mrb_state *mrb, mrb_value self)
{
  mrb_float height;
  mrb_get_args(mrb, "f", &height);
  nk_layout_row_template_begin(granada_context_ptr(mrb, self), (float)height);
  return self;
}

static mrb_value
ctx_layout_row_template_push_dynamic(mrb_state *mrb, mrb_value self)
{
  nk_layout_row_template_push_dynamic(granada_context_ptr(mrb, self));
  return self;
}

static mrb_value
ctx_layout_row_template_push_variable(mrb_state *mrb, mrb_value self)
{
  mrb_float min_width;
  mrb_get_args(mrb, "f", &min_width);
  nk_layout_row_template_push_variable(granada_context_ptr(mrb, self), (float)min_width);
  return self;
}

static mrb_value
ctx_layout_row_template_push_static(mrb_state *mrb, mrb_value self)
{
  mrb_float width;
  mrb_get_args(mrb, "f", &width);
  nk_layout_row_template_push_static(granada_context_ptr(mrb, self), (float)width);
  return self;
}

static mrb_value
ctx_layout_row_template_end(mrb_state *mrb, mrb_value self)
{
  nk_layout_row_template_end(granada_context_ptr(mrb, self));
  return self;
}

static mrb_value
ctx_layout_space_begin(mrb_state *mrb, mrb_value self)
{
  mrb_int fmt, count;
  mrb_float height;
  mrb_get_args(mrb, "ifi", &fmt, &height, &count);
  nk_layout_space_begin(granada_context_ptr(mrb, self), (enum nk_layout_format)fmt, (float)height, (int)count);
  return self;
}

static mrb_value
ctx_layout_space_push(mrb_state *mrb, mrb_value self)
{
  mrb_value bounds;
  mrb_get_args(mrb, "o", &bounds);
  nk_layout_space_push(granada_context_ptr(mrb, self), granada_rect_get(mrb, bounds));
  return self;
}

static mrb_value
ctx_layout_space_end(mrb_state *mrb, mrb_value self)
{
  nk_layout_space_end(granada_context_ptr(mrb, self));
  return self;
}

static mrb_value
ctx_layout_space_bounds(mrb_state *mrb, mrb_value self)
{
  return granada_rect_wrap(mrb, nk_layout_space_bounds(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_layout_space_to_screen(mrb_state *mrb, mrb_value self)
{
  mrb_value v;
  mrb_get_args(mrb, "o", &v);
  return granada_vec2_wrap(mrb, nk_layout_space_to_screen(granada_context_ptr(mrb, self), granada_vec2_get(mrb, v)));
}

static mrb_value
ctx_layout_space_to_local(mrb_state *mrb, mrb_value self)
{
  mrb_value v;
  mrb_get_args(mrb, "o", &v);
  return granada_vec2_wrap(mrb, nk_layout_space_to_local(granada_context_ptr(mrb, self), granada_vec2_get(mrb, v)));
}

static mrb_value
ctx_layout_space_rect_to_screen(mrb_state *mrb, mrb_value self)
{
  mrb_value r;
  mrb_get_args(mrb, "o", &r);
  return granada_rect_wrap(mrb, nk_layout_space_rect_to_screen(granada_context_ptr(mrb, self), granada_rect_get(mrb, r)));
}

static mrb_value
ctx_layout_space_rect_to_local(mrb_state *mrb, mrb_value self)
{
  mrb_value r;
  mrb_get_args(mrb, "o", &r);
  return granada_rect_wrap(mrb, nk_layout_space_rect_to_local(granada_context_ptr(mrb, self), granada_rect_get(mrb, r)));
}

static mrb_value
ctx_spacer(mrb_state *mrb, mrb_value self)
{
  nk_spacer(granada_context_ptr(mrb, self));
  return self;
}

static mrb_value
ctx_spacing(mrb_state *mrb, mrb_value self)
{
  mrb_int cols;
  mrb_get_args(mrb, "i", &cols);
  nk_spacing(granada_context_ptr(mrb, self), (int)cols);
  return self;
}

static mrb_value
ctx_layout_widget_bounds(mrb_state *mrb, mrb_value self)
{
  return granada_rect_wrap(mrb, nk_layout_widget_bounds(granada_context_ptr(mrb, self)));
}

static mrb_value
ctx_layout_set_min_row_height(mrb_state *mrb, mrb_value self)
{
  mrb_float h;
  mrb_get_args(mrb, "f", &h);
  nk_layout_set_min_row_height(granada_context_ptr(mrb, self), (float)h);
  return self;
}

static mrb_value
ctx_layout_reset_min_row_height(mrb_state *mrb, mrb_value self)
{
  nk_layout_reset_min_row_height(granada_context_ptr(mrb, self));
  return self;
}

static mrb_value
ctx_layout_ratio_from_pixel(mrb_state *mrb, mrb_value self)
{
  mrb_float px;
  mrb_get_args(mrb, "f", &px);
  return mrb_float_value(mrb, nk_layout_ratio_from_pixel(granada_context_ptr(mrb, self), (float)px));
}

void
mrb_granada_layout_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native)
{
  mrb_define_method(mrb, ctx, "layout_row_dynamic", ctx_layout_row_dynamic, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, ctx, "layout_row_static", ctx_layout_row_static, MRB_ARGS_ARG(2, 1));
  mrb_define_method(mrb, ctx, "layout_row_begin", ctx_layout_row_begin, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, ctx, "layout_row_push", ctx_layout_row_push, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "layout_row_end", ctx_layout_row_end, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "layout_row", ctx_layout_row, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, ctx, "layout_row_template_begin", ctx_layout_row_template_begin, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "layout_row_template_push_dynamic", ctx_layout_row_template_push_dynamic, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "layout_row_template_push_variable", ctx_layout_row_template_push_variable, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "layout_row_template_push_static", ctx_layout_row_template_push_static, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "layout_row_template_end", ctx_layout_row_template_end, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "layout_space_begin", ctx_layout_space_begin, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, ctx, "layout_space_push", ctx_layout_space_push, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "layout_space_end", ctx_layout_space_end, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "layout_space_bounds", ctx_layout_space_bounds, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "layout_space_to_screen", ctx_layout_space_to_screen, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "layout_space_to_local", ctx_layout_space_to_local, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "layout_space_rect_to_screen", ctx_layout_space_rect_to_screen, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "layout_space_rect_to_local", ctx_layout_space_rect_to_local, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "spacer", ctx_spacer, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "spacing", ctx_spacing, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "layout_widget_bounds", ctx_layout_widget_bounds, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "layout_set_min_row_height", ctx_layout_set_min_row_height, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "layout_reset_min_row_height", ctx_layout_reset_min_row_height, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "layout_ratio_from_pixel", ctx_layout_ratio_from_pixel, MRB_ARGS_REQ(1));

  granada_define_native_fwd(mrb, native, "layout_row_dynamic", MRB_ARGS_ARG(2, 1));
  granada_define_native_fwd(mrb, native, "layout_row_static", MRB_ARGS_ARG(3, 1));
  granada_define_native_fwd(mrb, native, "layout_row_begin", MRB_ARGS_REQ(4));
  granada_define_native_fwd(mrb, native, "layout_row_push", MRB_ARGS_REQ(2));
  granada_define_native_fwd(mrb, native, "layout_row_end", MRB_ARGS_REQ(1));
  granada_define_native_fwd(mrb, native, "layout_row", MRB_ARGS_REQ(4));
  granada_define_native_fwd(mrb, native, "spacer", MRB_ARGS_REQ(1));
  granada_define_native_fwd(mrb, native, "spacing", MRB_ARGS_REQ(2));
}
