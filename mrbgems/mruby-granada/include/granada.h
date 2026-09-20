#ifndef GRANADA_H
#define GRANADA_H

#include "granada_config.h"
#include "nuklear.h"

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/error.h>
#include <mruby/gc.h>
#include <mruby/numeric.h>
#include <mruby/string.h>

extern const struct mrb_data_type granada_vec2_type;
extern const struct mrb_data_type granada_rect_type;
extern const struct mrb_data_type granada_color_type;
extern const struct mrb_data_type granada_colorf_type;
extern const struct mrb_data_type granada_image_type;
extern const struct mrb_data_type granada_nineslice_type;
extern const struct mrb_data_type granada_context_type;

mrb_value granada_vec2_wrap(mrb_state *mrb, struct nk_vec2 v);
struct nk_vec2 granada_vec2_get(mrb_state *mrb, mrb_value obj);

mrb_value granada_rect_wrap(mrb_state *mrb, struct nk_rect r);
struct nk_rect granada_rect_get(mrb_state *mrb, mrb_value obj);

mrb_value granada_color_wrap(mrb_state *mrb, struct nk_color c);
struct nk_color granada_color_get(mrb_state *mrb, mrb_value obj);

mrb_value granada_colorf_wrap(mrb_state *mrb, struct nk_colorf c);
struct nk_colorf granada_colorf_get(mrb_state *mrb, mrb_value obj);

mrb_value granada_image_wrap(mrb_state *mrb, struct nk_image img);
struct nk_image granada_image_get(mrb_state *mrb, mrb_value obj);

mrb_value granada_nineslice_wrap(mrb_state *mrb, struct nk_nine_slice s);
struct nk_nine_slice granada_nineslice_get(mrb_state *mrb, mrb_value obj);

typedef struct granada_ctx {
  struct nk_context nk;
  struct nk_context *nk_ext; /* non-NULL: wrap a host-owned context */
  int owned;                 /* 1: we nk_free + atlas_clear */
  struct nk_font_atlas atlas;
  struct nk_font *font;
  float *floats;
  int floats_cap;
} granada_ctx;

struct nk_context *granada_context_ptr(mrb_state *mrb, mrb_value obj);
granada_ctx *granada_ctx_get(mrb_state *mrb, mrb_value obj);
float *granada_ctx_floats(mrb_state *mrb, mrb_value obj, int n);
mrb_value granada_context_wrap_external(mrb_state *mrb, struct nk_context *nk);
mrb_value granada_yield(mrb_state *mrb, void *data);
mrb_value granada_open_block(mrb_state *mrb, struct nk_context *ctx, nk_bool open,
                             void (*endfn)(struct nk_context *), mrb_value blk);
void granada_define_native_fwd(mrb_state *mrb, struct RClass *native, const char *name, mrb_aspec spec);
void granada_define_native_fwds(mrb_state *mrb, struct RClass *native, const char **names);

nk_plugin_filter granada_filter_from(mrb_state *mrb, mrb_value v);

void mrb_granada_types_init(mrb_state *mrb, struct RClass *mod, struct RClass *native);
void mrb_granada_flags_init(mrb_state *mrb, struct RClass *mod);
void mrb_granada_context_init(mrb_state *mrb, struct RClass *mod, struct RClass *native);
void mrb_granada_input_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native);
void mrb_granada_window_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native);
void mrb_granada_layout_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native);
void mrb_granada_widgets_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native);
void mrb_granada_containers_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native);
void mrb_granada_style_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native);
void mrb_granada_canvas_init(mrb_state *mrb, struct RClass *ctx, struct RClass *native);
void mrb_granada_host_init(mrb_state *mrb, struct RClass *mod);

#endif /* GRANADA_H */
