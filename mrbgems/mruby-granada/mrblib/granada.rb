# Granada — Nuklear bindings for mruby 4.x
#
# VERSION and NUKLEAR_VERSION are defined from C (granada_core.c) so they
# stay in sync with granada_config.h. This file is the Ruby-side surface:
# Native 1:1 wrappers grow under Granada::Native; the idiomatic DSL lands
# in Granada::UI / Granada.app in later phases.

module Granada
  # Immediate-mode UI builder. Blocks passed to Granada.app / #window will
  # be instance_eval'd here once the host and DSL are in place.
  class UI
  end
end
