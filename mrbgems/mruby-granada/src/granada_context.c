/*
 * Granada::Context — wraps struct nk_context with nk_init_default / nk_clear / nk_free.
 */
#include "granada.h"

static void
context_free(mrb_state *mrb, void *ptr)
{
  granada_ctx *g = (granada_ctx *)ptr;
  if (g) {
    nk_free(&g->nk);
    nk_font_atlas_clear(&g->atlas);
    mrb_free(mrb, g->floats);
    mrb_free(mrb, g);
  }
}

const struct mrb_data_type granada_context_type = { "Granada::Context", context_free };

granada_ctx *
granada_ctx_get(mrb_state *mrb, mrb_value obj)
{
  granada_ctx *g = (granada_ctx *)mrb_data_get_ptr(mrb, obj, &granada_context_type);
  if (!g) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Granada::Context is not initialized (already freed?)");
  }
  return g;
}

struct nk_context *
granada_context_ptr(mrb_state *mrb, mrb_value obj)
{
  return &granada_ctx_get(mrb, obj)->nk;
}

float *
granada_ctx_floats(mrb_state *mrb, mrb_value obj, int n)
{
  granada_ctx *g = granada_ctx_get(mrb, obj);
  if (n < 1) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "need at least one float");
  }
  if (g->floats_cap < n) {
    g->floats = (float *)mrb_realloc(mrb, g->floats, sizeof(float) * (size_t)n);
    g->floats_cap = n;
  }
  return g->floats;
}

mrb_value
granada_yield(mrb_state *mrb, void *data)
{
  return mrb_yield_argv(mrb, *(mrb_value *)data, 0, NULL);
}

static mrb_value
granada_native_fwd(mrb_state *mrb, mrb_value self)
{
  mrb_value *argv;
  mrb_int argc;
  mrb_value blk;
  mrb_sym mid = mrb_get_mid(mrb);

  (void)self;
  mrb_get_args(mrb, "*&", &argv, &argc, &blk);
  if (argc < 1) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "Granada::Native.%s requires a Context",
               mrb_sym_name(mrb, mid));
  }
  return mrb_funcall_with_block(mrb, argv[0], mid, argc - 1, argv + 1, blk);
}

void
granada_define_native_fwd(mrb_state *mrb, struct RClass *native, const char *name, mrb_aspec spec)
{
  mrb_define_module_function(mrb, native, name, granada_native_fwd, spec);
}

static mrb_value
context_initialize(mrb_state *mrb, mrb_value self)
{
  granada_ctx *g;
  void *old = DATA_PTR(self);

  if (old) {
    context_free(mrb, old);
    DATA_PTR(self) = NULL;
  }

  g = (granada_ctx *)mrb_malloc(mrb, sizeof(*g));
  g->floats = NULL;
  g->floats_cap = 0;
  g->font = NULL;
  {
    int tw = 0, th = 0;
    nk_font_atlas_init_default(&g->atlas);
    nk_font_atlas_begin(&g->atlas);
    g->font = nk_font_atlas_add_default(&g->atlas, 13.0f, 0);
    nk_font_atlas_bake(&g->atlas, &tw, &th, NK_FONT_ATLAS_ALPHA8);
    nk_font_atlas_end(&g->atlas, nk_handle_id(0), 0);
  }
  if (!g->font || !nk_init_default(&g->nk, &g->font->handle)) {
    nk_font_atlas_clear(&g->atlas);
    mrb_free(mrb, g);
    mrb_raise(mrb, E_RUNTIME_ERROR, "nk_init_default failed");
  }
  mrb_data_init(self, g, &granada_context_type);
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
  granada_ctx *g = (granada_ctx *)mrb_data_get_ptr(mrb, self, &granada_context_type);
  if (g) {
    context_free(mrb, g);
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

  mrb_granada_input_init(mrb, ctx, native);
  mrb_granada_window_init(mrb, ctx, native);
  mrb_granada_layout_init(mrb, ctx, native);
}
