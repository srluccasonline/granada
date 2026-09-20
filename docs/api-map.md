# API map — Nuklear v4.13.3 → Granada

Gerado por `tools/inventory_nuklear.rb` a partir de `vendor/nuklear/nuklear.h`.
Não edite a tabela de funções à mão: rode `make inventory` de novo depois de atualizar o header.
Status: `unbound` (ainda não ligado), `native` (Granada::Native), `dsl` (também na DSL), `skip` (proposital).

- Funções `NK_API`: **552** (540 para bind, 12 skip vararg/printf)
- Enums nomeados: **55**
- Structs nomeados: **159**

## Status global

| Seção | Funções | unbound | native | dsl | skip |
|---|---:|---:|---:|---:|---:|
| Api | 0 | 0 | 0 | 0 | 0 |
| Context | 7 | 4 | 3 | 0 | 0 |
| Input | 30 | 22 | 8 | 0 | 0 |
| Drawing | 25 | 25 | 0 | 0 | 0 |
| Window | 34 | 4 | 30 | 0 | 0 |
| Layout | 24 | 0 | 24 | 0 | 0 |
| Group | 8 | 3 | 5 | 0 | 0 |
| Tree | 9 | 4 | 5 | 0 | 0 |
| List View | 2 | 2 | 0 | 0 | 0 |
| Widget | 12 | 1 | 11 | 0 | 0 |
| Text | 25 | 2 | 15 | 0 | 8 |
| Link | 12 | 11 | 1 | 0 | 0 |
| Button | 20 | 10 | 10 | 0 | 0 |
| Checkbox | 11 | 8 | 3 | 0 | 0 |
| Radio Button | 8 | 6 | 2 | 0 | 0 |
| Selectable | 12 | 10 | 2 | 0 | 0 |
| Slider | 4 | 0 | 4 | 0 | 0 |
| Knob | 2 | 1 | 1 | 0 | 0 |
| Progressbar | 2 | 0 | 2 | 0 | 0 |
| Color Picker | 2 | 0 | 2 | 0 | 0 |
| Properties | 6 | 1 | 5 | 0 | 0 |
| Text Edit | 5 | 2 | 3 | 0 | 0 |
| Chart | 9 | 5 | 4 | 0 | 0 |
| Popup | 5 | 2 | 3 | 0 | 0 |
| Combobox | 8 | 7 | 1 | 0 | 0 |
| Abstract Combobox | 17 | 13 | 4 | 0 | 0 |
| Contextual | 9 | 5 | 4 | 0 | 0 |
| Tooltip | 12 | 5 | 3 | 0 | 4 |
| Menu | 18 | 12 | 6 | 0 | 0 |
| Style | 21 | 15 | 6 | 0 | 0 |
| Color | 50 | 32 | 18 | 0 | 0 |
| Image | 16 | 14 | 2 | 0 | 0 |
| Math | 14 | 6 | 8 | 0 | 0 |
| String | 35 | 35 | 0 | 0 | 0 |
| Utf-8 | 4 | 4 | 0 | 0 | 0 |
| Font | 14 | 14 | 0 | 0 | 0 |
| Memory Buffer | 10 | 10 | 0 | 0 | 0 |
| Text Editor | 19 | 12 | 7 | 0 | 0 |
| Draw List | 27 | 27 | 0 | 0 | 0 |
| Gui | 4 | 4 | 0 | 0 | 0 |

## Api

Structs: `nk_buffer`, `nk_allocator`, `nk_command_buffer`, `nk_draw_command`, `nk_convert_config`, `nk_style_item`, `nk_text_edit`, `nk_draw_list`, `nk_user_font`, `nk_panel`, `nk_context`, `nk_draw_vertex_layout_element`, `nk_style_button`, `nk_style_link`, `nk_style_toggle`, `nk_style_selectable`, `nk_style_slide`, `nk_style_progress`, `nk_style_scrollbar`, `nk_style_edit`, `nk_style_property`, `nk_style_chart`, `nk_style_combo`, `nk_style_tab`, `nk_style_window_header`, `nk_style_window`, `nk_color`, `nk_colorf`, `nk_vec2`, `nk_vec2i`, `nk_rect`, `nk_recti`, `nk_image`, `nk_nine_slice`, `nk_cursor`, `nk_scroll`

Enums: `nk_heading`, `nk_button_behavior`, `nk_link_underline`, `nk_modify`, `nk_orientation`, `nk_collapse_states`, `nk_show_states`, `nk_chart_type`, `nk_chart_event`, `nk_color_format`, `nk_popup_type`, `nk_layout_format`, `nk_tree_type`, `nk_tooltip_pos`, `nk_symbol_type`


## Context

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_init_default` | `init_default` | `nk_bool` |
| `unbound` | `nk_init_fixed` | `init_fixed` | `nk_bool` |
| `unbound` | `nk_init` | `init` | `nk_bool` |
| `unbound` | `nk_init_custom` | `init_custom` | `nk_bool` |
| `native` | `nk_clear` | `clear` | `void` |
| `native` | `nk_free` | `free` | `void` |
| `unbound` | `nk_set_user_data` | `set_user_data` | `void` |

## Input

Structs: `nk_mouse_button`, `nk_vec2`, `nk_mouse`, `nk_key`, `nk_keyboard`, `nk_input`

Enums: `nk_keys`, `nk_buttons`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_input_begin` | `input_begin` | `void` |
| `native` | `nk_input_motion` | `input_motion` | `void` |
| `native` | `nk_input_key` | `input_key` | `void` |
| `native` | `nk_input_button` | `input_button` | `void` |
| `native` | `nk_input_scroll` | `input_scroll` | `void` |
| `native` | `nk_input_char` | `input_char` | `void` |
| `unbound` | `nk_input_glyph` | `input_glyph` | `void` |
| `native` | `nk_input_unicode` | `input_unicode` | `void` |
| `native` | `nk_input_end` | `input_end` | `void` |
| `unbound` | `nk_input_has_mouse_click` | `input_has_mouse_click` | `nk_bool` |
| `unbound` | `nk_input_has_mouse_click_in_rect` | `input_has_mouse_click_in_rect` | `nk_bool` |
| `unbound` | `nk_input_has_mouse_click_in_button_rect` | `input_has_mouse_click_in_button_rect` | `nk_bool` |
| `unbound` | `nk_input_has_mouse_click_down_in_rect` | `input_has_mouse_click_down_in_rect` | `nk_bool` |
| `unbound` | `nk_input_is_mouse_click_in_rect` | `input_is_mouse_click_in_rect` | `nk_bool` |
| `unbound` | `nk_input_is_mouse_click_down_in_rect` | `input_is_mouse_click_down_in_rect` | `nk_bool` |
| `unbound` | `nk_input_any_mouse_click_in_rect` | `input_any_mouse_click_in_rect` | `nk_bool` |
| `unbound` | `nk_input_is_mouse_prev_hovering_rect` | `input_is_mouse_prev_hovering_rect` | `nk_bool` |
| `unbound` | `nk_input_is_mouse_hovering_rect` | `input_is_mouse_hovering_rect` | `nk_bool` |
| `unbound` | `nk_input_is_mouse_hovering_still_rect` | `input_is_mouse_hovering_still_rect` | `nk_bool` |
| `unbound` | `nk_input_is_mouse_hovering_delay_rect` | `input_is_mouse_hovering_delay_rect` | `nk_bool` |
| `unbound` | `nk_input_is_mouse_hovering_still_delay_rect` | `input_is_mouse_hovering_still_delay_rect` | `nk_bool` |
| `unbound` | `nk_input_is_mouse_hovering_still_delay_clicked_rect` | `input_is_mouse_hovering_still_delay_clicked_rect` | `nk_bool` |
| `unbound` | `nk_input_is_mouse_moved` | `input_is_mouse_moved` | `nk_bool` |
| `unbound` | `nk_input_mouse_clicked` | `input_mouse_clicked` | `nk_bool` |
| `unbound` | `nk_input_is_mouse_down` | `input_is_mouse_down` | `nk_bool` |
| `unbound` | `nk_input_is_mouse_pressed` | `input_is_mouse_pressed` | `nk_bool` |
| `unbound` | `nk_input_is_mouse_released` | `input_is_mouse_released` | `nk_bool` |
| `unbound` | `nk_input_is_key_pressed` | `input_is_key_pressed` | `nk_bool` |
| `unbound` | `nk_input_is_key_released` | `input_is_key_released` | `nk_bool` |
| `unbound` | `nk_input_is_key_down` | `input_is_key_down` | `nk_bool` |

