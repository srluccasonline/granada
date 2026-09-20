/*
 * Granada value types: Vec2, Rect, Color, ColorF, Image.
 * Native constructors (nk_vec2, nk_rgb, …) live here too.
 */
#include "granada.h"

#include <stdio.h>
#include <string.h>

static struct RClass *cVec2;
static struct RClass *cRect;
static struct RClass *cColor;
static struct RClass *cColorF;
static struct RClass *cImage;

static void
value_free(mrb_state *mrb, void *ptr)
{
  mrb_free(mrb, ptr);
}

const struct mrb_data_type granada_vec2_type   = { "Granada::Vec2",   value_free };
const struct mrb_data_type granada_rect_type   = { "Granada::Rect",   value_free };
const struct mrb_data_type granada_color_type  = { "Granada::Color",  value_free };
const struct mrb_data_type granada_colorf_type = { "Granada::ColorF", value_free };
const struct mrb_data_type granada_image_type  = { "Granada::Image",  value_free };

static void *
alloc_copy(mrb_state *mrb, const void *src, size_t n)
{
  void *p = mrb_malloc(mrb, n);
  memcpy(p, src, n);
  return p;
}

mrb_value
granada_vec2_wrap(mrb_state *mrb, struct nk_vec2 v)
{
  struct nk_vec2 *p = (struct nk_vec2 *)alloc_copy(mrb, &v, sizeof(v));
  return mrb_obj_value(Data_Wrap_Struct(mrb, cVec2, &granada_vec2_type, p));
}

struct nk_vec2
granada_vec2_get(mrb_state *mrb, mrb_value obj)
{
  struct nk_vec2 *p = (struct nk_vec2 *)mrb_data_get_ptr(mrb, obj, &granada_vec2_type);
  if (!p) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized Granada::Vec2");
  }
  return *p;
}

mrb_value
granada_rect_wrap(mrb_state *mrb, struct nk_rect r)
{
  struct nk_rect *p = (struct nk_rect *)alloc_copy(mrb, &r, sizeof(r));
  return mrb_obj_value(Data_Wrap_Struct(mrb, cRect, &granada_rect_type, p));
}

struct nk_rect
granada_rect_get(mrb_state *mrb, mrb_value obj)
{
  struct nk_rect *p = (struct nk_rect *)mrb_data_get_ptr(mrb, obj, &granada_rect_type);
  if (!p) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized Granada::Rect");
  }
  return *p;
}

mrb_value
granada_color_wrap(mrb_state *mrb, struct nk_color c)
{
  struct nk_color *p = (struct nk_color *)alloc_copy(mrb, &c, sizeof(c));
  return mrb_obj_value(Data_Wrap_Struct(mrb, cColor, &granada_color_type, p));
}

struct nk_color
granada_color_get(mrb_state *mrb, mrb_value obj)
{
  struct nk_color *p = (struct nk_color *)mrb_data_get_ptr(mrb, obj, &granada_color_type);
  if (!p) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized Granada::Color");
  }
  return *p;
}

mrb_value
granada_colorf_wrap(mrb_state *mrb, struct nk_colorf c)
{
  struct nk_colorf *p = (struct nk_colorf *)alloc_copy(mrb, &c, sizeof(c));
  return mrb_obj_value(Data_Wrap_Struct(mrb, cColorF, &granada_colorf_type, p));
}

struct nk_colorf
granada_colorf_get(mrb_state *mrb, mrb_value obj)
{
  struct nk_colorf *p = (struct nk_colorf *)mrb_data_get_ptr(mrb, obj, &granada_colorf_type);
  if (!p) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized Granada::ColorF");
  }
  return *p;
}

mrb_value
granada_image_wrap(mrb_state *mrb, struct nk_image img)
{
  struct nk_image *p = (struct nk_image *)alloc_copy(mrb, &img, sizeof(img));
  return mrb_obj_value(Data_Wrap_Struct(mrb, cImage, &granada_image_type, p));
}

struct nk_image
granada_image_get(mrb_state *mrb, mrb_value obj)
{
  struct nk_image *p = (struct nk_image *)mrb_data_get_ptr(mrb, obj, &granada_image_type);
  if (!p) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized Granada::Image");
  }
  return *p;
}

