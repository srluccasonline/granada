# Arquitetura — Granada

Granada é um wrapper mruby 4.x do Nuklear (immediate-mode, single-header C). O produto se chama **Granada** (a pedra vermelha); Nuklear é a biblioteca C por baixo. **Não existe módulo Ruby `Nuklear`.** Quem escreve UI fala `Granada.app`, `Granada::UI`, `Granada::Native`, `Granada::Context`.

## Camadas

```
Granada.app / Granada::UI     DSL Ruby (mrblib)
        │
Granada::Host                 GLFW + OpenGL 3 (opcional)
        │
Granada::Native               1:1 com nuklear.h
        │
nuklear.h v4.13.3             C, sem backend próprio
```

- **Native** não sabe de janela, OpenGL nem GLFW.
- **Host** cria o `nk_context`, injeta input, consome o command buffer.
- **DSL** esconde bitflags, begin/end e ponteiros C.

Testes do gem exercitam Native (e, quando fizer sentido, a DSL) **sem** GLFW.

## Immediate mode

O bloco passado a `Granada.app` **roda todo frame**. Widgets não são objetos persistentes. Estado da UI (checkbox ligado, texto do edit, posição de scroll que a app quer lembrar) vive em locais Ruby — variáveis, ivars, um hash — e é passado de volta para o widget a cada frame.

```ruby
# errado: guardar o botão
@ok = button("Ok")   # o retorno é "foi clicado neste frame?", não um widget

# certo: guardar o estado da aplicação
@volume = slider(@volume, min: 0.0, max: 1.0)
```

Ver `docs/building-uis.md`.

## Tipos Native

| C | Ruby |
|---|---|
| `struct nk_context*` | `Granada::Context` (`mrb_data_type`, `nk_free` no DFREE) |
| `struct nk_rect` | `Granada::Rect` |
| `struct nk_vec2` | `Granada::Vec2` |
| `struct nk_color` | `Granada::Color` |
| `struct nk_colorf` | `Granada::ColorF` |
| `struct nk_image` | `Granada::Image` |
| `nk_flags` / enums | Fixnum + constantes `Granada::WINDOW_BORDER` etc. |
| `nk_bool *` / `float *` | valor Ruby in, valor Ruby out (cópia no stack C no frame) |

Funções `nk_*f` / `va_list` **não** são bound: em Ruby se interpola a string.

Macros `nk_tree_push` usam `__FILE__`/`__LINE__` no C. No binding o id é explícito: `tree_push(id:, title:, ...)`.

Pares begin/end (`nk_begin`/`nk_end`, group, tree, popup, combo, menu) usam `MRB_ENSURE` para chamar o `*_end` se o bloco Ruby levantar.

## Flags de compilação do Nuklear

Definidas uma vez em `mrbgems/mruby-granada/include/granada_config.h` e incluídas **antes** de `nuklear.h` em todo `.c`. A implementação (`NK_IMPLEMENTATION`) vive só em `nuklear_impl.c`.

## Host

`host_glfw.c` (Fase D) liga GLFW 3 + o header oficial `nuklear_glfw_gl3.h`. Compila só se `pkg-config glfw3` existir. O core do gem continua útil sem isso.

## O que não entra no Native de primeira

- allocators custom (`nk_init` com `nk_allocator` próprio)
- `nk_plot_function` com callback C cru
- vertex layout completo de `nk_convert` (fica para quem escrever outro backend)
- plugins de filtro de edit além dos built-in do Nuklear