## Drawing

Structs: `nk_draw_null_texture`, `nk_vec2`, `nk_convert_config`, `nk_command`, `nk_command_scissor`, `nk_command_line`, `nk_vec2i`, `nk_color`, `nk_command_curve`, `nk_command_rect`, `nk_command_rect_filled`, `nk_command_rect_multi_color`, `nk_command_triangle`, `nk_command_triangle_filled`, `nk_command_circle`, `nk_command_circle_filled`, `nk_command_arc`, `nk_command_arc_filled`, `nk_command_polygon`, `nk_command_polygon_filled`, `nk_command_polyline`, `nk_command_image`, `nk_image`, `nk_command_custom`, `nk_command_text`, `nk_command_buffer`, `nk_buffer`, `nk_rect`

Enums: `nk_anti_aliasing`, `nk_convert_result`, `nk_command_type`, `nk_command_clipping`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `unbound` | `nk__begin` | `_begin` | `const struct nk_command*` |
| `unbound` | `nk__next` | `_next` | `const struct nk_command*` |
| `unbound` | `nk_convert` | `convert` | `nk_flags` |
| `unbound` | `nk__draw_begin` | `_draw_begin` | `const struct nk_draw_command*` |
| `unbound` | `nk__draw_end` | `_draw_end` | `const struct nk_draw_command*` |
| `unbound` | `nk__draw_next` | `_draw_next` | `const struct nk_draw_command*` |
| `unbound` | `nk_stroke_line` | `stroke_line` | `void` |
| `unbound` | `nk_stroke_curve` | `stroke_curve` | `void` |
| `unbound` | `nk_stroke_rect` | `stroke_rect` | `void` |
| `unbound` | `nk_stroke_circle` | `stroke_circle` | `void` |
| `unbound` | `nk_stroke_arc` | `stroke_arc` | `void` |
| `unbound` | `nk_stroke_triangle` | `stroke_triangle` | `void` |
| `unbound` | `nk_stroke_polyline` | `stroke_polyline` | `void` |
| `unbound` | `nk_stroke_polygon` | `stroke_polygon` | `void` |
| `unbound` | `nk_fill_rect` | `fill_rect` | `void` |
| `unbound` | `nk_fill_rect_multi_color` | `fill_rect_multi_color` | `void` |
| `unbound` | `nk_fill_circle` | `fill_circle` | `void` |
| `unbound` | `nk_fill_arc` | `fill_arc` | `void` |
| `unbound` | `nk_fill_triangle` | `fill_triangle` | `void` |
| `unbound` | `nk_fill_polygon` | `fill_polygon` | `void` |
| `unbound` | `nk_draw_image` | `draw_image` | `void` |
| `unbound` | `nk_draw_nine_slice` | `draw_nine_slice` | `void` |
| `unbound` | `nk_draw_text` | `draw_text` | `void` |
| `unbound` | `nk_push_scissor` | `push_scissor` | `void` |
| `unbound` | `nk_push_custom` | `push_custom` | `void` |

## Window

Enums: `nk_panel_flags`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_begin` | `begin` | `nk_bool` |
| `native` | `nk_begin_titled` | `begin_titled` | `nk_bool` |
| `native` | `nk_end` | `end` | `void` |
| `native` | `nk_window_get_bounds` | `window_get_bounds` | `struct nk_rect` |
| `native` | `nk_window_get_position` | `window_get_position` | `struct nk_vec2` |
| `native` | `nk_window_get_size` | `window_get_size` | `struct nk_vec2` |
| `native` | `nk_window_get_width` | `window_get_width` | `float` |
| `native` | `nk_window_get_height` | `window_get_height` | `float` |
| `unbound` | `nk_window_get_panel` | `window_get_panel` | `struct nk_panel*` |
| `native` | `nk_window_get_content_region` | `window_get_content_region` | `struct nk_rect` |
| `native` | `nk_window_get_content_region_min` | `window_get_content_region_min` | `struct nk_vec2` |
| `native` | `nk_window_get_content_region_max` | `window_get_content_region_max` | `struct nk_vec2` |
| `native` | `nk_window_get_content_region_size` | `window_get_content_region_size` | `struct nk_vec2` |
| `unbound` | `nk_window_get_canvas` | `window_get_canvas` | `struct nk_command_buffer*` |
| `native` | `nk_window_get_scroll` | `window_get_scroll` | `void` |
| `native` | `nk_window_has_focus` | `window_has_focus` | `nk_bool` |
| `native` | `nk_window_is_hovered` | `window_is_hovered` | `nk_bool` |
| `native` | `nk_window_is_collapsed` | `window_is_collapsed` | `nk_bool` |
| `native` | `nk_window_is_closed` | `window_is_closed` | `nk_bool` |
| `native` | `nk_window_is_hidden` | `window_is_hidden` | `nk_bool` |
| `native` | `nk_window_is_active` | `window_is_active` | `nk_bool` |
| `native` | `nk_window_is_any_hovered` | `window_is_any_hovered` | `nk_bool` |
| `native` | `nk_item_is_any_active` | `item_is_any_active` | `nk_bool` |
| `native` | `nk_window_set_bounds` | `window_set_bounds` | `void` |
| `native` | `nk_window_set_position` | `window_set_position` | `void` |
| `native` | `nk_window_set_size` | `window_set_size` | `void` |
| `native` | `nk_window_set_focus` | `window_set_focus` | `void` |
| `native` | `nk_window_set_scroll` | `window_set_scroll` | `void` |
| `native` | `nk_window_close` | `window_close` | `void` |
| `native` | `nk_window_collapse` | `window_collapse` | `void` |
| `unbound` | `nk_window_collapse_if` | `window_collapse_if` | `void` |
| `native` | `nk_window_show` | `window_show` | `void` |
| `unbound` | `nk_window_show_if` | `window_show_if` | `void` |
| `native` | `nk_rule_horizontal` | `rule_horizontal` | `void` |

## Layout

Enums: `nk_widget_align`, `nk_widget_alignment`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_layout_set_min_row_height` | `layout_set_min_row_height` | `void` |
| `native` | `nk_layout_reset_min_row_height` | `layout_reset_min_row_height` | `void` |
| `native` | `nk_layout_widget_bounds` | `layout_widget_bounds` | `struct nk_rect` |
| `native` | `nk_layout_ratio_from_pixel` | `layout_ratio_from_pixel` | `float` |
| `native` | `nk_layout_row_dynamic` | `layout_row_dynamic` | `void` |
| `native` | `nk_layout_row_static` | `layout_row_static` | `void` |
| `native` | `nk_layout_row_begin` | `layout_row_begin` | `void` |
| `native` | `nk_layout_row_push` | `layout_row_push` | `void` |
| `native` | `nk_layout_row_end` | `layout_row_end` | `void` |
| `native` | `nk_layout_row` | `layout_row` | `void` |
| `native` | `nk_layout_row_template_begin` | `layout_row_template_begin` | `void` |
| `native` | `nk_layout_row_template_push_dynamic` | `layout_row_template_push_dynamic` | `void` |
| `native` | `nk_layout_row_template_push_variable` | `layout_row_template_push_variable` | `void` |
| `native` | `nk_layout_row_template_push_static` | `layout_row_template_push_static` | `void` |
| `native` | `nk_layout_row_template_end` | `layout_row_template_end` | `void` |
| `native` | `nk_layout_space_begin` | `layout_space_begin` | `void` |
| `native` | `nk_layout_space_push` | `layout_space_push` | `void` |
| `native` | `nk_layout_space_end` | `layout_space_end` | `void` |
| `native` | `nk_layout_space_bounds` | `layout_space_bounds` | `struct nk_rect` |
| `native` | `nk_layout_space_to_screen` | `layout_space_to_screen` | `struct nk_vec2` |
| `native` | `nk_layout_space_to_local` | `layout_space_to_local` | `struct nk_vec2` |
| `native` | `nk_layout_space_rect_to_screen` | `layout_space_rect_to_screen` | `struct nk_rect` |
| `native` | `nk_layout_space_rect_to_local` | `layout_space_rect_to_local` | `struct nk_rect` |
| `native` | `nk_spacer` | `spacer` | `void` |

