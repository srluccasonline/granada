/*
 * Widget queries, text/label, links, buttons, checkbox/radio, selectable,
 * slider/knob/progress, color picker, property, edit.
 *
 * Pointer in/out C APIs return the updated Ruby value (docs/architecture.md).
 */
#include "granada.h"

static mrb_value
finish_click(mrb_state *mrb, nk_bool clicked, mrb_value blk)
{
  if (!mrb_nil_p(blk) && clicked) {
    return mrb_yield_argv(mrb, blk, 0, NULL);
  }
  return mrb_bool_value(clicked);
}

static mrb_value ctx_widget_bounds(mrb_state *mrb, mrb_value self)
{ return granada_rect_wrap(mrb, nk_widget_bounds(granada_context_ptr(mrb, self))); }
static mrb_value ctx_widget_position(mrb_state *mrb, mrb_value self)
{ return granada_vec2_wrap(mrb, nk_widget_position(granada_context_ptr(mrb, self))); }
static mrb_value ctx_widget_size(mrb_state *mrb, mrb_value self)
{ return granada_vec2_wrap(mrb, nk_widget_size(granada_context_ptr(mrb, self))); }
static mrb_value ctx_widget_width(mrb_state *mrb, mrb_value self)
{ return mrb_float_value(mrb, nk_widget_width(granada_context_ptr(mrb, self))); }
static mrb_value ctx_widget_height(mrb_state *mrb, mrb_value self)
{ return mrb_float_value(mrb, nk_widget_height(granada_context_ptr(mrb, self))); }
static mrb_value ctx_widget_hovered(mrb_state *mrb, mrb_value self)
{ return mrb_bool_value(nk_widget_is_hovered(granada_context_ptr(mrb, self))); }

static mrb_value
ctx_widget_clicked(mrb_state *mrb, mrb_value self)
{
  mrb_int btn = NK_BUTTON_LEFT;
  mrb_get_args(mrb, "|i", &btn);
  return mrb_bool_value(nk_widget_is_mouse_clicked(granada_context_ptr(mrb, self), (enum nk_buttons)btn));
}

static mrb_value
ctx_widget_click_down(mrb_state *mrb, mrb_value self)
{
  mrb_int btn;
  mrb_bool down = TRUE;
  mrb_get_args(mrb, "i|b", &btn, &down);
  return mrb_bool_value(nk_widget_has_mouse_click_down(granada_context_ptr(mrb, self), (enum nk_buttons)btn, down ? nk_true : nk_false));
}

static mrb_value
ctx_disable_begin(mrb_state *mrb, mrb_value self)
{
  mrb_value blk = mrb_nil_value();
  struct nk_context *ctx = granada_context_ptr(mrb, self);
  mrb_get_args(mrb, "&", &blk);
  nk_widget_disable_begin(ctx);
  if (mrb_nil_p(blk)) return self;
  {
    mrb_value result;
    mrb_value block = blk;
    MRB_ENSURE(mrb, result, granada_yield, &block) {
      nk_widget_disable_end(ctx);
    }
    return result;
  }
}

static mrb_value ctx_disable_end(mrb_state *mrb, mrb_value self)
{ nk_widget_disable_end(granada_context_ptr(mrb, self)); return self; }

static mrb_value
ctx_text(mrb_state *mrb, mrb_value self)
{
  mrb_value str;
  mrb_int align = NK_TEXT_LEFT;
  mrb_get_args(mrb, "S|i", &str, &align);
  nk_text(granada_context_ptr(mrb, self), RSTRING_PTR(str), (int)RSTRING_LEN(str), (nk_flags)align);
  return self;
}

static mrb_value
ctx_text_colored(mrb_state *mrb, mrb_value self)
{
  mrb_value str, color;
  mrb_int align = NK_TEXT_LEFT;
  mrb_get_args(mrb, "So|i", &str, &color, &align);
  nk_text_colored(granada_context_ptr(mrb, self), RSTRING_PTR(str), (int)RSTRING_LEN(str), (nk_flags)align, granada_color_get(mrb, color));
  return self;
}

