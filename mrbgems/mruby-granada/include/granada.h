#ifndef GRANADA_H
#define GRANADA_H

#include "granada_config.h"
#include "nuklear.h"

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/error.h>
#include <mruby/numeric.h>
#include <mruby/string.h>

extern const struct mrb_data_type granada_vec2_type;
extern const struct mrb_data_type granada_rect_type;
extern const struct mrb_data_type granada_color_type;
extern const struct mrb_data_type granada_colorf_type;
extern const struct mrb_data_type granada_image_type;
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

struct nk_context *granada_context_ptr(mrb_state *mrb, mrb_value obj);

void mrb_granada_types_init(mrb_state *mrb, struct RClass *mod, struct RClass *native);
void mrb_granada_flags_init(mrb_state *mrb, struct RClass *mod);
void mrb_granada_context_init(mrb_state *mrb, struct RClass *mod, struct RClass *native);

#endif /* GRANADA_H */