## Group

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_group_begin` | `group_begin` | `nk_bool` |
| `native` | `nk_group_begin_titled` | `group_begin_titled` | `nk_bool` |
| `native` | `nk_group_end` | `group_end` | `void` |
| `unbound` | `nk_group_scrolled_offset_begin` | `group_scrolled_offset_begin` | `nk_bool` |
| `unbound` | `nk_group_scrolled_begin` | `group_scrolled_begin` | `nk_bool` |
| `unbound` | `nk_group_scrolled_end` | `group_scrolled_end` | `void` |
| `native` | `nk_group_get_scroll` | `group_get_scroll` | `void` |
| `native` | `nk_group_set_scroll` | `group_set_scroll` | `void` |

## Tree

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_tree_push_hashed` | `tree_push_hashed` | `nk_bool` |
| `native` | `nk_tree_image_push_hashed` | `tree_image_push_hashed` | `nk_bool` |
| `native` | `nk_tree_pop` | `tree_pop` | `void` |
| `native` | `nk_tree_state_push` | `tree_state_push` | `nk_bool` |
| `unbound` | `nk_tree_state_image_push` | `tree_state_image_push` | `nk_bool` |
| `native` | `nk_tree_state_pop` | `tree_state_pop` | `void` |
| `unbound` | `nk_tree_element_push_hashed` | `tree_element_push_hashed` | `nk_bool` |
| `unbound` | `nk_tree_element_image_push_hashed` | `tree_element_image_push_hashed` | `nk_bool` |
| `unbound` | `nk_tree_element_pop` | `tree_element_pop` | `void` |

## List View

Structs: `nk_list_view`, `nk_context`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `unbound` | `nk_list_view_begin` | `list_view_begin` | `nk_bool` |
| `unbound` | `nk_list_view_end` | `list_view_end` | `void` |

## Widget

Enums: `nk_widget_layout_states`, `nk_widget_states`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `unbound` | `nk_widget` | `widget` | `enum nk_widget_layout_states` |
| `native` | `nk_widget_bounds` | `widget_bounds` | `struct nk_rect` |
| `native` | `nk_widget_position` | `widget_position` | `struct nk_vec2` |
| `native` | `nk_widget_size` | `widget_size` | `struct nk_vec2` |
| `native` | `nk_widget_width` | `widget_width` | `float` |
| `native` | `nk_widget_height` | `widget_height` | `float` |
| `native` | `nk_widget_is_hovered` | `widget_is_hovered` | `nk_bool` |
| `native` | `nk_widget_is_mouse_clicked` | `widget_is_mouse_clicked` | `nk_bool` |
| `native` | `nk_widget_has_mouse_click_down` | `widget_has_mouse_click_down` | `nk_bool` |
| `native` | `nk_spacing` | `spacing` | `void` |
| `native` | `nk_widget_disable_begin` | `widget_disable_begin` | `void` |
| `native` | `nk_widget_disable_end` | `widget_disable_end` | `void` |

## Text