static mrb_value
ctx_text_wrap(mrb_state *mrb, mrb_value self)
{
  mrb_value str;
  mrb_get_args(mrb, "S", &str);
  nk_text_wrap(granada_context_ptr(mrb, self), RSTRING_PTR(str), (int)RSTRING_LEN(str));
  return self;
}

static mrb_value
ctx_text_wrap_colored(mrb_state *mrb, mrb_value self)
{
  mrb_value str, color;
  mrb_get_args(mrb, "So", &str, &color);
  nk_text_wrap_colored(granada_context_ptr(mrb, self), RSTRING_PTR(str), (int)RSTRING_LEN(str), granada_color_get(mrb, color));
  return self;
}

static mrb_value
ctx_label(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_int align = NK_TEXT_LEFT;
  mrb_get_args(mrb, "z|i", &text, &align);
  nk_label(granada_context_ptr(mrb, self), text, (nk_flags)align);
  return self;
}

static mrb_value
ctx_label_colored(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_int align;
  mrb_value color;
  mrb_get_args(mrb, "zio", &text, &align, &color);
  nk_label_colored(granada_context_ptr(mrb, self), text, (nk_flags)align, granada_color_get(mrb, color));
  return self;
}

static mrb_value
ctx_label_wrap(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_get_args(mrb, "z", &text);
  nk_label_wrap(granada_context_ptr(mrb, self), text);
  return self;
}

static mrb_value
ctx_label_colored_wrap(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_value color;
  mrb_get_args(mrb, "zo", &text, &color);
  nk_label_colored_wrap(granada_context_ptr(mrb, self), text, granada_color_get(mrb, color));
  return self;
}

static mrb_value
ctx_image(mrb_state *mrb, mrb_value self)
{
  mrb_value img;
  mrb_get_args(mrb, "o", &img);
  nk_image(granada_context_ptr(mrb, self), granada_image_get(mrb, img));
  return self;
}

static mrb_value
ctx_image_color(mrb_state *mrb, mrb_value self)
{
  mrb_value img, color;
  mrb_get_args(mrb, "oo", &img, &color);
  nk_image_color(granada_context_ptr(mrb, self), granada_image_get(mrb, img), granada_color_get(mrb, color));
  return self;
}

static mrb_value
ctx_value_bool(mrb_state *mrb, mrb_value self)
{
  char *prefix;
  mrb_bool v;
  mrb_get_args(mrb, "zb", &prefix, &v);
  nk_value_bool(granada_context_ptr(mrb, self), prefix, v ? 1 : 0);
  return self;
}

static mrb_value
ctx_value_int(mrb_state *mrb, mrb_value self)
{
  char *prefix;
  mrb_int v;
  mrb_get_args(mrb, "zi", &prefix, &v);
  nk_value_int(granada_context_ptr(mrb, self), prefix, (int)v);
  return self;
}

static mrb_value
ctx_value_uint(mrb_state *mrb, mrb_value self)
{
  char *prefix;
  mrb_int v;
  mrb_get_args(mrb, "zi", &prefix, &v);
  nk_value_uint(granada_context_ptr(mrb, self), prefix, (unsigned)v);
  return self;
}

static mrb_value
ctx_value_float(mrb_state *mrb, mrb_value self)
{
  char *prefix;
  mrb_float v;
  mrb_get_args(mrb, "zf", &prefix, &v);
  nk_value_float(granada_context_ptr(mrb, self), prefix, (float)v);
  return self;
}

static mrb_value
ctx_value_color_hex(mrb_state *mrb, mrb_value self)
{
  char *prefix;
  mrb_value color;
  mrb_get_args(mrb, "zo", &prefix, &color);
  nk_value_color_hex(granada_context_ptr(mrb, self), prefix, granada_color_get(mrb, color));
  return self;
}