static void
replace_data(mrb_state *mrb, mrb_value self, const struct mrb_data_type *type, void *p)
{
  void *old = DATA_PTR(self);
  if (old) {
    type->dfree(mrb, old);
  }
  mrb_data_init(self, p, type);
}

/* --- Vec2 --- */

static mrb_value
vec2_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float x = 0, y = 0;
  struct nk_vec2 v;
  struct nk_vec2 *p;

  mrb_get_args(mrb, "|ff", &x, &y);
  v = nk_vec2((float)x, (float)y);
  p = (struct nk_vec2 *)alloc_copy(mrb, &v, sizeof(v));
  replace_data(mrb, self, &granada_vec2_type, p);
  return self;
}

static mrb_value
vec2_x(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, granada_vec2_get(mrb, self).x);
}

static mrb_value
vec2_y(mrb_state *mrb, mrb_value self)
{
  return mrb_float_value(mrb, granada_vec2_get(mrb, self).y);
}

static mrb_value
vec2_set_x(mrb_state *mrb, mrb_value self)
{
  mrb_float x;
  struct nk_vec2 *p;

  mrb_get_args(mrb, "f", &x);
  p = (struct nk_vec2 *)mrb_data_get_ptr(mrb, self, &granada_vec2_type);
  if (!p) mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized Granada::Vec2");
  p->x = (float)x;
  return mrb_float_value(mrb, p->x);
}

static mrb_value
vec2_set_y(mrb_state *mrb, mrb_value self)
{
  mrb_float y;
  struct nk_vec2 *p;

  mrb_get_args(mrb, "f", &y);
  p = (struct nk_vec2 *)mrb_data_get_ptr(mrb, self, &granada_vec2_type);
  if (!p) mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized Granada::Vec2");
  p->y = (float)y;
  return mrb_float_value(mrb, p->y);
}

static mrb_value
vec2_to_a(mrb_state *mrb, mrb_value self)
{
  struct nk_vec2 v = granada_vec2_get(mrb, self);
  mrb_value a = mrb_ary_new_capa(mrb, 2);
  mrb_ary_push(mrb, a, mrb_float_value(mrb, v.x));
  mrb_ary_push(mrb, a, mrb_float_value(mrb, v.y));
  return a;
}

static mrb_value
vec2_eq(mrb_state *mrb, mrb_value self)
{
  mrb_value other;
  struct nk_vec2 a, b;

  mrb_get_args(mrb, "o", &other);
  if (!mrb_data_p(other) || DATA_TYPE(other) != &granada_vec2_type) {
    return mrb_false_value();
  }
  a = granada_vec2_get(mrb, self);
  b = granada_vec2_get(mrb, other);
  return mrb_bool_value(a.x == b.x && a.y == b.y);
}

static mrb_value
vec2_inspect(mrb_state *mrb, mrb_value self)
{
  struct nk_vec2 v = granada_vec2_get(mrb, self);
  char buf[80];
  snprintf(buf, sizeof(buf), "#<Granada::Vec2 x=%g y=%g>", v.x, v.y);
  return mrb_str_new_cstr(mrb, buf);
}

/* --- Rect --- */

static mrb_value
rect_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float x = 0, y = 0, w = 0, h = 0;
  struct nk_rect r;
  struct nk_rect *p;

  mrb_get_args(mrb, "|ffff", &x, &y, &w, &h);
  r = nk_rect((float)x, (float)y, (float)w, (float)h);
  p = (struct nk_rect *)alloc_copy(mrb, &r, sizeof(r));
  replace_data(mrb, self, &granada_rect_type, p);
  return self;
}

static mrb_value
rect_x(mrb_state *mrb, mrb_value self) { return mrb_float_value(mrb, granada_rect_get(mrb, self).x); }
static mrb_value
rect_y(mrb_state *mrb, mrb_value self) { return mrb_float_value(mrb, granada_rect_get(mrb, self).y); }
static mrb_value
rect_w(mrb_state *mrb, mrb_value self) { return mrb_float_value(mrb, granada_rect_get(mrb, self).w); }
static mrb_value
rect_h(mrb_state *mrb, mrb_value self) { return mrb_float_value(mrb, granada_rect_get(mrb, self).h); }

