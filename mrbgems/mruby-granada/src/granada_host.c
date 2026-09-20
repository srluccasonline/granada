/*
 * Optional GLFW + OpenGL 3 host. Compiles always; real window loop only if
 * GRANADA_HAS_GLFW (pkg-config glfw3 + glew at gem configure time).
 *
 * Granada::Host.run(title, width, height, vsync) { |ctx, w, h| ... }
 * Esc / Ctrl+Q / Cmd+Q request close. Host.quit! does the same from Ruby.
 */
#include "granada.h"
#include <stdio.h>
#include <string.h>

#ifndef GRANADA_HAS_GLFW

static mrb_value host_available(mrb_state *mrb, mrb_value self)
{ (void)mrb; (void)self; return mrb_false_value(); }

static mrb_value
host_run(mrb_state *mrb, mrb_value self)
{
  (void)self;
  mrb_raise(mrb, E_RUNTIME_ERROR,
            "Granada was built without GLFW (install glfw3 + glew and rebuild)");
  return mrb_nil_value();
}

static mrb_value host_quit(mrb_state *mrb, mrb_value self)
{ (void)mrb; (void)self; return mrb_nil_value(); }

static mrb_value host_size(mrb_state *mrb, mrb_value self)
{
  mrb_value a;
  (void)self;
  a = mrb_ary_new_capa(mrb, 2);
  mrb_ary_push(mrb, a, mrb_fixnum_value(0));
  mrb_ary_push(mrb, a, mrb_fixnum_value(0));
  return a;
}

static mrb_value
host_image(mrb_state *mrb, mrb_value self)
{
  (void)self;
  mrb_raise(mrb, E_RUNTIME_ERROR,
            "Granada was built without GLFW (install glfw3 + glew and rebuild)");
  return mrb_nil_value();
}

#else /* GRANADA_HAS_GLFW */

#define GLFW_INCLUDE_NONE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NK_GLFW_GL3_IMPLEMENTATION
#include "nuklear_glfw_gl3.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_ONLY_JPEG
#define STBI_NO_STDIO
#include "stb_image.h"

#define GRANADA_MAX_VERTEX_BUFFER   (512 * 1024)
#define GRANADA_MAX_ELEMENT_BUFFER  (128 * 1024)
#define GRANADA_MAX_IMAGES          64

static struct nk_glfw g_glfw;
static GLFWwindow *g_win;
static int g_quit;
static GLuint g_images[GRANADA_MAX_IMAGES];
static int g_image_n;

static void
host_free_images(void)
{
  if (g_image_n > 0) {
    glDeleteTextures((GLsizei)g_image_n, g_images);
  }
  g_image_n = 0;
}

static void
host_error(int code, const char *desc)
{
  (void)code;
  fprintf(stderr, "GLFW: %s\n", desc);
}

static mrb_value host_available(mrb_state *mrb, mrb_value self)
{ (void)mrb; (void)self; return mrb_true_value(); }

static mrb_value host_quit(mrb_state *mrb, mrb_value self)
{
  (void)mrb; (void)self;
  g_quit = 1;
  if (g_win) glfwSetWindowShouldClose(g_win, GLFW_TRUE);
  return mrb_nil_value();
}

static mrb_value host_size(mrb_state *mrb, mrb_value self)
{
  int w = 0, h = 0;
  mrb_value a;
  (void)self;
  if (g_win) glfwGetWindowSize(g_win, &w, &h);
  a = mrb_ary_new_capa(mrb, 2);
  mrb_ary_push(mrb, a, mrb_int_value(mrb, w));
  mrb_ary_push(mrb, a, mrb_int_value(mrb, h));
  return a;
}

static mrb_value
host_image(mrb_state *mrb, mrb_value self)
{
  mrb_value path_v;
  const char *path;
  FILE *fp;
  unsigned char *filebuf = 0, *pixels;
  long flen;
  int w = 0, h = 0, n = 0;
  GLuint tex;
  struct nk_image img;

  (void)self;
  if (!g_win) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Host.image requires an active Granada.app window");
  }
  mrb_get_args(mrb, "o", &path_v);
  path = mrb_string_cstr(mrb, path_v);
  fp = fopen(path, "rb");
  if (!fp) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "cannot open image '%s'", path);
  }
  fseek(fp, 0, SEEK_END);
  flen = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  if (flen <= 0) {
    fclose(fp);
    mrb_raisef(mrb, E_RUNTIME_ERROR, "empty image '%s'", path);
  }
  filebuf = (unsigned char *)mrb_malloc(mrb, (size_t)flen);
  if (fread(filebuf, 1, (size_t)flen, fp) != (size_t)flen) {
    fclose(fp);
    mrb_free(mrb, filebuf);
    mrb_raisef(mrb, E_RUNTIME_ERROR, "failed to read image '%s'", path);
  }
  fclose(fp);
  pixels = stbi_load_from_memory(filebuf, (int)flen, &w, &h, &n, 4);
  mrb_free(mrb, filebuf);
  if (!pixels) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "cannot decode image '%s'", path);
  }
  if (g_image_n >= GRANADA_MAX_IMAGES) {
    stbi_image_free(pixels);
    mrb_raise(mrb, E_RUNTIME_ERROR, "too many Host.image textures");
  }
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
  stbi_image_free(pixels);
  g_images[g_image_n++] = tex;
  img = nk_image_id((int)tex);
  img.w = (nk_ushort)w;
  img.h = (nk_ushort)h;
  return granada_image_wrap(mrb, img);
}

typedef struct host_loop {
  mrb_value blk;
  mrb_value ctx_obj;
} host_loop;