static mrb_value
ctx_link_label(mrb_state *mrb, mrb_value self)
{
  char *title;
  mrb_int align = NK_TEXT_LEFT;
  mrb_value blk = mrb_nil_value();
  mrb_get_args(mrb, "z|i&", &title, &align, &blk);
  return finish_click(mrb, nk_link_label(granada_context_ptr(mrb, self), title, (nk_flags)align), blk);
}

static mrb_value
ctx_button_label(mrb_state *mrb, mrb_value self)
{
  char *title;
  mrb_value blk = mrb_nil_value();
  mrb_get_args(mrb, "z&", &title, &blk);
  return finish_click(mrb, nk_button_label(granada_context_ptr(mrb, self), title), blk);
}

static mrb_value
ctx_button_text(mrb_state *mrb, mrb_value self)
{
  mrb_value str;
  mrb_value blk = mrb_nil_value();
  mrb_get_args(mrb, "S&", &str, &blk);
  return finish_click(mrb, nk_button_text(granada_context_ptr(mrb, self), RSTRING_PTR(str), (int)RSTRING_LEN(str)), blk);
}

static mrb_value
ctx_button_color(mrb_state *mrb, mrb_value self)
{
  mrb_value color;
  mrb_value blk = mrb_nil_value();
  mrb_get_args(mrb, "o&", &color, &blk);
  return finish_click(mrb, nk_button_color(granada_context_ptr(mrb, self), granada_color_get(mrb, color)), blk);
}

static mrb_value
ctx_button_symbol(mrb_state *mrb, mrb_value self)
{
  mrb_int sym;
  mrb_value blk = mrb_nil_value();
  mrb_get_args(mrb, "i&", &sym, &blk);
  return finish_click(mrb, nk_button_symbol(granada_context_ptr(mrb, self), (enum nk_symbol_type)sym), blk);
}

static mrb_value
ctx_button_image(mrb_state *mrb, mrb_value self)
{
  mrb_value img;
  mrb_value blk = mrb_nil_value();
  mrb_get_args(mrb, "o&", &img, &blk);
  return finish_click(mrb, nk_button_image(granada_context_ptr(mrb, self), granada_image_get(mrb, img)), blk);
}

static mrb_value
ctx_button_symbol_label(mrb_state *mrb, mrb_value self)
{
  mrb_int sym, align = NK_TEXT_LEFT;
  char *title;
  mrb_value blk = mrb_nil_value();
  mrb_get_args(mrb, "iz|i&", &sym, &title, &align, &blk);
  return finish_click(mrb, nk_button_symbol_label(granada_context_ptr(mrb, self), (enum nk_symbol_type)sym, title, (nk_flags)align), blk);
}

static mrb_value
ctx_button_image_label(mrb_state *mrb, mrb_value self)
{
  mrb_value img;
  char *title;
  mrb_int align = NK_TEXT_LEFT;
  mrb_value blk = mrb_nil_value();
  mrb_get_args(mrb, "oz|i&", &img, &title, &align, &blk);
  return finish_click(mrb, nk_button_image_label(granada_context_ptr(mrb, self), granada_image_get(mrb, img), title, (nk_flags)align), blk);
}

static mrb_value
ctx_button_set_behavior(mrb_state *mrb, mrb_value self)
{
  mrb_int b;
  mrb_get_args(mrb, "i", &b);
  nk_button_set_behavior(granada_context_ptr(mrb, self), (enum nk_button_behavior)b);
  return self;
}

static mrb_value
ctx_button_push_behavior(mrb_state *mrb, mrb_value self)
{
  mrb_int b;
  mrb_get_args(mrb, "i", &b);
  return mrb_bool_value(nk_button_push_behavior(granada_context_ptr(mrb, self), (enum nk_button_behavior)b));
}

static mrb_value ctx_button_pop_behavior(mrb_state *mrb, mrb_value self)
{ return mrb_bool_value(nk_button_pop_behavior(granada_context_ptr(mrb, self))); }

