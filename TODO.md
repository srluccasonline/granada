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

- [ ] Types: Rect, Vec2, Color, ColorF, Image, NineSlice, Handle
- [ ] Flags / enums (WINDOW_*, TEXT_*, KEY_*, BUTTON_*, …)
- [ ] Context (init / clear / free)
- [ ] Input
- [ ] Drawing iterators (`nk__begin`, `nk_convert`, …)
- [ ] Window (`nk_begin` / `nk_end` + queries; `MRB_ENSURE`)
- [ ] Layout
- [ ] Groups
- [ ] Tree / list_view
- [ ] Widget queries / spacing / disable
- [ ] Text / label (sem `*f` vararg)
- [ ] Links
- [ ] Button
- [ ] Checkbox / radio / option
- [ ] Selectable
- [ ] Slider / knob / progress
- [ ] Color picker
- [ ] Property
- [ ] Edit (buffer gerenciado em Ruby)
- [ ] Chart
- [ ] Popup
- [ ] Combo
- [ ] Contextual
- [ ] Tooltip (sem `*f` vararg)
- [ ] Menu / menubar
- [ ] Style push/pop
- [ ] Color helpers
- [ ] Image / nine-slice
- [ ] Font atlas (o que o host precisa)
- [ ] Math / rect / vec helpers
- [ ] Buffer / string / utf-8 (só o que Native precisa; resto `skip` no mapa)

## Fase D — Host GLFW + OpenGL 3

- [ ] `src/host_glfw.c` separado do core
- [ ] `Granada.app` loop (poll → frame → yield → render)
- [ ] Font stash
- [ ] Esc / Cmd+Q / Ctrl+Q
- [ ] `examples/hello.rb` abre janela

## Fase E — DSL

- [ ] `Granada::UI` com `instance_eval`
- [ ] `window` / `row` / widgets com kwargs
- [ ] Estado in/out (checkbox, slider, property devolvem valor)
- [ ] `docs/dsl.md` completo
- [ ] `examples/kitchen_sink.rb`

## Fase F — polish

- [ ] `docs/architecture.md` / `building-uis.md` / `mruby4.md` alinhados ao código
- [x] CI GitHub Actions (macOS + Ubuntu) — workflow adicionado; ainda não validado no GitHub
- [ ] README com exemplo rodando