static mrb_value
rect_set_field(mrb_state *mrb, mrb_value self, int which)
{
  mrb_float v;
  struct nk_rect *p;

  mrb_get_args(mrb, "f", &v);
  p = (struct nk_rect *)mrb_data_get_ptr(mrb, self, &granada_rect_type);
  if (!p) mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized Granada::Rect");
  switch (which) {
    case 0: p->x = (float)v; break;
    case 1: p->y = (float)v; break;
    case 2: p->w = (float)v; break;
    default: p->h = (float)v; break;
  }
  return mrb_float_value(mrb, v);
}

static mrb_value rect_set_x(mrb_state *mrb, mrb_value self) { return rect_set_field(mrb, self, 0); }
static mrb_value rect_set_y(mrb_state *mrb, mrb_value self) { return rect_set_field(mrb, self, 1); }
static mrb_value rect_set_w(mrb_state *mrb, mrb_value self) { return rect_set_field(mrb, self, 2); }
static mrb_value rect_set_h(mrb_state *mrb, mrb_value self) { return rect_set_field(mrb, self, 3); }

static mrb_value
rect_pos(mrb_state *mrb, mrb_value self)
{
  return granada_vec2_wrap(mrb, nk_rect_pos(granada_rect_get(mrb, self)));
}

static mrb_value
rect_size(mrb_state *mrb, mrb_value self)
{
  return granada_vec2_wrap(mrb, nk_rect_size(granada_rect_get(mrb, self)));
}

static mrb_value
rect_to_a(mrb_state *mrb, mrb_value self)
{
  struct nk_rect r = granada_rect_get(mrb, self);
  mrb_value a = mrb_ary_new_capa(mrb, 4);
  mrb_ary_push(mrb, a, mrb_float_value(mrb, r.x));
  mrb_ary_push(mrb, a, mrb_float_value(mrb, r.y));
  mrb_ary_push(mrb, a, mrb_float_value(mrb, r.w));
  mrb_ary_push(mrb, a, mrb_float_value(mrb, r.h));
  return a;
}

static mrb_value
rect_eq(mrb_state *mrb, mrb_value self)
{
  mrb_value other;
  struct nk_rect a, b;

  mrb_get_args(mrb, "o", &other);
  if (!mrb_data_p(other) || DATA_TYPE(other) != &granada_rect_type) {
    return mrb_false_value();
  }
  a = granada_rect_get(mrb, self);
  b = granada_rect_get(mrb, other);
  return mrb_bool_value(a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.h);
}

static mrb_value
rect_inspect(mrb_state *mrb, mrb_value self)
{
  struct nk_rect r = granada_rect_get(mrb, self);
  char buf[96];
  snprintf(buf, sizeof(buf), "#<Granada::Rect x=%g y=%g w=%g h=%g>", r.x, r.y, r.w, r.h);
  return mrb_str_new_cstr(mrb, buf);
}

/* --- Color --- */

static nk_byte
clamp_byte(mrb_int n)
{
  if (n < 0) return 0;
  if (n > 255) return 255;
  return (nk_byte)n;
}

static mrb_value
color_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_int r = 0, g = 0, b = 0, a = 255;
  struct nk_color c;
  struct nk_color *p;

  mrb_get_args(mrb, "|iiii", &r, &g, &b, &a);
  c = nk_rgba((int)r, (int)g, (int)b, (int)a);
  p = (struct nk_color *)alloc_copy(mrb, &c, sizeof(c));
  replace_data(mrb, self, &granada_color_type, p);
  return self;
}

static mrb_value color_r(mrb_state *mrb, mrb_value self) { return mrb_fixnum_value(granada_color_get(mrb, self).r); }
static mrb_value color_g(mrb_state *mrb, mrb_value self) { return mrb_fixnum_value(granada_color_get(mrb, self).g); }
static mrb_value color_b(mrb_state *mrb, mrb_value self) { return mrb_fixnum_value(granada_color_get(mrb, self).b); }
static mrb_value color_a(mrb_state *mrb, mrb_value self) { return mrb_fixnum_value(granada_color_get(mrb, self).a); }