static mrb_value
ctx_check_label(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_bool active;
  mrb_get_args(mrb, "zb", &text, &active);
  return mrb_bool_value(nk_check_label(granada_context_ptr(mrb, self), text, active ? nk_true : nk_false));
}

static mrb_value
ctx_checkbox_label(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_bool active;
  nk_bool a;
  mrb_get_args(mrb, "zb", &text, &active);
  a = active ? nk_true : nk_false;
  nk_checkbox_label(granada_context_ptr(mrb, self), text, &a);
  return mrb_bool_value(a);
}

static mrb_value
ctx_checkbox_flags_label(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_int flags, value;
  unsigned f;
  mrb_get_args(mrb, "zii", &text, &flags, &value);
  f = (unsigned)flags;
  nk_checkbox_flags_label(granada_context_ptr(mrb, self), text, &f, (unsigned)value);
  return mrb_int_value(mrb, (mrb_int)f);
}

static mrb_value
ctx_radio_label(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_bool active;
  nk_bool a;
  mrb_get_args(mrb, "zb", &text, &active);
  a = active ? nk_true : nk_false;
  nk_radio_label(granada_context_ptr(mrb, self), text, &a);
  return mrb_bool_value(a);
}

static mrb_value
ctx_option_label(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_bool active;
  mrb_get_args(mrb, "zb", &text, &active);
  return mrb_bool_value(nk_option_label(granada_context_ptr(mrb, self), text, active ? nk_true : nk_false));
}

static mrb_value
ctx_selectable_label(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_int align = NK_TEXT_LEFT;
  mrb_bool value;
  nk_bool v;
  mrb_get_args(mrb, "zib", &text, &align, &value);
  v = value ? nk_true : nk_false;
  nk_selectable_label(granada_context_ptr(mrb, self), text, (nk_flags)align, &v);
  return mrb_bool_value(v);
}

static mrb_value
ctx_select_label(mrb_state *mrb, mrb_value self)
{
  char *text;
  mrb_int align = NK_TEXT_LEFT;
  mrb_bool value;
  mrb_get_args(mrb, "zib", &text, &align, &value);
  return mrb_bool_value(nk_select_label(granada_context_ptr(mrb, self), text, (nk_flags)align, value ? nk_true : nk_false));
}

static mrb_value
ctx_slider_float(mrb_state *mrb, mrb_value self)
{
  mrb_float min, val, max, step;
  float v;
  mrb_get_args(mrb, "ffff", &min, &val, &max, &step);
  v = (float)val;
  nk_slider_float(granada_context_ptr(mrb, self), (float)min, &v, (float)max, (float)step);
  return mrb_float_value(mrb, v);
}

static mrb_value
ctx_slide_float(mrb_state *mrb, mrb_value self)
{
  mrb_float min, val, max, step;
  mrb_get_args(mrb, "ffff", &min, &val, &max, &step);
  return mrb_float_value(mrb, nk_slide_float(granada_context_ptr(mrb, self), (float)min, (float)val, (float)max, (float)step));
}

static mrb_value
ctx_slider_int(mrb_state *mrb, mrb_value self)
{
  mrb_int min, val, max, step;
  int v;
  mrb_get_args(mrb, "iiii", &min, &val, &max, &step);
  v = (int)val;
  nk_slider_int(granada_context_ptr(mrb, self), (int)min, &v, (int)max, (int)step);
  return mrb_int_value(mrb, v);
}

static mrb_value
ctx_slide_int(mrb_state *mrb, mrb_value self)
{
  mrb_int min, val, max, step;
  mrb_get_args(mrb, "iiii", &min, &val, &max, &step);
  return mrb_int_value(mrb, nk_slide_int(granada_context_ptr(mrb, self), (int)min, (int)val, (int)max, (int)step));
}

