# TODO — Granada

Checklist vivo. Marcar `[x]` só com código/teste comprovando. O detalhe por função C está em `docs/api-map.md` (gerado por `make inventory`).

Nuklear **v4.13.3**. mruby **4.0.0**. Autor: Luccas Brandão Bezerra. Apache-2.0.

## Fase A — esqueleto

- [x] Repo GitHub `srluccasonline/granada`
- [x] LICENSE Apache-2.0 + NOTICE
- [x] Vendor `nuklear.h` v4.13.3
- [x] Build mruby 4.0.0 + gem `mruby-granada` (`make` / `make test`)
- [x] Módulo `Granada` / `Granada::Native` / `Granada::UI`

## Fase B — inventário

- [x] `tools/inventory_nuklear.rb` gera `docs/api-map.md`
- [x] Toda `NK_API` listada com status `unbound` / `native` / `dsl` / `skip` (552 funções, 540 bind, 12 skip vararg)

## Fase C — Native (1:1)

- [x] Types: Rect, Vec2, Color, ColorF, Image (NineSlice / Handle depois)
- [x] Flags / enums (WINDOW_*, TEXT_*, KEY_*, MOUSE_*, EDIT_*, COLOR_*, …)
- [x] Context (init / clear / free; wrap externo para o host)
- [x] Input
- [ ] Drawing iterators (`nk__begin`, `nk_convert`, …) — o host GLFW usa o backend oficial, não precisa no Ruby
- [x] Window (`nk_begin` / `nk_end` + queries; `MRB_ENSURE`)
- [x] Layout
- [x] Groups
- [x] Tree (hashed + state_push)
- [x] List view
- [x] Widget queries / spacing / disable
- [x] Text / label (sem `*f` vararg)
- [x] Links (`link_label`)
- [x] Button
- [x] Checkbox / radio / option
- [x] Selectable
- [x] Slider / knob / progress
- [x] Color picker
- [x] Property
- [x] Edit (buffer Ruby, filtros por símbolo)
- [x] Chart (`chart_begin` / `plot`)
- [x] Popup
- [x] Combo
- [x] Contextual
- [x] Tooltip (sem `*f` vararg)
- [x] Menu / menubar
- [x] Style (`style_from_table`, cursor, `style_push` com slots nomeados)
- [x] Color helpers (já nos types)
- [x] Image / nine-slice (`Host.image`, `Image#nine_slice`)
- [x] Font (`Granada.app font:, font_size:`; default atlas se omitir)
- [x] Canvas (`widget_alloc`, `fill_rect`, `stroke_*`, `draw_text`)
- [ ] Math / rect / vec helpers extras
- [ ] Buffer / string / utf-8 (só o que Native precisa; resto `skip` no mapa)

## Fase D — Host GLFW + OpenGL 3

- [x] `src/granada_host.c` separado do core (opcional via pkg-config)
- [x] `Granada.app` loop (poll → frame → yield → render)
- [x] Font stash (default atlas no `nk_glfw3_font_stash_*`)
- [x] Esc / Cmd+Q / Ctrl+Q
- [x] `examples/hello.rb` abre janela quando o host existe

## Fase E — DSL

- [x] `Granada::UI` com `instance_eval`
- [x] `window` / `row` / widgets com kwargs
- [x] Estado in/out (checkbox, slider, property devolvem valor)
- [x] `docs/dsl.md` completo
- [x] `examples/kitchen_sink.rb`

## Fase F — polish

- [x] `docs/architecture.md` / `building-uis.md` / `mruby4.md` alinhados ao código
- [x] CI GitHub Actions (macOS + Ubuntu) — instala glfw/glew
- [x] README com exemplo rodando