static mrb_value
color_set_field(mrb_state *mrb, mrb_value self, int which)
{
  mrb_int n;
  struct nk_color *p;

  mrb_get_args(mrb, "i", &n);
  p = (struct nk_color *)mrb_data_get_ptr(mrb, self, &granada_color_type);
  if (!p) mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized Granada::Color");
  switch (which) {
    case 0: p->r = clamp_byte(n); return mrb_fixnum_value(p->r);
    case 1: p->g = clamp_byte(n); return mrb_fixnum_value(p->g);
    case 2: p->b = clamp_byte(n); return mrb_fixnum_value(p->b);
    default: p->a = clamp_byte(n); return mrb_fixnum_value(p->a);
  }
}

static mrb_value color_set_r(mrb_state *mrb, mrb_value self) { return color_set_field(mrb, self, 0); }
static mrb_value color_set_g(mrb_state *mrb, mrb_value self) { return color_set_field(mrb, self, 1); }
static mrb_value color_set_b(mrb_state *mrb, mrb_value self) { return color_set_field(mrb, self, 2); }
static mrb_value color_set_a(mrb_state *mrb, mrb_value self) { return color_set_field(mrb, self, 3); }

static mrb_value
color_to_a(mrb_state *mrb, mrb_value self)
{
  struct nk_color c = granada_color_get(mrb, self);
  mrb_value a = mrb_ary_new_capa(mrb, 4);
  mrb_ary_push(mrb, a, mrb_fixnum_value(c.r));
  mrb_ary_push(mrb, a, mrb_fixnum_value(c.g));
  mrb_ary_push(mrb, a, mrb_fixnum_value(c.b));
  mrb_ary_push(mrb, a, mrb_fixnum_value(c.a));
  return a;
}

static mrb_value
color_to_u32(mrb_state *mrb, mrb_value self)
{
  return mrb_int_value(mrb, (mrb_int)nk_color_u32(granada_color_get(mrb, self)));
}

static mrb_value
color_hex(mrb_state *mrb, mrb_value self)
{
  char buf[8];
  nk_color_hex_rgb(buf, granada_color_get(mrb, self));
  return mrb_str_new_cstr(mrb, buf);
}

static mrb_value
color_hex_rgba(mrb_state *mrb, mrb_value self)
{
  char buf[10];
  nk_color_hex_rgba(buf, granada_color_get(mrb, self));
  return mrb_str_new_cstr(mrb, buf);
}

static mrb_value
color_to_colorf(mrb_state *mrb, mrb_value self)
{
  return granada_colorf_wrap(mrb, nk_color_cf(granada_color_get(mrb, self)));
}

static mrb_value
color_eq(mrb_state *mrb, mrb_value self)
{
  mrb_value other;
  struct nk_color a, b;

  mrb_get_args(mrb, "o", &other);
  if (!mrb_data_p(other) || DATA_TYPE(other) != &granada_color_type) {
    return mrb_false_value();
  }
  a = granada_color_get(mrb, self);
  b = granada_color_get(mrb, other);
  return mrb_bool_value(a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a);
}

static mrb_value
color_inspect(mrb_state *mrb, mrb_value self)
{
  struct nk_color c = granada_color_get(mrb, self);
  char buf[80];
  snprintf(buf, sizeof(buf), "#<Granada::Color r=%u g=%u b=%u a=%u>",
           (unsigned)c.r, (unsigned)c.g, (unsigned)c.b, (unsigned)c.a);
  return mrb_str_new_cstr(mrb, buf);
}

static mrb_value
color_s_rgb(mrb_state *mrb, mrb_value self)
{
  mrb_int r, g, b;
  (void)self;
  mrb_get_args(mrb, "iii", &r, &g, &b);
  return granada_color_wrap(mrb, nk_rgb((int)r, (int)g, (int)b));
}

static mrb_value
color_s_rgba(mrb_state *mrb, mrb_value self)
{
  mrb_int r, g, b, a = 255;
  (void)self;
  mrb_get_args(mrb, "iii|i", &r, &g, &b, &a);
  return granada_color_wrap(mrb, nk_rgba((int)r, (int)g, (int)b, (int)a));
}

static mrb_value
color_s_hex(mrb_state *mrb, mrb_value self)
{
  char *s;
  (void)self;
  mrb_get_args(mrb, "z", &s);
  return granada_color_wrap(mrb, nk_rgba_hex(s));
}

/* --- ColorF --- */