Enums: `nk_text_align`, `nk_text_alignment`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_text` | `text` | `void` |
| `native` | `nk_text_colored` | `text_colored` | `void` |
| `native` | `nk_text_wrap` | `text_wrap` | `void` |
| `native` | `nk_text_wrap_colored` | `text_wrap_colored` | `void` |
| `native` | `nk_label` | `label` | `void` |
| `native` | `nk_label_colored` | `label_colored` | `void` |
| `native` | `nk_label_wrap` | `label_wrap` | `void` |
| `native` | `nk_label_colored_wrap` | `label_colored_wrap` | `void` |
| `native` | `nk_image` | `image` | `void` |
| `native` | `nk_image_color` | `image_color` | `void` |
| `skip` | `nk_labelf` | `labelf` | `void` (Ruby interpolates strings; not bound (`...` / va_list)) |
| `skip` | `nk_labelf_colored` | `labelf_colored` | `void` (Ruby interpolates strings; not bound (`...` / va_list)) |
| `skip` | `nk_labelf_wrap` | `labelf_wrap` | `void` (Ruby interpolates strings; not bound (`...` / va_list)) |
| `skip` | `nk_labelf_colored_wrap` | `labelf_colored_wrap` | `void` (Ruby interpolates strings; not bound (`...` / va_list)) |
| `skip` | `nk_labelfv` | `labelfv` | `void` (Ruby interpolates strings; not bound (`...` / va_list)) |
| `skip` | `nk_labelfv_colored` | `labelfv_colored` | `void` (Ruby interpolates strings; not bound (`...` / va_list)) |
| `skip` | `nk_labelfv_wrap` | `labelfv_wrap` | `void` (Ruby interpolates strings; not bound (`...` / va_list)) |
| `skip` | `nk_labelfv_colored_wrap` | `labelfv_colored_wrap` | `void` (Ruby interpolates strings; not bound (`...` / va_list)) |
| `native` | `nk_value_bool` | `value_bool` | `void` |
| `native` | `nk_value_int` | `value_int` | `void` |
| `native` | `nk_value_uint` | `value_uint` | `void` |
| `native` | `nk_value_float` | `value_float` | `void` |
| `unbound` | `nk_value_color_byte` | `value_color_byte` | `void` |
| `unbound` | `nk_value_color_float` | `value_color_float` | `void` |
| `native` | `nk_value_color_hex` | `value_color_hex` | `void` |

## Link

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `unbound` | `nk_link_text` | `link_text` | `nk_bool` |
| `native` | `nk_link_label` | `link_label` | `nk_bool` |
| `unbound` | `nk_link_text_styled` | `link_text_styled` | `nk_bool` |
| `unbound` | `nk_link_label_styled` | `link_label_styled` | `nk_bool` |
| `unbound` | `nk_link_text_underline` | `link_text_underline` | `nk_bool` |
| `unbound` | `nk_link_label_underline` | `link_label_underline` | `nk_bool` |
| `unbound` | `nk_link_text_hover_underline` | `link_text_hover_underline` | `nk_bool` |
| `unbound` | `nk_link_label_hover_underline` | `link_label_hover_underline` | `nk_bool` |
| `unbound` | `nk_link_text_no_underline` | `link_text_no_underline` | `nk_bool` |
| `unbound` | `nk_link_label_no_underline` | `link_label_no_underline` | `nk_bool` |
| `unbound` | `nk_link_text_colored` | `link_text_colored` | `nk_bool` |
| `unbound` | `nk_link_label_colored` | `link_label_colored` | `nk_bool` |

## Button

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_button_text` | `button_text` | `nk_bool` |
| `native` | `nk_button_label` | `button_label` | `nk_bool` |
| `native` | `nk_button_color` | `button_color` | `nk_bool` |
| `native` | `nk_button_symbol` | `button_symbol` | `nk_bool` |
| `native` | `nk_button_image` | `button_image` | `nk_bool` |
| `native` | `nk_button_symbol_label` | `button_symbol_label` | `nk_bool` |
| `unbound` | `nk_button_symbol_text` | `button_symbol_text` | `nk_bool` |
| `native` | `nk_button_image_label` | `button_image_label` | `nk_bool` |
| `unbound` | `nk_button_image_text` | `button_image_text` | `nk_bool` |
| `unbound` | `nk_button_text_styled` | `button_text_styled` | `nk_bool` |
| `unbound` | `nk_button_label_styled` | `button_label_styled` | `nk_bool` |
| `unbound` | `nk_button_symbol_styled` | `button_symbol_styled` | `nk_bool` |
| `unbound` | `nk_button_image_styled` | `button_image_styled` | `nk_bool` |
| `unbound` | `nk_button_symbol_text_styled` | `button_symbol_text_styled` | `nk_bool` |
| `unbound` | `nk_button_symbol_label_styled` | `button_symbol_label_styled` | `nk_bool` |
| `unbound` | `nk_button_image_label_styled` | `button_image_label_styled` | `nk_bool` |
| `unbound` | `nk_button_image_text_styled` | `button_image_text_styled` | `nk_bool` |
| `native` | `nk_button_set_behavior` | `button_set_behavior` | `void` |
| `native` | `nk_button_push_behavior` | `button_push_behavior` | `nk_bool` |
| `native` | `nk_button_pop_behavior` | `button_pop_behavior` | `nk_bool` |

## Checkbox

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_check_label` | `check_label` | `nk_bool` |
| `unbound` | `nk_check_text` | `check_text` | `nk_bool` |
| `unbound` | `nk_check_text_align` | `check_text_align` | `nk_bool` |
| `unbound` | `nk_check_flags_label` | `check_flags_label` | `unsigned` |
| `unbound` | `nk_check_flags_text` | `check_flags_text` | `unsigned` |
| `native` | `nk_checkbox_label` | `checkbox_label` | `nk_bool` |
| `unbound` | `nk_checkbox_label_align` | `checkbox_label_align` | `nk_bool` |
| `unbound` | `nk_checkbox_text` | `checkbox_text` | `nk_bool` |
| `unbound` | `nk_checkbox_text_align` | `checkbox_text_align` | `nk_bool` |
| `native` | `nk_checkbox_flags_label` | `checkbox_flags_label` | `nk_bool` |
| `unbound` | `nk_checkbox_flags_text` | `checkbox_flags_text` | `nk_bool` |

## Radio Button

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_radio_label` | `radio_label` | `nk_bool` |
| `unbound` | `nk_radio_label_align` | `radio_label_align` | `nk_bool` |
| `unbound` | `nk_radio_text` | `radio_text` | `nk_bool` |
| `unbound` | `nk_radio_text_align` | `radio_text_align` | `nk_bool` |
| `native` | `nk_option_label` | `option_label` | `nk_bool` |
| `unbound` | `nk_option_label_align` | `option_label_align` | `nk_bool` |
| `unbound` | `nk_option_text` | `option_text` | `nk_bool` |
| `unbound` | `nk_option_text_align` | `option_text_align` | `nk_bool` |

## Selectable

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_selectable_label` | `selectable_label` | `nk_bool` |
| `unbound` | `nk_selectable_text` | `selectable_text` | `nk_bool` |
| `unbound` | `nk_selectable_image_label` | `selectable_image_label` | `nk_bool` |
| `unbound` | `nk_selectable_image_text` | `selectable_image_text` | `nk_bool` |
| `unbound` | `nk_selectable_symbol_label` | `selectable_symbol_label` | `nk_bool` |
| `unbound` | `nk_selectable_symbol_text` | `selectable_symbol_text` | `nk_bool` |
| `native` | `nk_select_label` | `select_label` | `nk_bool` |
| `unbound` | `nk_select_text` | `select_text` | `nk_bool` |
| `unbound` | `nk_select_image_label` | `select_image_label` | `nk_bool` |
| `unbound` | `nk_select_image_text` | `select_image_text` | `nk_bool` |
| `unbound` | `nk_select_symbol_label` | `select_symbol_label` | `nk_bool` |
| `unbound` | `nk_select_symbol_text` | `select_symbol_text` | `nk_bool` |

## Slider

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_slide_float` | `slide_float` | `float` |
| `native` | `nk_slide_int` | `slide_int` | `int` |
| `native` | `nk_slider_float` | `slider_float` | `nk_bool` |
| `native` | `nk_slider_int` | `slider_int` | `nk_bool` |

## Knob

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_knob_float` | `knob_float` | `nk_bool` |
| `unbound` | `nk_knob_int` | `knob_int` | `nk_bool` |

## Progressbar

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_progress` | `progress` | `nk_bool` |
| `native` | `nk_prog` | `prog` | `nk_size` |

## Color Picker

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_color_picker` | `color_picker` | `struct nk_colorf` |
| `native` | `nk_color_pick` | `color_pick` | `nk_bool` |

## Properties

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_property_int` | `property_int` | `nk_bool` |
| `native` | `nk_property_float` | `property_float` | `nk_bool` |
| `unbound` | `nk_property_double` | `property_double` | `nk_bool` |
| `native` | `nk_propertyi` | `propertyi` | `int` |
| `native` | `nk_propertyf` | `propertyf` | `float` |
| `native` | `nk_propertyd` | `propertyd` | `double` |

## Text Edit

Enums: `nk_edit_flags`, `nk_edit_types`, `nk_edit_events`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_edit_string` | `edit_string` | `nk_flags` |
| `unbound` | `nk_edit_string_zero_terminated` | `edit_string_zero_terminated` | `nk_flags` |
| `unbound` | `nk_edit_buffer` | `edit_buffer` | `nk_flags` |
| `native` | `nk_edit_focus` | `edit_focus` | `void` |
| `native` | `nk_edit_unfocus` | `edit_unfocus` | `void` |

## Chart

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_chart_begin` | `chart_begin` | `nk_bool` |
| `unbound` | `nk_chart_begin_colored` | `chart_begin_colored` | `nk_bool` |
| `unbound` | `nk_chart_add_slot` | `chart_add_slot` | `void` |
| `unbound` | `nk_chart_add_slot_colored` | `chart_add_slot_colored` | `void` |
| `native` | `nk_chart_push` | `chart_push` | `nk_flags` |
| `unbound` | `nk_chart_push_slot` | `chart_push_slot` | `nk_flags` |
| `native` | `nk_chart_end` | `chart_end` | `void` |
| `native` | `nk_plot` | `plot` | `void` |
| `unbound` | `nk_plot_function` | `plot_function` | `void` |

