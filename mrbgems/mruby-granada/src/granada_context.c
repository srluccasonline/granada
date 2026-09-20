/*
 * Granada::Context — wraps struct nk_context with nk_init_default / nk_clear / nk_free.
 */
#include "granada.h"

static void
context_free(mrb_state *mrb, void *ptr)
{
  struct nk_context *ctx = (struct nk_context *)ptr;
  if (ctx) {
    nk_free(ctx);
    mrb_free(mrb, ctx);
  }
}

const struct mrb_data_type granada_context_type = { "Granada::Context", context_free };

struct nk_context *
granada_context_ptr(mrb_state *mrb, mrb_value obj)
{
  struct nk_context *ctx = (struct nk_context *)mrb_data_get_ptr(mrb, obj, &granada_context_type);
  if (!ctx) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Granada::Context is not initialized (already freed?)");
  }
  return ctx;
}

static mrb_value
context_initialize(mrb_state *mrb, mrb_value self)
{
  struct nk_context *ctx;
  void *old = DATA_PTR(self);

  if (old) {
    context_free(mrb, old);
    DATA_PTR(self) = NULL;
  }

  ctx = (struct nk_context *)mrb_malloc(mrb, sizeof(*ctx));
  if (!nk_init_default(ctx, NULL)) {
    mrb_free(mrb, ctx);
    mrb_raise(mrb, E_RUNTIME_ERROR, "nk_init_default failed");
  }
  mrb_data_init(self, ctx, &granada_context_type);
  return self;
}

static mrb_value
context_clear(mrb_state *mrb, mrb_value self)
{
  nk_clear(granada_context_ptr(mrb, self));
  return self;
}

static mrb_value
context_free_m(mrb_state *mrb, mrb_value self)
{
  struct nk_context *ctx = (struct nk_context *)mrb_data_get_ptr(mrb, self, &granada_context_type);
  if (ctx) {
    nk_free(ctx);
    mrb_free(mrb, ctx);
    DATA_PTR(self) = NULL;
  }
  return mrb_nil_value();
}

static mrb_value
context_alive(mrb_state *mrb, mrb_value self)
{
  return mrb_bool_value(mrb_data_get_ptr(mrb, self, &granada_context_type) != NULL);
}

static mrb_value
context_style_default(mrb_state *mrb, mrb_value self)
{
  nk_style_default(granada_context_ptr(mrb, self));
  return self;
}

static mrb_value
native_init_default(mrb_state *mrb, mrb_value self)
{
  (void)self;
  return mrb_obj_new(mrb, mrb_class_get_under(mrb, mrb_module_get(mrb, "Granada"), "Context"), 0, NULL);
}

static mrb_value
native_clear(mrb_state *mrb, mrb_value self)
{
  mrb_value ctx;
  (void)self;
  mrb_get_args(mrb, "o", &ctx);
  nk_clear(granada_context_ptr(mrb, ctx));
  return ctx;
}

static mrb_value
native_free(mrb_state *mrb, mrb_value self)
{
  mrb_value ctx;
  (void)self;
  mrb_get_args(mrb, "o", &ctx);
  return context_free_m(mrb, ctx);
}

void
mrb_granada_context_init(mrb_state *mrb, struct RClass *mod, struct RClass *native)
{
  struct RClass *ctx = mrb_define_class_under(mrb, mod, "Context", mrb->object_class);
  MRB_SET_INSTANCE_TT(ctx, MRB_TT_CDATA);

  mrb_define_method(mrb, ctx, "initialize", context_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "clear", context_clear, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "free", context_free_m, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "alive?", context_alive, MRB_ARGS_NONE());
  mrb_define_method(mrb, ctx, "style_default", context_style_default, MRB_ARGS_NONE());

  mrb_define_module_function(mrb, native, "init_default", native_init_default, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, native, "clear", native_clear, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, native, "free", native_free, MRB_ARGS_REQ(1));
}
