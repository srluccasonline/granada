/*
 * Custom drawing on the current window canvas (nk_window_get_canvas).
 * Must be called between begin/end; use widget_alloc to reserve layout space.
 */
#include "granada.h"

static struct nk_command_buffer *
canvas_buf(mrb_state *mrb, mrb_value self)
{
  struct nk_command_buffer *b = nk_window_get_canvas(granada_context_ptr(mrb, self));
  if (!b) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "canvas drawing requires an open window");
  }
  return b;
}

static mrb_value
ctx_widget_alloc(mrb_state *mrb, mrb_value self)
{
  struct nk_rect bounds = {0, 0, 0, 0};
  nk_widget(&bounds, granada_context_ptr(mrb, self));
  return granada_rect_wrap(mrb, bounds);
}

static mrb_value
ctx_fill_rect(mrb_state *mrb, mrb_value self)
{
  mrb_value rect, color;
  mrb_float rounding = 0;
  mrb_get_args(mrb, "oo|f", &rect, &color, &rounding);
  nk_fill_rect(canvas_buf(mrb, self), granada_rect_get(mrb, rect), (float)rounding, granada_color_get(mrb, color));
  return self;
}

static mrb_value
ctx_stroke_rect(mrb_state *mrb, mrb_value self)
{
  mrb_value rect, color;
  mrb_float thickness = 1.0, rounding = 0;
  mrb_get_args(mrb, "oo|ff", &rect, &color, &thickness, &rounding);
  nk_stroke_rect(canvas_buf(mrb, self), granada_rect_get(mrb, rect), (float)rounding, (float)thickness, granada_color_get(mrb, color));
  return self;
}

static mrb_value
ctx_stroke_line(mrb_state *mrb, mrb_value self)
{
  mrb_float x0, y0, x1, y1, thickness = 1.0;
  mrb_value color;
  mrb_get_args(mrb, "ffffo|f", &x0, &y0, &x1, &y1, &color, &thickness);
  nk_stroke_line(canvas_buf(mrb, self), (float)x0, (float)y0, (float)x1, (float)y1, (float)thickness, granada_color_get(mrb, color));
  return self;
}

static mrb_value
ctx_fill_circle(mrb_state *mrb, mrb_value self)
{
  mrb_value rect, color;
  mrb_get_args(mrb, "oo", &rect, &color);
  nk_fill_circle(canvas_buf(mrb, self), granada_rect_get(mrb, rect), granada_color_get(mrb, color));
  return self;
}

static mrb_value
ctx_stroke_circle(mrb_state *mrb, mrb_value self)
{
  mrb_value rect, color;
  mrb_float thickness = 1.0;
  mrb_get_args(mrb, "oo|f", &rect, &color, &thickness);
  nk_stroke_circle(canvas_buf(mrb, self), granada_rect_get(mrb, rect), (float)thickness, granada_color_get(mrb, color));
  return self;
}

static mrb_value
ctx_fill_triangle(mrb_state *mrb, mrb_value self)
{
  mrb_float x0, y0, x1, y1, x2, y2;
  mrb_value color;
  mrb_get_args(mrb, "ffffffo", &x0, &y0, &x1, &y1, &x2, &y2, &color);
  nk_fill_triangle(canvas_buf(mrb, self), (float)x0, (float)y0, (float)x1, (float)y1, (float)x2, (float)y2, granada_color_get(mrb, color));
  return self;
}

static mrb_value
ctx_stroke_triangle(mrb_state *mrb, mrb_value self)
{
  mrb_float x0, y0, x1, y1, x2, y2, thickness = 1.0;
  mrb_value color;
  mrb_get_args(mrb, "ffffffo|f", &x0, &y0, &x1, &y1, &x2, &y2, &color, &thickness);
  nk_stroke_triangle(canvas_buf(mrb, self), (float)x0, (float)y0, (float)x1, (float)y1, (float)x2, (float)y2, (float)thickness, granada_color_get(mrb, color));
  return self;
}

static mrb_value
ctx_draw_image(mrb_state *mrb, mrb_value self)
{
  mrb_value rect, img, color = mrb_nil_value();
  struct nk_color col;
  struct nk_image image;
  mrb_get_args(mrb, "oo|o", &rect, &img, &color);
  image = granada_image_get(mrb, img);
  col = mrb_nil_p(color) ? nk_rgb(255, 255, 255) : granada_color_get(mrb, color);
  nk_draw_image(canvas_buf(mrb, self), granada_rect_get(mrb, rect), &image, col);
  return self;
}

static mrb_value
ctx_draw_text(mrb_state *mrb, mrb_value self)
{
  mrb_value rect, str, fg, bg = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  struct nk_color background;
  mrb_get_args(mrb, "oSo|o", &rect, &str, &fg, &bg);
  background = mrb_nil_p(bg) ? nk_rgba(0, 0, 0, 0) : granada_color_get(mrb, bg);
  if (!ctx->style.font) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "draw_text requires a font");
  }
  nk_draw_text(canvas_buf(mrb, self), granada_rect_get(mrb, rect),
               RSTRING_PTR(str), (int)RSTRING_LEN(str),
               ctx->style.font, background, granada_color_get(mrb, fg));
  return self;
}

static mrb_value
ctx_scissor(mrb_state *mrb, mrb_value self)
{
  mrb_value rect;
  mrb_get_args(mrb, "o", &rect);
  nk_push_scissor(canvas_buf(mrb, self), granada_rect_get(mrb, rect));
  return self;
}

void
mrb_granada_canvas_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native)
{
  static const char *fwds[] = {
    "widget_alloc", "fill_rect", "stroke_rect", "stroke_line",
    "fill_circle", "stroke_circle", "fill_triangle", "stroke_triangle",
    "draw_image", "draw_text", "scissor",
    0
  };
  mrb_define_method(mrb, ctx, "widget_alloc", ctx_widget_alloc, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "fill_rect", ctx_fill_rect, MRB_ARGS_ARG(2, 1));
  mrb_define_method(mrb, ctx, "stroke_rect", ctx_stroke_rect, MRB_ARGS_ARG(2, 2));
  mrb_define_method(mrb, ctx, "stroke_line", ctx_stroke_line, MRB_ARGS_ARG(5, 1));
  mrb_define_method(mrb, ctx, "fill_circle", ctx_fill_circle, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "stroke_circle", ctx_stroke_circle, MRB_ARGS_ARG(2, 1));
  mrb_define_method(mrb, ctx, "fill_triangle", ctx_fill_triangle, MRB_ARGS_REQ(7));
  mrb_define_method(mrb, ctx, "stroke_triangle", ctx_stroke_triangle, MRB_ARGS_ARG(7, 1));
  mrb_define_method(mrb, ctx, "draw_image", ctx_draw_image, MRB_ARGS_ARG(2, 1));
  mrb_define_method(mrb, ctx, "draw_text", ctx_draw_text, MRB_ARGS_ARG(3, 1));
  mrb_define_method(mrb, ctx, "scissor", ctx_scissor, MRB_ARGS_REQ(1));
  granada_define_native_fwds(mrb, native, fwds);
}