static mrb_value
colorf_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_float r = 0, g = 0, b = 0, a = 1.0;
  struct nk_colorf c;
  struct nk_colorf *p;

  mrb_get_args(mrb, "|ffff", &r, &g, &b, &a);
  c.r = (float)r; c.g = (float)g; c.b = (float)b; c.a = (float)a;
  p = (struct nk_colorf *)alloc_copy(mrb, &c, sizeof(c));
  replace_data(mrb, self, &granada_colorf_type, p);
  return self;
}

static mrb_value colorf_r(mrb_state *mrb, mrb_value self) { return mrb_float_value(mrb, granada_colorf_get(mrb, self).r); }
static mrb_value colorf_g(mrb_state *mrb, mrb_value self) { return mrb_float_value(mrb, granada_colorf_get(mrb, self).g); }
static mrb_value colorf_b(mrb_state *mrb, mrb_value self) { return mrb_float_value(mrb, granada_colorf_get(mrb, self).b); }
static mrb_value colorf_a(mrb_state *mrb, mrb_value self) { return mrb_float_value(mrb, granada_colorf_get(mrb, self).a); }

static mrb_value
colorf_to_color(mrb_state *mrb, mrb_value self)
{
  return granada_color_wrap(mrb, nk_rgba_cf(granada_colorf_get(mrb, self)));
}

static mrb_value
colorf_eq(mrb_state *mrb, mrb_value self)
{
  mrb_value other;
  struct nk_colorf a, b;

  mrb_get_args(mrb, "o", &other);
  if (!mrb_data_p(other) || DATA_TYPE(other) != &granada_colorf_type) {
    return mrb_false_value();
  }
  a = granada_colorf_get(mrb, self);
  b = granada_colorf_get(mrb, other);
  return mrb_bool_value(a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a);
}

static mrb_value
colorf_inspect(mrb_state *mrb, mrb_value self)
{
  struct nk_colorf c = granada_colorf_get(mrb, self);
  char buf[96];
  snprintf(buf, sizeof(buf), "#<Granada::ColorF r=%g g=%g b=%g a=%g>", c.r, c.g, c.b, c.a);
  return mrb_str_new_cstr(mrb, buf);
}

/* --- Image --- */

static mrb_value
image_s_id(mrb_state *mrb, mrb_value self)
{
  mrb_int id;
  (void)self;
  mrb_get_args(mrb, "i", &id);
  return granada_image_wrap(mrb, nk_image_id((int)id));
}

static mrb_value
image_w(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(granada_image_get(mrb, self).w);
}

static mrb_value
image_h(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(granada_image_get(mrb, self).h);
}

static mrb_value
image_id(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value(granada_image_get(mrb, self).handle.id);
}

static mrb_value
image_subimage(mrb_state *mrb, mrb_value self)
{
  struct nk_image img = granada_image_get(mrb, self);
  return mrb_bool_value(nk_image_is_subimage(&img));
}

/* --- Native constructors (1:1 with nk_*) --- */

static mrb_value native_vec2(mrb_state *mrb, mrb_value self)
{
  mrb_float x, y;
  (void)self;
  mrb_get_args(mrb, "ff", &x, &y);
  return granada_vec2_wrap(mrb, nk_vec2((float)x, (float)y));
}

static mrb_value native_vec2i(mrb_state *mrb, mrb_value self)
{
  mrb_int x, y;
  (void)self;
  mrb_get_args(mrb, "ii", &x, &y);
  return granada_vec2_wrap(mrb, nk_vec2i((int)x, (int)y));
}

static mrb_value native_rect(mrb_state *mrb, mrb_value self)
{
  mrb_float x, y, w, h;
  (void)self;
  mrb_get_args(mrb, "ffff", &x, &y, &w, &h);
  return granada_rect_wrap(mrb, nk_rect((float)x, (float)y, (float)w, (float)h));
}

static mrb_value native_recti(mrb_state *mrb, mrb_value self)
{
  mrb_int x, y, w, h;
  (void)self;
  mrb_get_args(mrb, "iiii", &x, &y, &w, &h);
  return granada_rect_wrap(mrb, nk_recti((int)x, (int)y, (int)w, (int)h));
}

static mrb_value native_recta(mrb_state *mrb, mrb_value self)
{
  mrb_value pos, size;
  (void)self;
  mrb_get_args(mrb, "oo", &pos, &size);
  return granada_rect_wrap(mrb, nk_recta(granada_vec2_get(mrb, pos), granada_vec2_get(mrb, size)));
}