static mrb_value
ctx_knob_float(mrb_state *mrb, mrb_value self)
{
  mrb_float min, val, max, step, dead = 0;
  mrb_int heading = NK_UP;
  float v;
  mrb_get_args(mrb, "ffff|if", &min, &val, &max, &step, &heading, &dead);
  v = (float)val;
  nk_knob_float(granada_context_ptr(mrb, self), (float)min, &v, (float)max, (float)step, (enum nk_heading)heading, (float)dead);
  return mrb_float_value(mrb, v);
}

static mrb_value
ctx_progress(mrb_state *mrb, mrb_value self)
{
  mrb_int cur, max;
  mrb_bool mod = FALSE;
  nk_size c;
  mrb_get_args(mrb, "ii|b", &cur, &max, &mod);
  c = (nk_size)cur;
  nk_progress(granada_context_ptr(mrb, self), &c, (nk_size)max, mod ? nk_true : nk_false);
  return mrb_int_value(mrb, (mrb_int)c);
}

static mrb_value
ctx_prog(mrb_state *mrb, mrb_value self)
{
  mrb_int cur, max;
  mrb_bool mod = FALSE;
  mrb_get_args(mrb, "ii|b", &cur, &max, &mod);
  return mrb_int_value(mrb, (mrb_int)nk_prog(granada_context_ptr(mrb, self), (nk_size)cur, (nk_size)max, mod ? nk_true : nk_false));
}

static mrb_value
ctx_color_picker(mrb_state *mrb, mrb_value self)
{
  mrb_value cf;
  mrb_int fmt = NK_RGBA;
  mrb_get_args(mrb, "o|i", &cf, &fmt);
  return granada_colorf_wrap(mrb, nk_color_picker(granada_context_ptr(mrb, self), granada_colorf_get(mrb, cf), (enum nk_color_format)fmt));
}

static mrb_value
ctx_color_pick(mrb_state *mrb, mrb_value self)
{
  mrb_value cf;
  mrb_int fmt = NK_RGBA;
  struct nk_colorf c;
  mrb_get_args(mrb, "o|i", &cf, &fmt);
  c = granada_colorf_get(mrb, cf);
  nk_color_pick(granada_context_ptr(mrb, self), &c, (enum nk_color_format)fmt);
  return granada_colorf_wrap(mrb, c);
}

static mrb_value
ctx_propertyi(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_int min, val, max, step;
  mrb_float inc = 1.0;
  mrb_get_args(mrb, "ziiii|f", &name, &min, &val, &max, &step, &inc);
  return mrb_int_value(mrb, nk_propertyi(granada_context_ptr(mrb, self), name, (int)min, (int)val, (int)max, (int)step, (float)inc));
}

static mrb_value
ctx_propertyf(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_float min, val, max, step, inc = 1.0;
  mrb_get_args(mrb, "zffff|f", &name, &min, &val, &max, &step, &inc);
  return mrb_float_value(mrb, nk_propertyf(granada_context_ptr(mrb, self), name, (float)min, (float)val, (float)max, (float)step, (float)inc));
}

static mrb_value
ctx_propertyd(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_float min, val, max, step, inc = 1.0;
  mrb_get_args(mrb, "zffff|f", &name, &min, &val, &max, &step, &inc);
  return mrb_float_value(mrb, nk_propertyd(granada_context_ptr(mrb, self), name, (double)min, (double)val, (double)max, (double)step, (float)inc));
}

static mrb_value
ctx_property_int(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_int min, val, max, step;
  mrb_float inc = 1.0;
  int v;
  mrb_get_args(mrb, "ziiii|f", &name, &min, &val, &max, &step, &inc);
  v = (int)val;
  nk_property_int(granada_context_ptr(mrb, self), name, (int)min, &v, (int)max, (int)step, (float)inc);
  return mrb_int_value(mrb, v);
}