## Popup

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_popup_begin` | `popup_begin` | `nk_bool` |
| `native` | `nk_popup_close` | `popup_close` | `void` |
| `native` | `nk_popup_end` | `popup_end` | `void` |
| `unbound` | `nk_popup_get_scroll` | `popup_get_scroll` | `void` |
| `unbound` | `nk_popup_set_scroll` | `popup_set_scroll` | `void` |

## Combobox

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_combo` | `combo` | `int` |
| `unbound` | `nk_combo_separator` | `combo_separator` | `int` |
| `unbound` | `nk_combo_string` | `combo_string` | `int` |
| `unbound` | `nk_combo_callback` | `combo_callback` | `int` |
| `unbound` | `nk_combobox` | `combobox` | `nk_bool` |
| `unbound` | `nk_combobox_string` | `combobox_string` | `nk_bool` |
| `unbound` | `nk_combobox_separator` | `combobox_separator` | `nk_bool` |
| `unbound` | `nk_combobox_callback` | `combobox_callback` | `nk_bool` |

## Abstract Combobox

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `unbound` | `nk_combo_begin_text` | `combo_begin_text` | `nk_bool` |
| `native` | `nk_combo_begin_label` | `combo_begin_label` | `nk_bool` |
| `unbound` | `nk_combo_begin_color` | `combo_begin_color` | `nk_bool` |
| `unbound` | `nk_combo_begin_symbol` | `combo_begin_symbol` | `nk_bool` |
| `unbound` | `nk_combo_begin_symbol_label` | `combo_begin_symbol_label` | `nk_bool` |
| `unbound` | `nk_combo_begin_symbol_text` | `combo_begin_symbol_text` | `nk_bool` |
| `unbound` | `nk_combo_begin_image` | `combo_begin_image` | `nk_bool` |
| `unbound` | `nk_combo_begin_image_label` | `combo_begin_image_label` | `nk_bool` |
| `unbound` | `nk_combo_begin_image_text` | `combo_begin_image_text` | `nk_bool` |
| `native` | `nk_combo_item_label` | `combo_item_label` | `nk_bool` |
| `unbound` | `nk_combo_item_text` | `combo_item_text` | `nk_bool` |
| `unbound` | `nk_combo_item_image_label` | `combo_item_image_label` | `nk_bool` |
| `unbound` | `nk_combo_item_image_text` | `combo_item_image_text` | `nk_bool` |
| `unbound` | `nk_combo_item_symbol_label` | `combo_item_symbol_label` | `nk_bool` |
| `unbound` | `nk_combo_item_symbol_text` | `combo_item_symbol_text` | `nk_bool` |
| `native` | `nk_combo_close` | `combo_close` | `void` |
| `native` | `nk_combo_end` | `combo_end` | `void` |

## Contextual

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_contextual_begin` | `contextual_begin` | `nk_bool` |
| `unbound` | `nk_contextual_item_text` | `contextual_item_text` | `nk_bool` |
| `native` | `nk_contextual_item_label` | `contextual_item_label` | `nk_bool` |
| `unbound` | `nk_contextual_item_image_label` | `contextual_item_image_label` | `nk_bool` |
| `unbound` | `nk_contextual_item_image_text` | `contextual_item_image_text` | `nk_bool` |
| `unbound` | `nk_contextual_item_symbol_label` | `contextual_item_symbol_label` | `nk_bool` |
| `unbound` | `nk_contextual_item_symbol_text` | `contextual_item_symbol_text` | `nk_bool` |
| `native` | `nk_contextual_close` | `contextual_close` | `void` |
| `native` | `nk_contextual_end` | `contextual_end` | `void` |

## Tooltip

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_tooltip` | `tooltip` | `void` |
| `unbound` | `nk_tooltip_offset` | `tooltip_offset` | `void` |
| `unbound` | `nk_do_tooltip` | `do_tooltip` | `void` |
| `unbound` | `nk_do_tooltip_delay` | `do_tooltip_delay` | `void` |
| `unbound` | `nk_do_tooltip_delay_clicked` | `do_tooltip_delay_clicked` | `void` |
| `skip` | `nk_tooltipf` | `tooltipf` | `void` (Ruby interpolates strings; not bound (`...` / va_list)) |
| `skip` | `nk_tooltipfv` | `tooltipfv` | `void` (Ruby interpolates strings; not bound (`...` / va_list)) |
| `skip` | `nk_tooltipf_offset` | `tooltipf_offset` | `void` (Ruby interpolates strings; not bound (`...` / va_list)) |
| `skip` | `nk_tooltipfv_offset` | `tooltipfv_offset` | `void` (Ruby interpolates strings; not bound (`...` / va_list)) |
| `native` | `nk_tooltip_begin` | `tooltip_begin` | `nk_bool` |
| `unbound` | `nk_tooltip_begin_offset` | `tooltip_begin_offset` | `nk_bool` |
| `native` | `nk_tooltip_end` | `tooltip_end` | `void` |

## Menu

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_menubar_begin` | `menubar_begin` | `void` |
| `native` | `nk_menubar_end` | `menubar_end` | `void` |
| `unbound` | `nk_menu_begin_text` | `menu_begin_text` | `nk_bool` |
| `native` | `nk_menu_begin_label` | `menu_begin_label` | `nk_bool` |
| `unbound` | `nk_menu_begin_image` | `menu_begin_image` | `nk_bool` |
| `unbound` | `nk_menu_begin_image_text` | `menu_begin_image_text` | `nk_bool` |
| `unbound` | `nk_menu_begin_image_label` | `menu_begin_image_label` | `nk_bool` |
| `unbound` | `nk_menu_begin_symbol` | `menu_begin_symbol` | `nk_bool` |
| `unbound` | `nk_menu_begin_symbol_text` | `menu_begin_symbol_text` | `nk_bool` |
| `unbound` | `nk_menu_begin_symbol_label` | `menu_begin_symbol_label` | `nk_bool` |
| `unbound` | `nk_menu_item_text` | `menu_item_text` | `nk_bool` |
| `native` | `nk_menu_item_label` | `menu_item_label` | `nk_bool` |
| `unbound` | `nk_menu_item_image_label` | `menu_item_image_label` | `nk_bool` |
| `unbound` | `nk_menu_item_image_text` | `menu_item_image_text` | `nk_bool` |
| `unbound` | `nk_menu_item_symbol_text` | `menu_item_symbol_text` | `nk_bool` |
| `unbound` | `nk_menu_item_symbol_label` | `menu_item_symbol_label` | `nk_bool` |
| `native` | `nk_menu_close` | `menu_close` | `void` |
| `native` | `nk_menu_end` | `menu_end` | `void` |

## Style

Enums: `nk_style_colors`, `nk_style_cursor`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_style_default` | `style_default` | `void` |
| `native` | `nk_style_from_table` | `style_from_table` | `void` |
| `unbound` | `nk_style_load_cursor` | `style_load_cursor` | `void` |
| `unbound` | `nk_style_load_all_cursors` | `style_load_all_cursors` | `void` |
| `native` | `nk_style_get_color_by_name` | `style_get_color_by_name` | `const char*` |
| `unbound` | `nk_style_set_font` | `style_set_font` | `void` |
| `native` | `nk_style_set_cursor` | `style_set_cursor` | `nk_bool` |
| `native` | `nk_style_show_cursor` | `style_show_cursor` | `void` |
| `native` | `nk_style_hide_cursor` | `style_hide_cursor` | `void` |
| `unbound` | `nk_style_push_font` | `style_push_font` | `nk_bool` |
| `unbound` | `nk_style_push_float` | `style_push_float` | `nk_bool` |
| `unbound` | `nk_style_push_vec2` | `style_push_vec2` | `nk_bool` |
| `unbound` | `nk_style_push_style_item` | `style_push_style_item` | `nk_bool` |
| `unbound` | `nk_style_push_flags` | `style_push_flags` | `nk_bool` |
| `unbound` | `nk_style_push_color` | `style_push_color` | `nk_bool` |
| `unbound` | `nk_style_pop_font` | `style_pop_font` | `nk_bool` |
| `unbound` | `nk_style_pop_float` | `style_pop_float` | `nk_bool` |
| `unbound` | `nk_style_pop_vec2` | `style_pop_vec2` | `nk_bool` |
| `unbound` | `nk_style_pop_style_item` | `style_pop_style_item` | `nk_bool` |
| `unbound` | `nk_style_pop_flags` | `style_pop_flags` | `nk_bool` |
| `unbound` | `nk_style_pop_color` | `style_pop_color` | `nk_bool` |