static mrb_value native_null_rect(mrb_state *mrb, mrb_value self)
{
  (void)mrb; (void)self;
  return granada_rect_wrap(mrb, nk_get_null_rect());
}

static mrb_value native_rect_pos(mrb_state *mrb, mrb_value self)
{
  mrb_value r;
  (void)self;
  mrb_get_args(mrb, "o", &r);
  return granada_vec2_wrap(mrb, nk_rect_pos(granada_rect_get(mrb, r)));
}

static mrb_value native_rect_size(mrb_state *mrb, mrb_value self)
{
  mrb_value r;
  (void)self;
  mrb_get_args(mrb, "o", &r);
  return granada_vec2_wrap(mrb, nk_rect_size(granada_rect_get(mrb, r)));
}

static mrb_value native_rgb(mrb_state *mrb, mrb_value self)
{
  mrb_int r, g, b;
  (void)self;
  mrb_get_args(mrb, "iii", &r, &g, &b);
  return granada_color_wrap(mrb, nk_rgb((int)r, (int)g, (int)b));
}

static mrb_value native_rgba(mrb_state *mrb, mrb_value self)
{
  mrb_int r, g, b, a = 255;
  (void)self;
  mrb_get_args(mrb, "iii|i", &r, &g, &b, &a);
  return granada_color_wrap(mrb, nk_rgba((int)r, (int)g, (int)b, (int)a));
}

static mrb_value native_rgb_f(mrb_state *mrb, mrb_value self)
{
  mrb_float r, g, b;
  (void)self;
  mrb_get_args(mrb, "fff", &r, &g, &b);
  return granada_color_wrap(mrb, nk_rgb_f((float)r, (float)g, (float)b));
}

static mrb_value native_rgba_f(mrb_state *mrb, mrb_value self)
{
  mrb_float r, g, b, a = 1.0;
  (void)self;
  mrb_get_args(mrb, "fff|f", &r, &g, &b, &a);
  return granada_color_wrap(mrb, nk_rgba_f((float)r, (float)g, (float)b, (float)a));
}

static mrb_value native_rgb_hex(mrb_state *mrb, mrb_value self)
{
  char *s;
  (void)self;
  mrb_get_args(mrb, "z", &s);
  return granada_color_wrap(mrb, nk_rgb_hex(s));
}

static mrb_value native_rgba_hex(mrb_state *mrb, mrb_value self)
{
  char *s;
  (void)self;
  mrb_get_args(mrb, "z", &s);
  return granada_color_wrap(mrb, nk_rgba_hex(s));
}

static mrb_value native_hsv(mrb_state *mrb, mrb_value self)
{
  mrb_int h, s, v;
  (void)self;
  mrb_get_args(mrb, "iii", &h, &s, &v);
  return granada_color_wrap(mrb, nk_hsv((int)h, (int)s, (int)v));
}

static mrb_value native_hsva(mrb_state *mrb, mrb_value self)
{
  mrb_int h, s, v, a = 255;
  (void)self;
  mrb_get_args(mrb, "iii|i", &h, &s, &v, &a);
  return granada_color_wrap(mrb, nk_hsva((int)h, (int)s, (int)v, (int)a));
}

static mrb_value native_hsv_f(mrb_state *mrb, mrb_value self)
{
  mrb_float h, s, v;
  (void)self;
  mrb_get_args(mrb, "fff", &h, &s, &v);
  return granada_color_wrap(mrb, nk_hsv_f((float)h, (float)s, (float)v));
}

static mrb_value native_hsva_f(mrb_state *mrb, mrb_value self)
{
  mrb_float h, s, v, a = 1.0;
  (void)self;
  mrb_get_args(mrb, "fff|f", &h, &s, &v, &a);
  return granada_color_wrap(mrb, nk_hsva_f((float)h, (float)s, (float)v, (float)a));
}

static mrb_value native_rgb_cf(mrb_state *mrb, mrb_value self)
{
  mrb_value c;
  (void)self;
  mrb_get_args(mrb, "o", &c);
  return granada_color_wrap(mrb, nk_rgb_cf(granada_colorf_get(mrb, c)));
}

