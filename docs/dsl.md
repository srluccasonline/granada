# DSL Granada

A DSL é a camada de cima: Ruby idiomático por cima de `Granada::Native`. **Ainda não está implementada** (Fase E). Este arquivo é o contrato para quando formos escrever UIs.

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

O bloco de `app` e o de `window` rodam com `instance_eval` em um `Granada::UI`, então `window`, `label`, `button` não precisam do prefixo `Granada.`.

## Regras

1. **Kwargs, não bitflags.** `border: true` em vez de `WINDOW_BORDER`.
2. **Blocos escondem begin/end.** `window { }` chama `nk_begin` / `nk_end` (com `MRB_ENSURE`).
3. **Estado in/out.** Widgets que no C recebem `T*` devolvem o valor novo. A aplicação guarda o estado.
4. **Button/selectable** devolvem `true` neste frame *ou* aceitam bloco.
5. **`window` sem x/y/w/h** preenche a janela nativa (`fill: true` implícito).
6. **Sem `nk_labelf`.** Use interpolação: `label "fps #{fps}"`.

## Mapa curto (alvo)

| DSL | Native |
|---|---|
| `app(...)` | Host loop |
| `window(name, **opts) { }` | `nk_begin` / `nk_end` |
| `row(height:, cols:) { }` | `nk_layout_row_dynamic` |
| `label(text, align:)` | `nk_label` |
| `button(text) { }` | `nk_button_label` |
| `checkbox(text, value)` | `nk_checkbox_label` → devolve bool |
| `slider(value, min:, max:, step:)` | `nk_slider_float` → devolve float |
| `property(name, value, min:, max:, step:)` | `nk_property_*` |
| `edit(text, **opts)` | `nk_edit_string` + buffer Ruby |
| `group(name) { }` | `nk_group_begin` / `nk_group_end` |
| `tree(id:, title:) { }` | `nk_tree_push_hashed` / `nk_tree_pop` |
| `quit` | fecha a janela do host |

Native continua público: `Granada::Native` e `Granada::Context` para quem quiser o C na cara.

## O que a DSL *não* é

Não é retained-mode. Não há `Button.new` que você reposiciona depois. Se o `if` que desenha um widget for falso neste frame, o widget some. Isso é Nuklear, não um bug.
