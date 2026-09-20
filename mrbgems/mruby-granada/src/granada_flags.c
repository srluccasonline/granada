/*
 * Granada flag/enum constants. Ruby names drop the NK_ prefix:
 *   NK_WINDOW_BORDER -> Granada::WINDOW_BORDER
 */
#include "granada.h"

static void
def_i(mrb_state *mrb, struct RClass *mod, const char *name, mrb_int value)
{
  mrb_define_const(mrb, mod, name, mrb_fixnum_value(value));
}

void
mrb_granada_flags_init(mrb_state *mrb, struct RClass *mod)
{
  def_i(mrb, mod, "WINDOW_BORDER", NK_WINDOW_BORDER);
  def_i(mrb, mod, "WINDOW_MOVABLE", NK_WINDOW_MOVABLE);
  def_i(mrb, mod, "WINDOW_SCALABLE", NK_WINDOW_SCALABLE);
  def_i(mrb, mod, "WINDOW_CLOSABLE", NK_WINDOW_CLOSABLE);
  def_i(mrb, mod, "WINDOW_MINIMIZABLE", NK_WINDOW_MINIMIZABLE);
  def_i(mrb, mod, "WINDOW_NO_SCROLLBAR", NK_WINDOW_NO_SCROLLBAR);
  def_i(mrb, mod, "WINDOW_TITLE", NK_WINDOW_TITLE);
  def_i(mrb, mod, "WINDOW_SCROLL_AUTO_HIDE", NK_WINDOW_SCROLL_AUTO_HIDE);
  def_i(mrb, mod, "WINDOW_BACKGROUND", NK_WINDOW_BACKGROUND);
  def_i(mrb, mod, "WINDOW_SCALE_LEFT", NK_WINDOW_SCALE_LEFT);
  def_i(mrb, mod, "WINDOW_NO_INPUT", NK_WINDOW_NO_INPUT);

  def_i(mrb, mod, "TEXT_ALIGN_LEFT", NK_TEXT_ALIGN_LEFT);
  def_i(mrb, mod, "TEXT_ALIGN_CENTERED", NK_TEXT_ALIGN_CENTERED);
  def_i(mrb, mod, "TEXT_ALIGN_RIGHT", NK_TEXT_ALIGN_RIGHT);
  def_i(mrb, mod, "TEXT_ALIGN_TOP", NK_TEXT_ALIGN_TOP);
  def_i(mrb, mod, "TEXT_ALIGN_MIDDLE", NK_TEXT_ALIGN_MIDDLE);
  def_i(mrb, mod, "TEXT_ALIGN_BOTTOM", NK_TEXT_ALIGN_BOTTOM);
  def_i(mrb, mod, "TEXT_LEFT", NK_TEXT_LEFT);
  def_i(mrb, mod, "TEXT_CENTERED", NK_TEXT_CENTERED);
  def_i(mrb, mod, "TEXT_RIGHT", NK_TEXT_RIGHT);

  def_i(mrb, mod, "KEY_NONE", NK_KEY_NONE);
  def_i(mrb, mod, "KEY_SHIFT", NK_KEY_SHIFT);
  def_i(mrb, mod, "KEY_CTRL", NK_KEY_CTRL);
  def_i(mrb, mod, "KEY_DEL", NK_KEY_DEL);
  def_i(mrb, mod, "KEY_ENTER", NK_KEY_ENTER);
  def_i(mrb, mod, "KEY_TAB", NK_KEY_TAB);
  def_i(mrb, mod, "KEY_BACKSPACE", NK_KEY_BACKSPACE);
  def_i(mrb, mod, "KEY_COPY", NK_KEY_COPY);
  def_i(mrb, mod, "KEY_CUT", NK_KEY_CUT);
  def_i(mrb, mod, "KEY_PASTE", NK_KEY_PASTE);
  def_i(mrb, mod, "KEY_UP", NK_KEY_UP);
  def_i(mrb, mod, "KEY_DOWN", NK_KEY_DOWN);
  def_i(mrb, mod, "KEY_LEFT", NK_KEY_LEFT);
  def_i(mrb, mod, "KEY_RIGHT", NK_KEY_RIGHT);
  def_i(mrb, mod, "KEY_TEXT_INSERT_MODE", NK_KEY_TEXT_INSERT_MODE);
  def_i(mrb, mod, "KEY_TEXT_REPLACE_MODE", NK_KEY_TEXT_REPLACE_MODE);
  def_i(mrb, mod, "KEY_TEXT_RESET_MODE", NK_KEY_TEXT_RESET_MODE);
  def_i(mrb, mod, "KEY_TEXT_LINE_START", NK_KEY_TEXT_LINE_START);
  def_i(mrb, mod, "KEY_TEXT_LINE_END", NK_KEY_TEXT_LINE_END);
  def_i(mrb, mod, "KEY_TEXT_START", NK_KEY_TEXT_START);
  def_i(mrb, mod, "KEY_TEXT_END", NK_KEY_TEXT_END);
  def_i(mrb, mod, "KEY_TEXT_UNDO", NK_KEY_TEXT_UNDO);
  def_i(mrb, mod, "KEY_TEXT_REDO", NK_KEY_TEXT_REDO);
  def_i(mrb, mod, "KEY_TEXT_SELECT_ALL", NK_KEY_TEXT_SELECT_ALL);
  def_i(mrb, mod, "KEY_TEXT_WORD_LEFT", NK_KEY_TEXT_WORD_LEFT);
  def_i(mrb, mod, "KEY_TEXT_WORD_RIGHT", NK_KEY_TEXT_WORD_RIGHT);
  def_i(mrb, mod, "KEY_SCROLL_START", NK_KEY_SCROLL_START);
  def_i(mrb, mod, "KEY_SCROLL_END", NK_KEY_SCROLL_END);
  def_i(mrb, mod, "KEY_SCROLL_DOWN", NK_KEY_SCROLL_DOWN);
  def_i(mrb, mod, "KEY_SCROLL_UP", NK_KEY_SCROLL_UP);
  def_i(mrb, mod, "KEY_ALT", NK_KEY_ALT);
  def_i(mrb, mod, "KEY_MAX", NK_KEY_MAX);

  def_i(mrb, mod, "MOUSE_LEFT", NK_BUTTON_LEFT);
  def_i(mrb, mod, "MOUSE_MIDDLE", NK_BUTTON_MIDDLE);
  def_i(mrb, mod, "MOUSE_RIGHT", NK_BUTTON_RIGHT);
  def_i(mrb, mod, "MOUSE_DOUBLE", NK_BUTTON_DOUBLE);
  def_i(mrb, mod, "MOUSE_X1", NK_BUTTON_X1);
  def_i(mrb, mod, "MOUSE_X2", NK_BUTTON_X2);

  def_i(mrb, mod, "UP", NK_UP);
  def_i(mrb, mod, "RIGHT", NK_RIGHT);
  def_i(mrb, mod, "DOWN", NK_DOWN);
  def_i(mrb, mod, "LEFT", NK_LEFT);

  def_i(mrb, mod, "BUTTON_DEFAULT", NK_BUTTON_DEFAULT);
  def_i(mrb, mod, "BUTTON_REPEATER", NK_BUTTON_REPEATER);

  def_i(mrb, mod, "FIXED", NK_FIXED);
  def_i(mrb, mod, "MODIFIABLE", NK_MODIFIABLE);
  def_i(mrb, mod, "VERTICAL", NK_VERTICAL);
  def_i(mrb, mod, "HORIZONTAL", NK_HORIZONTAL);
  def_i(mrb, mod, "MINIMIZED", NK_MINIMIZED);
  def_i(mrb, mod, "MAXIMIZED", NK_MAXIMIZED);
  def_i(mrb, mod, "HIDDEN", NK_HIDDEN);
  def_i(mrb, mod, "SHOWN", NK_SHOWN);

  def_i(mrb, mod, "CHART_LINES", NK_CHART_LINES);
  def_i(mrb, mod, "CHART_COLUMN", NK_CHART_COLUMN);
  def_i(mrb, mod, "CHART_HOVERING", NK_CHART_HOVERING);
  def_i(mrb, mod, "CHART_CLICKED", NK_CHART_CLICKED);

  def_i(mrb, mod, "RGB", NK_RGB);
  def_i(mrb, mod, "RGBA", NK_RGBA);
  def_i(mrb, mod, "POPUP_STATIC", NK_POPUP_STATIC);
  def_i(mrb, mod, "POPUP_DYNAMIC", NK_POPUP_DYNAMIC);
  def_i(mrb, mod, "DYNAMIC", NK_DYNAMIC);
  def_i(mrb, mod, "STATIC", NK_STATIC);
  def_i(mrb, mod, "TREE_NODE", NK_TREE_NODE);
  def_i(mrb, mod, "TREE_TAB", NK_TREE_TAB);

  def_i(mrb, mod, "SYMBOL_NONE", NK_SYMBOL_NONE);
  def_i(mrb, mod, "SYMBOL_X", NK_SYMBOL_X);
  def_i(mrb, mod, "SYMBOL_CIRCLE_SOLID", NK_SYMBOL_CIRCLE_SOLID);
  def_i(mrb, mod, "SYMBOL_CIRCLE_OUTLINE", NK_SYMBOL_CIRCLE_OUTLINE);
  def_i(mrb, mod, "SYMBOL_RECT_SOLID", NK_SYMBOL_RECT_SOLID);
  def_i(mrb, mod, "SYMBOL_RECT_OUTLINE", NK_SYMBOL_RECT_OUTLINE);
  def_i(mrb, mod, "SYMBOL_TRIANGLE_UP", NK_SYMBOL_TRIANGLE_UP);
  def_i(mrb, mod, "SYMBOL_TRIANGLE_DOWN", NK_SYMBOL_TRIANGLE_DOWN);
  def_i(mrb, mod, "SYMBOL_TRIANGLE_LEFT", NK_SYMBOL_TRIANGLE_LEFT);
  def_i(mrb, mod, "SYMBOL_TRIANGLE_RIGHT", NK_SYMBOL_TRIANGLE_RIGHT);
  def_i(mrb, mod, "SYMBOL_PLUS", NK_SYMBOL_PLUS);
  def_i(mrb, mod, "SYMBOL_MINUS", NK_SYMBOL_MINUS);
}
