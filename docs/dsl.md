# DSL Granada

A DSL é a camada de cima: Ruby idiomático por cima de `Granada::Context`. O bloco de `Granada.app` roda com `instance_eval` em um `Granada::UI` **reutilizado todo frame**. Ivars (`@vol`) são desse objeto: inicialize **dentro** do bloco (`@vol ||= 0.6`). Fora do `app` o `@vol` é outro objeto (o `main` do script) e no primeiro frame seria `nil`.

## Forma

```ruby
Granada.app title: "Granada", width: 800, height: 600 do
  window "demo", fill: true, border: true do
    row height: 32, cols: 2 do
      button("Ok") { quit }
      label "hello", align: :center
    end

    @on = checkbox("Enabled", @on)
    @vol = slider(@vol, min: 0.0, max: 1.0, step: 0.01)
  end
end
```

`Granada.app` exige o host GLFW (`Granada::Host.available?`). Sem GLFW, dá para instanciar `Granada::UI.new(ctx)` e chamar os mesmos métodos dentro de um `ctx.begin` headless (é o que os testes fazem).

## Regras

1. **Kwargs, não bitflags.** `border: true` em vez de `WINDOW_BORDER`.
2. **Blocos escondem begin/end.** `window { }` chama `nk_begin` / `nk_end` (com `MRB_ENSURE`).
3. **Estado in/out.** Widgets que no C recebem `T*` devolvem o valor novo. A aplicação guarda o estado.
4. **Button/selectable** devolvem `true` neste frame *ou* aceitam bloco.
5. **`window` sem x/y/w/h** preenche a janela nativa (`fill: true` implícito).
6. **Sem `nk_labelf`.** Use interpolação: `label "fps #{fps}"`.

## Mapa curto

| DSL | Native |
|---|---|
| `app(...)` | `Host.run` (GLFW loop) |
| `window(name, **opts) { }` | `nk_begin` / `nk_end` |
| `row(height:, cols:) { }` | `nk_layout_row_dynamic` |
| `row(static:, …)` | `nk_layout_row_static` |
| `label(text, align:)` | `nk_label` |
| `button(text) { }` | `nk_button_label` |
| `checkbox(text, value)` | `nk_checkbox_label` → devolve bool |
| `slider(value, min:, max:, step:)` | `nk_slider_float` / `nk_slider_int` |
| `property(name, value, min:, max:, step:)` | `nk_propertyi` / `nk_propertyf` |
| `edit(text, **opts)` | `nk_edit_string` (muta a String) |
| `combo(items, selected)` | `nk_combo` |
| `group(name) { }` | `nk_group_begin` / `nk_group_end` |
| `tree(id:, title:) { }` | `nk_tree_push_hashed` / `nk_tree_pop` |
| `menubar` / `menu` / `menu_item` | menubar + menu |
| `quit` | `Host.quit!` (Esc / Ctrl+Q / Cmd+Q também) |
| `list_view(id, count) { \|i\| }` | `nk_list_view_begin` / `end` (só as linhas visíveis) |
| `canvas(height:) { \|rect\| }` | `widget_alloc` + `fill_rect` / `stroke_*` / `draw_text` |
| `style_push("button.rounding", 8) { }` | `nk_style_push_*` / `pop_*` |
| `image_file("icon.png")` | `Host.image` (PNG/JPEG → textura do host) |
| `Granada.app font: "x.ttf", font_size: 16` | atlas TTF no host GLFW |

`Host.image` só funciona **dentro** de `Granada.app` (OpenGL já ligado). Guarde o `Image` numa ivar no primeiro frame.

Slots de `style_push`: `text.color`, `button.rounding`, `button.padding`, `button.text_normal`, `window.padding`, `window.rounding`, `window.background`, … (ver `granada_style.c`).

Native continua público: `Granada::Native` e `Granada::Context` para quem quiser o C na cara.

## Flags de `window`

| kwarg | default | C |
|---|---|---|
| `border:` | true | `WINDOW_BORDER` |
| `movable:` | true | `WINDOW_MOVABLE` |
| `scalable:` | true | `WINDOW_SCALABLE` |
| `title:` | true | `WINDOW_TITLE` |
| `closable:` | false | `WINDOW_CLOSABLE` |
| `minimizable:` | false | `WINDOW_MINIMIZABLE` |
| `no_scrollbar:` | false | `WINDOW_NO_SCROLLBAR` |
| `fill:` | true se não passar x/y | retângulo = tamanho da janela GLFW |

## O que a DSL *não* é

Não é retained-mode. Não há `Button.new` que você reposiciona depois. Se o `if` que desenha um widget for falso neste frame, o widget some. Isso é Nuklear, não um bug.