static mrb_value
ctx_property_float(mrb_state *mrb, mrb_value self)
{
  char *name;
  mrb_float min, val, max, step, inc = 1.0;
  float v;
  mrb_get_args(mrb, "zffff|f", &name, &min, &val, &max, &step, &inc);
  v = (float)val;
  nk_property_float(granada_context_ptr(mrb, self), name, (float)min, &v, (float)max, (float)step, (float)inc);
  return mrb_float_value(mrb, v);
}

static mrb_value
ctx_edit_string(mrb_state *mrb, mrb_value self)
{
  mrb_value str;
  mrb_int flags = NK_EDIT_FIELD;
  mrb_int max = 256;
  mrb_value filter = mrb_nil_value();
  int len;
  nk_flags ev;
  char *buf;

  mrb_get_args(mrb, "S|iio", &str, &flags, &max, &filter);
  if (max < 1) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "edit max must be positive");
  }
  mrb_str_modify(mrb, RSTRING(str));
  len = (int)RSTRING_LEN(str);
  if (len > (int)max) len = (int)max;
  mrb_str_resize(mrb, str, max);
  buf = RSTRING_PTR(str);
  ev = nk_edit_string(granada_context_ptr(mrb, self), (nk_flags)flags, buf, &len, (int)max, granada_filter_from(mrb, filter));
  mrb_str_resize(mrb, str, len);
  return mrb_int_value(mrb, (mrb_int)ev);
}

static mrb_value
ctx_edit_focus(mrb_state *mrb, mrb_value self)
{
  mrb_int flags = NK_EDIT_DEFAULT;
  mrb_get_args(mrb, "|i", &flags);
  nk_edit_focus(granada_context_ptr(mrb, self), (nk_flags)flags);
  return self;
}

static mrb_value ctx_edit_unfocus(mrb_state *mrb, mrb_value self)
{ nk_edit_unfocus(granada_context_ptr(mrb, self)); return self; }