static mrb_value native_rgba_cf(mrb_state *mrb, mrb_value self)
{
  mrb_value c;
  (void)self;
  mrb_get_args(mrb, "o", &c);
  return granada_color_wrap(mrb, nk_rgba_cf(granada_colorf_get(mrb, c)));
}

static mrb_value native_color_cf(mrb_state *mrb, mrb_value self)
{
  mrb_value c;
  (void)self;
  mrb_get_args(mrb, "o", &c);
  return granada_colorf_wrap(mrb, nk_color_cf(granada_color_get(mrb, c)));
}

static mrb_value native_color_u32(mrb_state *mrb, mrb_value self)
{
  mrb_value c;
  (void)self;
  mrb_get_args(mrb, "o", &c);
  return mrb_int_value(mrb, (mrb_int)nk_color_u32(granada_color_get(mrb, c)));
}

static mrb_value native_image_id(mrb_state *mrb, mrb_value self)
{
  mrb_int id;
  (void)self;
  mrb_get_args(mrb, "i", &id);
  return granada_image_wrap(mrb, nk_image_id((int)id));
}

static mrb_value native_rgb_factor(mrb_state *mrb, mrb_value self)
{
  mrb_value c;
  mrb_float factor;
  (void)self;
  mrb_get_args(mrb, "of", &c, &factor);
  return granada_color_wrap(mrb, nk_rgb_factor(granada_color_get(mrb, c), (float)factor));
}

static mrb_value native_rgba_u32(mrb_state *mrb, mrb_value self)
{
  mrb_int n;
  (void)self;
  mrb_get_args(mrb, "i", &n);
  return granada_color_wrap(mrb, nk_rgba_u32((nk_uint)n));
}

