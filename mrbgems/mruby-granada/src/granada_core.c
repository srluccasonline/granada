/*
 * Granada core: module bootstrap for mruby 4.0.
 *
 * Native widget bindings land in later translation units. This file only
 * defines Granada / Granada::Native and version constants so the gem loads
 * on a stock mruby 4.0.0 before any Nuklear call is wrapped.
 *
 * mruby 4 notes used here:
 *   - gem entry points stay mrb_<gem_underscored>_gem_{init,final}
 *   - no mrb_alloca (renamed mrb_temp_alloc in 4.0)
 *   - presym is always on
 */
#include "granada.h"

void
mrb_mruby_granada_gem_init(mrb_state *mrb)
{
  struct RClass *mod;
  struct RClass *native;

  mod = mrb_define_module(mrb, "Granada");
  native = mrb_define_module_under(mrb, mod, "Native");

  mrb_define_const(mrb, mod, "VERSION",
                   mrb_str_new_lit(mrb, GRANADA_VERSION));
  mrb_define_const(mrb, mod, "NUKLEAR_VERSION",
                   mrb_str_new_lit(mrb, GRANADA_NUKLEAR_VERSION));

  mrb_granada_flags_init(mrb, mod);
  mrb_granada_types_init(mrb, mod, native);
  mrb_granada_context_init(mrb, mod, native);
}

void
mrb_mruby_granada_gem_final(mrb_state *mrb)
{
  (void)mrb;
}
