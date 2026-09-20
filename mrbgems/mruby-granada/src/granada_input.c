/*
 * Input frame: nk_input_begin / motion / key / button / scroll / char / end.
 */
#include "granada.h"

static mrb_value
ctx_input_begin(mrb_state *mrb, mrb_value self)
{
  nk_input_begin(granada_context_ptr(mrb, self));
  return self;
}

static mrb_value
ctx_input_end(mrb_state *mrb, mrb_value self)
{
  nk_input_end(granada_context_ptr(mrb, self));
  return self;
}

static mrb_value
ctx_input_motion(mrb_state *mrb, mrb_value self)
{
  mrb_int x, y;
  mrb_get_args(mrb, "ii", &x, &y);
  nk_input_motion(granada_context_ptr(mrb, self), (int)x, (int)y);
  return self;
}

static mrb_value
ctx_input_key(mrb_state *mrb, mrb_value self)
{
  mrb_int key;
  mrb_bool down = TRUE;
  mrb_get_args(mrb, "i|b", &key, &down);
  nk_input_key(granada_context_ptr(mrb, self), (enum nk_keys)key, down ? nk_true : nk_false);
  return self;
}

static mrb_value
ctx_input_button(mrb_state *mrb, mrb_value self)
{
  mrb_int btn, x, y;
  mrb_bool down = TRUE;
  mrb_get_args(mrb, "iii|b", &btn, &x, &y, &down);
  nk_input_button(granada_context_ptr(mrb, self), (enum nk_buttons)btn, (int)x, (int)y, down ? nk_true : nk_false);
  return self;
}

static mrb_value
ctx_input_scroll(mrb_state *mrb, mrb_value self)
{
  mrb_value val;
  mrb_get_args(mrb, "o", &val);
  nk_input_scroll(granada_context_ptr(mrb, self), granada_vec2_get(mrb, val));
  return self;
}

static mrb_value
ctx_input_char(mrb_state *mrb, mrb_value self)
{
  mrb_value ch;
  mrb_get_args(mrb, "o", &ch);
  if (mrb_string_p(ch)) {
    if (RSTRING_LEN(ch) < 1) {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "input_char needs a non-empty string");
    }
    nk_input_char(granada_context_ptr(mrb, self), RSTRING_PTR(ch)[0]);
  } else {
    nk_input_char(granada_context_ptr(mrb, self), (char)mrb_as_int(mrb, ch));
  }
  return self;
}

static mrb_value
ctx_input_unicode(mrb_state *mrb, mrb_value self)
{
  mrb_int rune;
  mrb_get_args(mrb, "i", &rune);
  nk_input_unicode(granada_context_ptr(mrb, self), (nk_rune)rune);
  return self;
}

void
mrb_granada_input_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native)
{
  mrb_define_method(mrb, ctx, "input_begin", ctx_input_begin, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "input_end", ctx_input_end, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "input_motion", ctx_input_motion, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ctx, "input_key", ctx_input_key, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, ctx, "input_button", ctx_input_button, MRB_ARGS_ARG(3, 1));
  mrb_define_method(mrb, ctx, "input_scroll", ctx_input_scroll, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "input_char", ctx_input_char, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, ctx, "input_unicode", ctx_input_unicode, MRB_ARGS_REQ(1));

  granada_define_native_fwd(mrb, native, "input_begin", MRB_ARGS_REQ(1));
  granada_define_native_fwd(mrb, native, "input_end", MRB_ARGS_REQ(1));
  granada_define_native_fwd(mrb, native, "input_motion", MRB_ARGS_REQ(3));
  granada_define_native_fwd(mrb, native, "input_key", MRB_ARGS_ARG(2, 1));
  granada_define_native_fwd(mrb, native, "input_button", MRB_ARGS_ARG(4, 1));
  granada_define_native_fwd(mrb, native, "input_scroll", MRB_ARGS_REQ(2));
  granada_define_native_fwd(mrb, native, "input_char", MRB_ARGS_REQ(2));
  granada_define_native_fwd(mrb, native, "input_unicode", MRB_ARGS_REQ(2));
}