void
mrb_granada_types_init(mrb_state *mrb, struct RClass *mod, struct RClass *native)
{
  cVec2 = mrb_define_class_under(mrb, mod, "Vec2", mrb->object_class);
  MRB_SET_INSTANCE_TT(cVec2, MRB_TT_CDATA);
  mrb_define_method(mrb, cVec2, "initialize", vec2_initialize, MRB_ARGS_OPT(2));
  mrb_define_method(mrb, cVec2, "x", vec2_x, MRB_ARGS_NONE());
  mrb_define_method(mrb, cVec2, "y", vec2_y, MRB_ARGS_NONE());
  mrb_define_method(mrb, cVec2, "x=", vec2_set_x, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cVec2, "y=", vec2_set_y, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cVec2, "to_a", vec2_to_a, MRB_ARGS_NONE());
  mrb_define_method(mrb, cVec2, "==", vec2_eq, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cVec2, "inspect", vec2_inspect, MRB_ARGS_NONE());
  mrb_define_method(mrb, cVec2, "to_s", vec2_inspect, MRB_ARGS_NONE());

  cRect = mrb_define_class_under(mrb, mod, "Rect", mrb->object_class);
  MRB_SET_INSTANCE_TT(cRect, MRB_TT_CDATA);
  mrb_define_method(mrb, cRect, "initialize", rect_initialize, MRB_ARGS_OPT(4));
  mrb_define_method(mrb, cRect, "x", rect_x, MRB_ARGS_NONE());
  mrb_define_method(mrb, cRect, "y", rect_y, MRB_ARGS_NONE());
  mrb_define_method(mrb, cRect, "w", rect_w, MRB_ARGS_NONE());
  mrb_define_method(mrb, cRect, "h", rect_h, MRB_ARGS_NONE());
  mrb_define_method(mrb, cRect, "width", rect_w, MRB_ARGS_NONE());
  mrb_define_method(mrb, cRect, "height", rect_h, MRB_ARGS_NONE());
  mrb_define_method(mrb, cRect, "x=", rect_set_x, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cRect, "y=", rect_set_y, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cRect, "w=", rect_set_w, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cRect, "h=", rect_set_h, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cRect, "pos", rect_pos, MRB_ARGS_NONE());
  mrb_define_method(mrb, cRect, "size", rect_size, MRB_ARGS_NONE());
  mrb_define_method(mrb, cRect, "to_a", rect_to_a, MRB_ARGS_NONE());
  mrb_define_method(mrb, cRect, "==", rect_eq, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cRect, "inspect", rect_inspect, MRB_ARGS_NONE());
  mrb_define_method(mrb, cRect, "to_s", rect_inspect, MRB_ARGS_NONE());

  cColor = mrb_define_class_under(mrb, mod, "Color", mrb->object_class);
  MRB_SET_INSTANCE_TT(cColor, MRB_TT_CDATA);
  mrb_define_method(mrb, cColor, "initialize", color_initialize, MRB_ARGS_OPT(4));
  mrb_define_method(mrb, cColor, "r", color_r, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColor, "g", color_g, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColor, "b", color_b, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColor, "a", color_a, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColor, "r=", color_set_r, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cColor, "g=", color_set_g, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cColor, "b=", color_set_b, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cColor, "a=", color_set_a, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cColor, "to_a", color_to_a, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColor, "to_u32", color_to_u32, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColor, "hex", color_hex, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColor, "hex_rgba", color_hex_rgba, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColor, "to_colorf", color_to_colorf, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColor, "==", color_eq, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cColor, "inspect", color_inspect, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColor, "to_s", color_inspect, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, cColor, "rgb", color_s_rgb, MRB_ARGS_REQ(3));
  mrb_define_class_method(mrb, cColor, "rgba", color_s_rgba, MRB_ARGS_ARG(3, 1));
  mrb_define_class_method(mrb, cColor, "hex", color_s_hex, MRB_ARGS_REQ(1));

  cColorF = mrb_define_class_under(mrb, mod, "ColorF", mrb->object_class);
  MRB_SET_INSTANCE_TT(cColorF, MRB_TT_CDATA);
  mrb_define_method(mrb, cColorF, "initialize", colorf_initialize, MRB_ARGS_OPT(4));
  mrb_define_method(mrb, cColorF, "r", colorf_r, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColorF, "g", colorf_g, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColorF, "b", colorf_b, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColorF, "a", colorf_a, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColorF, "to_color", colorf_to_color, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColorF, "==", colorf_eq, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cColorF, "inspect", colorf_inspect, MRB_ARGS_NONE());
  mrb_define_method(mrb, cColorF, "to_s", colorf_inspect, MRB_ARGS_NONE());

  cImage = mrb_define_class_under(mrb, mod, "Image", mrb->object_class);
  MRB_SET_INSTANCE_TT(cImage, MRB_TT_CDATA);
  mrb_define_class_method(mrb, cImage, "id", image_s_id, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cImage, "w", image_w, MRB_ARGS_NONE());
  mrb_define_method(mrb, cImage, "h", image_h, MRB_ARGS_NONE());
  mrb_define_method(mrb, cImage, "id", image_id, MRB_ARGS_NONE());
  mrb_define_method(mrb, cImage, "subimage?", image_subimage, MRB_ARGS_NONE());

  mrb_define_module_function(mrb, native, "vec2", native_vec2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, native, "vec2i", native_vec2i, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, native, "rect", native_rect, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, native, "recti", native_recti, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, native, "recta", native_recta, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, native, "get_null_rect", native_null_rect, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, native, "rect_pos", native_rect_pos, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, native, "rect_size", native_rect_size, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, native, "rgb", native_rgb, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, native, "rgba", native_rgba, MRB_ARGS_ARG(3, 1));
  mrb_define_module_function(mrb, native, "rgb_f", native_rgb_f, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, native, "rgba_f", native_rgba_f, MRB_ARGS_ARG(3, 1));
  mrb_define_module_function(mrb, native, "rgb_hex", native_rgb_hex, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, native, "rgba_hex", native_rgba_hex, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, native, "hsv", native_hsv, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, native, "hsva", native_hsva, MRB_ARGS_ARG(3, 1));
  mrb_define_module_function(mrb, native, "hsv_f", native_hsv_f, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, native, "hsva_f", native_hsva_f, MRB_ARGS_ARG(3, 1));
  mrb_define_module_function(mrb, native, "rgb_cf", native_rgb_cf, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, native, "rgba_cf", native_rgba_cf, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, native, "color_cf", native_color_cf, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, native, "color_u32", native_color_u32, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, native, "rgb_factor", native_rgb_factor, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, native, "rgba_u32", native_rgba_u32, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, native, "image_id", native_image_id, MRB_ARGS_REQ(1));
}