void
mrb_granada_widgets_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native)
{
  static const char *fwds[] = {
    "widget_bounds", "widget_position", "widget_size", "widget_width", "widget_height",
    "widget_hovered?", "widget_clicked?", "widget_click_down?",
    "widget_disable_begin", "widget_disable_end", "disable",
    "text", "text_colored", "text_wrap", "text_wrap_colored",
    "label", "label_colored", "label_wrap", "label_colored_wrap",
    "image", "image_color",
    "value_bool", "value_int", "value_uint", "value_float", "value_color_hex",
    "link_label",
    "button_label", "button", "button_text", "button_color", "button_symbol",
    "button_image", "button_symbol_label", "button_image_label",
    "button_set_behavior", "button_push_behavior", "button_pop_behavior",
    "check_label", "checkbox_label", "checkbox", "checkbox_flags_label",
    "radio_label", "option_label",
    "selectable_label", "select_label",
    "slider_float", "slide_float", "slider_int", "slide_int", "knob_float",
    "progress", "prog", "color_picker", "color_pick",
    "propertyi", "propertyf", "propertyd", "property_int", "property_float",
    "edit_string", "edit_focus", "edit_unfocus",
    0
  };

  mrb_define_method(mrb, ctx, "widget_bounds", ctx_widget_bounds, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "widget_position", ctx_widget_position, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "widget_size", ctx_widget_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "widget_width", ctx_widget_width, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "widget_height", ctx_widget_height, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "widget_hovered?", ctx_widget_hovered, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "widget_clicked?", ctx_widget_clicked, MRB_ARGS_OPT(1));
  mrb_define_method(mrb, ctx, "widget_click_down?", ctx_widget_click_down, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, ctx, "widget_disable_begin", ctx_disable_begin, MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "disable", ctx_disable_begin, MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "widget_disable_end", ctx_disable_end, MRB_ARGS_NONE());

  mrb_define_method(mrb, ctx, "text", ctx_text, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, ctx, "text_colored", ctx_text_colored, MRB_ARGS_ARG(2, 1));
  mrb_define_method(mrb, ctx, "text_wrap", ctx_text_wrap, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "text_wrap_colored", ctx_text_wrap_colored, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "label", ctx_label, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, ctx, "label_colored", ctx_label_colored, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, ctx, "label_wrap", ctx_label_wrap, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "label_colored_wrap", ctx_label_colored_wrap, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "image", ctx_image, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "image_color", ctx_image_color, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "value_bool", ctx_value_bool, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "value_int", ctx_value_int, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "value_uint", ctx_value_uint, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "value_float", ctx_value_float, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "value_color_hex", ctx_value_color_hex, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "link_label", ctx_link_label, MRB_ARGS_ARG(1, 1) | MRB_ARGS_BLOCK());

  mrb_define_method(mrb, ctx, "button_label", ctx_button_label, MRB_ARGS_REQ(1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "button", ctx_button_label, MRB_ARGS_REQ(1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "button_text", ctx_button_text, MRB_ARGS_REQ(1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "button_color", ctx_button_color, MRB_ARGS_REQ(1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "button_symbol", ctx_button_symbol, MRB_ARGS_REQ(1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "button_image", ctx_button_image, MRB_ARGS_REQ(1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "button_symbol_label", ctx_button_symbol_label, MRB_ARGS_ARG(2, 1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "button_image_label", ctx_button_image_label, MRB_ARGS_ARG(2, 1) | MRB_ARGS_BLOCK());
  mrb_define_method(mrb, ctx, "button_set_behavior", ctx_button_set_behavior, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "button_push_behavior", ctx_button_push_behavior, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "button_pop_behavior", ctx_button_pop_behavior, MRB_ARGS_NONE());

  mrb_define_method(mrb, ctx, "check_label", ctx_check_label, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "checkbox_label", ctx_checkbox_label, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "checkbox", ctx_checkbox_label, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "checkbox_flags_label", ctx_checkbox_flags_label, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, ctx, "radio_label", ctx_radio_label, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "option_label", ctx_option_label, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "selectable_label", ctx_selectable_label, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, ctx, "select_label", ctx_select_label, MRB_ARGS_REQ(3));

  mrb_define_method(mrb, ctx, "slider_float", ctx_slider_float, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, ctx, "slide_float", ctx_slide_float, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, ctx, "slider_int", ctx_slider_int, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, ctx, "slide_int", ctx_slide_int, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, ctx, "knob_float", ctx_knob_float, MRB_ARGS_ARG(4, 2));
  mrb_define_method(mrb, ctx, "progress", ctx_progress, MRB_ARGS_ARG(2, 1));
  mrb_define_method(mrb, ctx, "prog", ctx_prog, MRB_ARGS_ARG(2, 1));
  mrb_define_method(mrb, ctx, "color_picker", ctx_color_picker, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, ctx, "color_pick", ctx_color_pick, MRB_ARGS_ARG(1, 1));

  mrb_define_method(mrb, ctx, "propertyi", ctx_propertyi, MRB_ARGS_ARG(5, 1));
  mrb_define_method(mrb, ctx, "propertyf", ctx_propertyf, MRB_ARGS_ARG(5, 1));
  mrb_define_method(mrb, ctx, "propertyd", ctx_propertyd, MRB_ARGS_ARG(5, 1));
  mrb_define_method(mrb, ctx, "property_int", ctx_property_int, MRB_ARGS_ARG(5, 1));
  mrb_define_method(mrb, ctx, "property_float", ctx_property_float, MRB_ARGS_ARG(5, 1));

  mrb_define_method(mrb, ctx, "edit_string", ctx_edit_string, MRB_ARGS_ARG(1, 3));
  mrb_define_method(mrb, ctx, "edit_focus", ctx_edit_focus, MRB_ARGS_OPT(1));
  mrb_define_method(mrb, ctx, "edit_unfocus", ctx_edit_unfocus, MRB_ARGS_NONE());

  granada_define_native_fwds(mrb, native, fwds);
}