static mrb_value
host_loop_body(mrb_state *mrb, void *data)
{
  host_loop *loop = (host_loop *)data;
  struct nk_context *nk = granada_context_ptr(mrb, loop->ctx_obj);

  while (g_win && !glfwWindowShouldClose(g_win) && !g_quit) {
    int w = 0, h = 0, fw = 0, fh = 0;
    mrb_value args[3];

    glfwPollEvents();
    if ((glfwGetKey(g_win, GLFW_KEY_ESCAPE) == GLFW_PRESS) ||
        ((glfwGetKey(g_win, GLFW_KEY_Q) == GLFW_PRESS) &&
         (glfwGetKey(g_win, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
          glfwGetKey(g_win, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS ||
          glfwGetKey(g_win, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS ||
          glfwGetKey(g_win, GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS))) {
      glfwSetWindowShouldClose(g_win, GLFW_TRUE);
      break;
    }

    glfwGetWindowSize(g_win, &w, &h);
    glfwGetFramebufferSize(g_win, &fw, &fh);
    nk_glfw3_new_frame(&g_glfw);

    args[0] = loop->ctx_obj;
    args[1] = mrb_int_value(mrb, w);
    args[2] = mrb_int_value(mrb, h);
    mrb_yield_argv(mrb, loop->blk, 3, args);

    glViewport(0, 0, fw, fh);
    glClearColor(0.10f, 0.10f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    nk_glfw3_render(&g_glfw, NK_ANTI_ALIASING_ON, GRANADA_MAX_VERTEX_BUFFER, GRANADA_MAX_ELEMENT_BUFFER);
    glfwSwapBuffers(g_win);
    nk_clear(nk);
  }
  return mrb_nil_value();
}

static mrb_value
host_run(mrb_state *mrb, mrb_value self)
{
  mrb_value title_v, blk, font_path = mrb_nil_value();
  mrb_int width = 800, height = 600;
  mrb_bool vsync = TRUE;
  mrb_float font_size = 13.0;
  const char *title;
  struct nk_context *nk;
  struct nk_font_atlas *atlas;
  struct nk_font *ui_font;
  mrb_value ctx_obj;
  mrb_value result;
  host_loop loop;

  (void)self;
  mrb_get_args(mrb, "o|iibof&", &title_v, &width, &height, &vsync, &font_path, &font_size, &blk);
  if (mrb_nil_p(blk)) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Granada::Host.run requires a block");
  }
  title = mrb_string_cstr(mrb, title_v);
  if (width < 64) width = 64;
  if (height < 64) height = 64;

  memset(&g_glfw, 0, sizeof(g_glfw));
  g_win = NULL;
  g_quit = 0;
  g_image_n = 0;

  glfwSetErrorCallback(host_error);
  if (!glfwInit()) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "glfwInit failed");
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  g_win = glfwCreateWindow((int)width, (int)height, title, NULL, NULL);
  if (!g_win) {
    glfwTerminate();
    mrb_raise(mrb, E_RUNTIME_ERROR, "glfwCreateWindow failed");
  }
  glfwMakeContextCurrent(g_win);
  glfwSwapInterval(vsync ? 1 : 0);
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    glfwDestroyWindow(g_win);
    g_win = NULL;
    glfwTerminate();
    mrb_raise(mrb, E_RUNTIME_ERROR, "glewInit failed");
  }

  nk = nk_glfw3_init(&g_glfw, g_win, NK_GLFW3_INSTALL_CALLBACKS);
  nk_glfw3_font_stash_begin(&g_glfw, &atlas);
  if (!mrb_nil_p(font_path)) {
    const char *fp = mrb_string_cstr(mrb, font_path);
    float px = (font_size > 0) ? (float)font_size : 13.0f;
    ui_font = nk_font_atlas_add_from_file(atlas, fp, px, 0);
    if (!ui_font) {
      nk_glfw3_shutdown(&g_glfw);
      glfwDestroyWindow(g_win);
      g_win = NULL;
      glfwTerminate();
      mrb_raisef(mrb, E_RUNTIME_ERROR, "cannot load font '%s'", fp);
    }
  } else {
    float px = (font_size > 0) ? (float)font_size : 13.0f;
    ui_font = nk_font_atlas_add_default(atlas, px, 0);
  }
  nk_glfw3_font_stash_end(&g_glfw);
  if (ui_font) nk_style_set_font(nk, &ui_font->handle);

  ctx_obj = granada_context_wrap_external(mrb, nk);
  mrb_gc_register(mrb, ctx_obj);
  mrb_gc_register(mrb, blk);
  loop.blk = blk;
  loop.ctx_obj = ctx_obj;

  MRB_ENSURE(mrb, result, host_loop_body, &loop) {
    mrb_gc_unregister(mrb, ctx_obj);
    mrb_gc_unregister(mrb, blk);
    host_free_images();
    nk_glfw3_shutdown(&g_glfw);
    if (g_win) glfwDestroyWindow(g_win);
    g_win = NULL;
    glfwTerminate();
    memset(&g_glfw, 0, sizeof(g_glfw));
    g_quit = 0;
  }
  return result;
}

#endif /* GRANADA_HAS_GLFW */

void
mrb_granada_host_init(mrb_state *mrb, struct RClass *mod)
{
  struct RClass *host = mrb_define_module_under(mrb, mod, "Host");
  mrb_define_module_function(mrb, host, "available?", host_available, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, host, "run", host_run, MRB_ARGS_ARG(1, 5) | MRB_ARGS_BLOCK());
  mrb_define_module_function(mrb, host, "quit!", host_quit, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, host, "size", host_size, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, host, "image", host_image, MRB_ARGS_REQ(1));
}