## Color

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_rgb` | `rgb` | `struct nk_color` |
| `unbound` | `nk_rgb_iv` | `rgb_iv` | `struct nk_color` |
| `unbound` | `nk_rgb_bv` | `rgb_bv` | `struct nk_color` |
| `native` | `nk_rgb_f` | `rgb_f` | `struct nk_color` |
| `unbound` | `nk_rgb_fv` | `rgb_fv` | `struct nk_color` |
| `native` | `nk_rgb_cf` | `rgb_cf` | `struct nk_color` |
| `native` | `nk_rgb_hex` | `rgb_hex` | `struct nk_color` |
| `native` | `nk_rgb_factor` | `rgb_factor` | `struct nk_color` |
| `native` | `nk_rgba` | `rgba` | `struct nk_color` |
| `native` | `nk_rgba_u32` | `rgba_u32` | `struct nk_color` |
| `unbound` | `nk_rgba_iv` | `rgba_iv` | `struct nk_color` |
| `unbound` | `nk_rgba_bv` | `rgba_bv` | `struct nk_color` |
| `native` | `nk_rgba_f` | `rgba_f` | `struct nk_color` |
| `unbound` | `nk_rgba_fv` | `rgba_fv` | `struct nk_color` |
| `native` | `nk_rgba_cf` | `rgba_cf` | `struct nk_color` |
| `native` | `nk_rgba_hex` | `rgba_hex` | `struct nk_color` |
| `unbound` | `nk_hsva_colorf` | `hsva_colorf` | `struct nk_colorf` |
| `unbound` | `nk_hsva_colorfv` | `hsva_colorfv` | `struct nk_colorf` |
| `unbound` | `nk_colorf_hsva_f` | `colorf_hsva_f` | `void` |
| `unbound` | `nk_colorf_hsva_fv` | `colorf_hsva_fv` | `void` |
| `native` | `nk_hsv` | `hsv` | `struct nk_color` |
| `unbound` | `nk_hsv_iv` | `hsv_iv` | `struct nk_color` |
| `unbound` | `nk_hsv_bv` | `hsv_bv` | `struct nk_color` |
| `native` | `nk_hsv_f` | `hsv_f` | `struct nk_color` |
| `unbound` | `nk_hsv_fv` | `hsv_fv` | `struct nk_color` |
| `native` | `nk_hsva` | `hsva` | `struct nk_color` |
| `unbound` | `nk_hsva_iv` | `hsva_iv` | `struct nk_color` |
| `unbound` | `nk_hsva_bv` | `hsva_bv` | `struct nk_color` |
| `native` | `nk_hsva_f` | `hsva_f` | `struct nk_color` |
| `unbound` | `nk_hsva_fv` | `hsva_fv` | `struct nk_color` |
| `unbound` | `nk_color_f` | `color_f` | `void` |
| `unbound` | `nk_color_fv` | `color_fv` | `void` |
| `native` | `nk_color_cf` | `color_cf` | `struct nk_colorf` |
| `unbound` | `nk_color_d` | `color_d` | `void` |
| `unbound` | `nk_color_dv` | `color_dv` | `void` |
| `native` | `nk_color_u32` | `color_u32` | `nk_uint` |
| `native` | `nk_color_hex_rgba` | `color_hex_rgba` | `void` |
| `native` | `nk_color_hex_rgb` | `color_hex_rgb` | `void` |
| `unbound` | `nk_color_hsv_i` | `color_hsv_i` | `void` |
| `unbound` | `nk_color_hsv_b` | `color_hsv_b` | `void` |
| `unbound` | `nk_color_hsv_iv` | `color_hsv_iv` | `void` |
| `unbound` | `nk_color_hsv_bv` | `color_hsv_bv` | `void` |
| `unbound` | `nk_color_hsv_f` | `color_hsv_f` | `void` |
| `unbound` | `nk_color_hsv_fv` | `color_hsv_fv` | `void` |
| `unbound` | `nk_color_hsva_i` | `color_hsva_i` | `void` |
| `unbound` | `nk_color_hsva_b` | `color_hsva_b` | `void` |
| `unbound` | `nk_color_hsva_iv` | `color_hsva_iv` | `void` |
| `unbound` | `nk_color_hsva_bv` | `color_hsva_bv` | `void` |
| `unbound` | `nk_color_hsva_f` | `color_hsva_f` | `void` |
| `unbound` | `nk_color_hsva_fv` | `color_hsva_fv` | `void` |

## Image

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `unbound` | `nk_handle_ptr` | `handle_ptr` | `nk_handle` |
| `unbound` | `nk_handle_id` | `handle_id` | `nk_handle` |
| `unbound` | `nk_image_handle` | `image_handle` | `struct nk_image` |
| `unbound` | `nk_image_ptr` | `image_ptr` | `struct nk_image` |
| `native` | `nk_image_id` | `image_id` | `struct nk_image` |
| `native` | `nk_image_is_subimage` | `image_is_subimage` | `nk_bool` |
| `unbound` | `nk_subimage_ptr` | `subimage_ptr` | `struct nk_image` |
| `unbound` | `nk_subimage_id` | `subimage_id` | `struct nk_image` |
| `unbound` | `nk_subimage_handle` | `subimage_handle` | `struct nk_image` |
| `unbound` | `nk_nine_slice_handle` | `nine_slice_handle` | `struct nk_nine_slice` |
| `unbound` | `nk_nine_slice_ptr` | `nine_slice_ptr` | `struct nk_nine_slice` |
| `unbound` | `nk_nine_slice_id` | `nine_slice_id` | `struct nk_nine_slice` |
| `unbound` | `nk_nine_slice_is_sub9slice` | `nine_slice_is_sub9slice` | `int` |
| `unbound` | `nk_sub9slice_ptr` | `sub9slice_ptr` | `struct nk_nine_slice` |
| `unbound` | `nk_sub9slice_id` | `sub9slice_id` | `struct nk_nine_slice` |
| `unbound` | `nk_sub9slice_handle` | `sub9slice_handle` | `struct nk_nine_slice` |

## Math

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `unbound` | `nk_murmur_hash` | `murmur_hash` | `nk_hash` |
| `unbound` | `nk_triangle_from_direction` | `triangle_from_direction` | `void` |
| `native` | `nk_vec2` | `vec2` | `struct nk_vec2` |
| `native` | `nk_vec2i` | `vec2i` | `struct nk_vec2` |
| `unbound` | `nk_vec2v` | `vec2v` | `struct nk_vec2` |
| `unbound` | `nk_vec2iv` | `vec2iv` | `struct nk_vec2` |
| `native` | `nk_get_null_rect` | `get_null_rect` | `struct nk_rect` |
| `native` | `nk_rect` | `rect` | `struct nk_rect` |
| `native` | `nk_recti` | `recti` | `struct nk_rect` |
| `native` | `nk_recta` | `recta` | `struct nk_rect` |
| `unbound` | `nk_rectv` | `rectv` | `struct nk_rect` |
| `unbound` | `nk_rectiv` | `rectiv` | `struct nk_rect` |
| `native` | `nk_rect_pos` | `rect_pos` | `struct nk_vec2` |
| `native` | `nk_rect_size` | `rect_size` | `struct nk_vec2` |

## String

Structs: `nk_str`, `nk_buffer`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `unbound` | `nk_strlen` | `strlen` | `int` |
| `unbound` | `nk_stricmp` | `stricmp` | `int` |
| `unbound` | `nk_stricmpn` | `stricmpn` | `int` |
| `unbound` | `nk_strtoi` | `strtoi` | `int` |
| `unbound` | `nk_strtof` | `strtof` | `float` |
| `unbound` | `nk_strtod` | `strtod` | `double` |
| `unbound` | `nk_strfilter` | `strfilter` | `int` |
| `unbound` | `nk_strmatch_fuzzy_string` | `strmatch_fuzzy_string` | `int` |
| `unbound` | `nk_strmatch_fuzzy_text` | `strmatch_fuzzy_text` | `int` |
| `unbound` | `nk_str_init_default` | `str_init_default` | `void` |
| `unbound` | `nk_str_init` | `str_init` | `void` |
| `unbound` | `nk_str_init_fixed` | `str_init_fixed` | `void` |
| `unbound` | `nk_str_clear` | `str_clear` | `void` |
| `unbound` | `nk_str_free` | `str_free` | `void` |
| `unbound` | `nk_str_append_text_char` | `str_append_text_char` | `int` |
| `unbound` | `nk_str_append_str_char` | `str_append_str_char` | `int` |
| `unbound` | `nk_str_append_text_utf8` | `str_append_text_utf8` | `int` |
| `unbound` | `nk_str_append_str_utf8` | `str_append_str_utf8` | `int` |
| `unbound` | `nk_str_append_text_runes` | `str_append_text_runes` | `int` |
| `unbound` | `nk_str_append_str_runes` | `str_append_str_runes` | `int` |
| `unbound` | `nk_str_insert_at_char` | `str_insert_at_char` | `int` |
| `unbound` | `nk_str_insert_at_rune` | `str_insert_at_rune` | `int` |
| `unbound` | `nk_str_insert_text_char` | `str_insert_text_char` | `int` |
| `unbound` | `nk_str_insert_str_char` | `str_insert_str_char` | `int` |
| `unbound` | `nk_str_insert_text_utf8` | `str_insert_text_utf8` | `int` |
| `unbound` | `nk_str_insert_str_utf8` | `str_insert_str_utf8` | `int` |
| `unbound` | `nk_str_insert_text_runes` | `str_insert_text_runes` | `int` |
| `unbound` | `nk_str_insert_str_runes` | `str_insert_str_runes` | `int` |
| `unbound` | `nk_str_remove_chars` | `str_remove_chars` | `void` |
| `unbound` | `nk_str_remove_runes` | `str_remove_runes` | `void` |
| `unbound` | `nk_str_delete_chars` | `str_delete_chars` | `void` |
| `unbound` | `nk_str_delete_runes` | `str_delete_runes` | `void` |
| `unbound` | `nk_str_rune_at` | `str_rune_at` | `nk_rune` |
| `unbound` | `nk_str_len` | `str_len` | `int` |
| `unbound` | `nk_str_len_char` | `str_len_char` | `int` |

## Utf-8

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `unbound` | `nk_utf_decode` | `utf_decode` | `int` |
| `unbound` | `nk_utf_encode` | `utf_encode` | `int` |
| `unbound` | `nk_utf_len` | `utf_len` | `int` |
| `unbound` | `nk_utf_at` | `utf_at` | `const char*` |

## Font

Structs: `nk_user_font_glyph`, `nk_vec2`, `nk_user_font`, `nk_font`, `nk_baked_font`, `nk_font_config`, `nk_font_glyph`, `nk_font_atlas`, `nk_allocator`, `nk_recti`, `nk_cursor`

Enums: `nk_font_coord_type`, `nk_font_atlas_format`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `unbound` | `nk_font_atlas_init_default` | `font_atlas_init_default` | `void` |
| `unbound` | `nk_font_atlas_init` | `font_atlas_init` | `void` |
| `unbound` | `nk_font_atlas_init_custom` | `font_atlas_init_custom` | `void` |
| `unbound` | `nk_font_atlas_begin` | `font_atlas_begin` | `void` |
| `unbound` | `nk_font_config` | `font_config` | `struct nk_font_config` |
| `unbound` | `nk_font_atlas_add_default` | `font_atlas_add_default` | `struct nk_font*` |
| `unbound` | `nk_font_atlas_add_from_memory` | `font_atlas_add_from_memory` | `struct nk_font*` |
| `unbound` | `nk_font_atlas_add_from_file` | `font_atlas_add_from_file` | `struct nk_font*` |
| `unbound` | `nk_font_atlas_add_compressed_base85` | `font_atlas_add_compressed_base85` | `struct nk_font*` |
| `unbound` | `nk_font_atlas_bake` | `font_atlas_bake` | `const void*` |
| `unbound` | `nk_font_atlas_end` | `font_atlas_end` | `void` |
| `unbound` | `nk_font_find_glyph` | `font_find_glyph` | `const struct nk_font_glyph*` |
| `unbound` | `nk_font_atlas_cleanup` | `font_atlas_cleanup` | `void` |
| `unbound` | `nk_font_atlas_clear` | `font_atlas_clear` | `void` |

## Memory Buffer

Structs: `nk_memory_status`, `nk_buffer_marker`, `nk_memory`, `nk_buffer`, `nk_allocator`

Enums: `nk_allocation_type`, `nk_buffer_allocation_type`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `unbound` | `nk_buffer_init_default` | `buffer_init_default` | `void` |
| `unbound` | `nk_buffer_init` | `buffer_init` | `void` |
| `unbound` | `nk_buffer_init_fixed` | `buffer_init_fixed` | `void` |
| `unbound` | `nk_buffer_info` | `buffer_info` | `void` |
| `unbound` | `nk_buffer_push` | `buffer_push` | `void` |
| `unbound` | `nk_buffer_mark` | `buffer_mark` | `void` |
| `unbound` | `nk_buffer_reset` | `buffer_reset` | `void` |
| `unbound` | `nk_buffer_clear` | `buffer_clear` | `void` |
| `unbound` | `nk_buffer_free` | `buffer_free` | `void` |
| `unbound` | `nk_buffer_total` | `buffer_total` | `nk_size` |

## Text Editor

Structs: `nk_text_edit`, `nk_clipboard`, `nk_text_undo_record`, `nk_text_undo_state`, `nk_str`, `nk_vec2`

Enums: `nk_text_edit_type`, `nk_text_edit_mode`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `native` | `nk_filter_default` | `filter_default` | `nk_bool` |
| `native` | `nk_filter_ascii` | `filter_ascii` | `nk_bool` |
| `native` | `nk_filter_float` | `filter_float` | `nk_bool` |
| `native` | `nk_filter_decimal` | `filter_decimal` | `nk_bool` |
| `native` | `nk_filter_hex` | `filter_hex` | `nk_bool` |
| `native` | `nk_filter_oct` | `filter_oct` | `nk_bool` |
| `native` | `nk_filter_binary` | `filter_binary` | `nk_bool` |
| `unbound` | `nk_textedit_init_default` | `textedit_init_default` | `void` |
| `unbound` | `nk_textedit_init` | `textedit_init` | `void` |
| `unbound` | `nk_textedit_init_fixed` | `textedit_init_fixed` | `void` |
| `unbound` | `nk_textedit_free` | `textedit_free` | `void` |
| `unbound` | `nk_textedit_text` | `textedit_text` | `void` |
| `unbound` | `nk_textedit_delete` | `textedit_delete` | `void` |
| `unbound` | `nk_textedit_delete_selection` | `textedit_delete_selection` | `void` |
| `unbound` | `nk_textedit_select_all` | `textedit_select_all` | `void` |
| `unbound` | `nk_textedit_cut` | `textedit_cut` | `nk_bool` |
| `unbound` | `nk_textedit_paste` | `textedit_paste` | `nk_bool` |
| `unbound` | `nk_textedit_undo` | `textedit_undo` | `void` |
| `unbound` | `nk_textedit_redo` | `textedit_redo` | `void` |

## Draw List

Structs: `nk_draw_vertex_layout_element`, `nk_draw_command`, `nk_rect`, `nk_draw_list`, `nk_vec2`, `nk_convert_config`, `nk_buffer`

Enums: `nk_draw_list_stroke`, `nk_draw_vertex_layout_attribute`, `nk_draw_vertex_layout_format`, `nk_anti_aliasing`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `unbound` | `nk_draw_list_init` | `draw_list_init` | `void` |
| `unbound` | `nk_draw_list_setup` | `draw_list_setup` | `void` |
| `unbound` | `nk__draw_list_begin` | `_draw_list_begin` | `const struct nk_draw_command*` |
| `unbound` | `nk__draw_list_next` | `_draw_list_next` | `const struct nk_draw_command*` |
| `unbound` | `nk__draw_list_end` | `_draw_list_end` | `const struct nk_draw_command*` |
| `unbound` | `nk_draw_list_path_clear` | `draw_list_path_clear` | `void` |
| `unbound` | `nk_draw_list_path_line_to` | `draw_list_path_line_to` | `void` |
| `unbound` | `nk_draw_list_path_arc_to_fast` | `draw_list_path_arc_to_fast` | `void` |
| `unbound` | `nk_draw_list_path_arc_to` | `draw_list_path_arc_to` | `void` |
| `unbound` | `nk_draw_list_path_rect_to` | `draw_list_path_rect_to` | `void` |
| `unbound` | `nk_draw_list_path_curve_to` | `draw_list_path_curve_to` | `void` |
| `unbound` | `nk_draw_list_path_fill` | `draw_list_path_fill` | `void` |
| `unbound` | `nk_draw_list_path_stroke` | `draw_list_path_stroke` | `void` |
| `unbound` | `nk_draw_list_stroke_line` | `draw_list_stroke_line` | `void` |
| `unbound` | `nk_draw_list_stroke_rect` | `draw_list_stroke_rect` | `void` |
| `unbound` | `nk_draw_list_stroke_triangle` | `draw_list_stroke_triangle` | `void` |
| `unbound` | `nk_draw_list_stroke_circle` | `draw_list_stroke_circle` | `void` |
| `unbound` | `nk_draw_list_stroke_curve` | `draw_list_stroke_curve` | `void` |
| `unbound` | `nk_draw_list_stroke_poly_line` | `draw_list_stroke_poly_line` | `void` |
| `unbound` | `nk_draw_list_fill_rect` | `draw_list_fill_rect` | `void` |
| `unbound` | `nk_draw_list_fill_rect_multi_color` | `draw_list_fill_rect_multi_color` | `void` |
| `unbound` | `nk_draw_list_fill_triangle` | `draw_list_fill_triangle` | `void` |
| `unbound` | `nk_draw_list_fill_circle` | `draw_list_fill_circle` | `void` |
| `unbound` | `nk_draw_list_fill_poly_convex` | `draw_list_fill_poly_convex` | `void` |
| `unbound` | `nk_draw_list_add_image` | `draw_list_add_image` | `void` |
| `unbound` | `nk_draw_list_add_text` | `draw_list_add_text` | `void` |
| `unbound` | `nk_draw_list_push_userdata` | `draw_list_push_userdata` | `void` |

## Gui

Structs: `nk_color`, `nk_image`, `nk_nine_slice`, `nk_style_item`, `nk_style_text`, `nk_vec2`, `nk_style_link`, `nk_style_button`, `nk_style_toggle`, `nk_style_selectable`, `nk_style_slider`, `nk_style_knob`, `nk_style_progress`, `nk_style_scrollbar`, `nk_style_edit`, `nk_style_property`, `nk_style_chart`, `nk_style_combo`, `nk_style_tab`, `nk_style_window_header`, `nk_style_window`, `nk_style`, `nk_cursor`, `nk_chart_slot`, `nk_chart`, `nk_row_layout`, `nk_rect`, `nk_popup_buffer`, `nk_menu_state`, `nk_scroll`, `nk_panel`, `nk_command_buffer`, `nk_table`, `nk_popup_state`, `nk_window`, `nk_edit_state`, `nk_property_state`, `nk_config_stack_`, `nk_configuration_stacks`, `nk_config_stack_style_item`, `nk_config_stack_float`, `nk_config_stack_vec2`, `nk_config_stack_flags`, `nk_config_stack_color`, `nk_config_stack_user_font`, `nk_config_stack_button_behavior`, `nk_page_element`, `nk_page`, `nk_pool`, `nk_allocator`, `nk_context`, `nk_input`, `nk_buffer`, `nk_clipboard`, `nk_draw_list`, `nk_text_edit`

Enums: `nk_style_item_type`, `nk_link_underline`, `nk_symbol_type`, `nk_style_header_align`, `nk_tooltip_pos`, `nk_panel_type`, `nk_panel_set`, `nk_chart_type`, `nk_panel_row_layout_type`, `nk_window_flags`, `nk_allocation_type`, `nk_button_behavior`

| Status | C | Ruby Native | Retorno |
|---|---|---|---|
| `unbound` | `nk_style_item_color` | `style_item_color` | `struct nk_style_item` |
| `unbound` | `nk_style_item_image` | `style_item_image` | `struct nk_style_item` |
| `unbound` | `nk_style_item_nine_slice` | `style_item_nine_slice` | `struct nk_style_item` |
| `unbound` | `nk_style_item_hide` | `style_item_hide` | `struct nk_style_item` |
