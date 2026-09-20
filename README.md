# Granada

Bindings **mruby 4.x** para [Nuklear](https://github.com/Immediate-Mode-UI/Nuklear) — toolkit immediate-mode em C, um único header.

O nome é a pedra vermelha.

Autor: **Luccas Brandão Bezerra**
Licença: **Apache 2.0** (Nuklear continua MIT / public domain; ver `NOTICE`)

## O que é

A API Ruby se chama **`Granada`**, nunca `Nuklear`. Nuklear é só a lib C vendored (`vendor/nuklear/nuklear.h`). `nk_begin` vira `Granada::Native.begin` (e `window` na DSL). A versão do C aparece em `Granada::NUKLEAR_VERSION`.

Três camadas, de baixo para cima:

1. **`Granada::Native`** — mapeamento 1:1 de `nuklear.h` v4.13.3
2. **`Granada::Host`** — janela + input + render (GLFW + OpenGL 3, opcional)
3. **DSL Ruby** — `Granada.app { window { button "Ok" } }`

O estado de cada função C está em [`docs/api-map.md`](docs/api-map.md). O checklist vivo é o [`TODO.md`](TODO.md).

## Versões pinadas

| Peça | Versão |
|---|---|
| Nuklear | v4.13.3 (`vendor/nuklear/nuklear.h`) |
| mruby | **4.0.0** (clonado em `vendor/mruby` no `make`, não commitado) |
| Host | GLFW 3 + OpenGL 3 (opcional; `pkg-config glfw3 glew`) |

mruby 4.0 é a tag estável. O PoC antigo em `nuklear_ruby` **não** é copiado: aquele C mistura host GLFW com uma fatia mínima da API. Granada reescreve os bindings contra a C API do mruby 4.0 (`MRB_ENSURE`, sem `mrb_alloca`, presym sempre ligado).

## Requisitos

- Ruby ≥ 2.7 para *buildar* o mruby (no macOS: Homebrew `ruby`, hoje 4.x)
- `clang` / Xcode CLT ou `gcc`
- `git`
- Para o host (janela): `glfw` + `glew` (`brew install glfw glew`)

## Build

```sh
make
```

Clona mruby 4.0.0, compila o gem `mruby-granada` (incluindo a implementação do Nuklear) e deixa `vendor/mruby/bin/mruby` com o módulo `Granada` linkado.

```sh
make hello      # janela GLFW, ou smoke headless se o host não compilou
make kitchen    # examples/kitchen_sink.rb
make test       # testes mruby do gem (não abrem janela)
make inventory  # regenera docs/api-map.md a partir de nuklear.h
```

## Uso

```ruby
Granada.app title: "Granada", width: 800, height: 600 do
  window "demo", fill: true do
    row height: 32, cols: 2 do
      button("Ok") { quit }
      label "hello", align: :center
    end
    @on = checkbox("Enabled", @on)
    @vol = slider(@vol, min: 0.0, max: 1.0)
    list_view "rows", 50, height: 120 do |i|
      label "row #{i}"
    end
  end
end

# opcional: Granada.app font: "MyFont.ttf", font_size: 16
# imagens: @icon ||= image_file("icon.png")  # só dentro do app (host GL)
```

`Granada::Native` e `Granada::Context` são o mapeamento 1:1. A DSL (`Granada.app` / `Granada::UI`) é o caminho usual. Sem GLFW, `Granada::Host.available?` é `false` e os testes exercitam Native headless.

## Documentação

- [`docs/architecture.md`](docs/architecture.md) — camadas, tipos, ciclo de frame
- [`docs/api-map.md`](docs/api-map.md) — cada `NK_API` → Ruby
- [`docs/dsl.md`](docs/dsl.md) — DSL idiomática (`Granada.app` / `Granada::UI`)
- [`docs/building-uis.md`](docs/building-uis.md) — como pensar UI em immediate mode
- [`docs/mruby4.md`](docs/mruby4.md) — notas da C API mruby 4.0 que o binding usa

## Layout

```
mrbgems/mruby-granada/   gem C + mrblib
vendor/nuklear/          nuklear.h v4.13.3 + GLFW GL3 backend + LICENSE
tools/inventory_nuklear.rb
examples/
docs/
```

## Licença

Apache License 2.0. Copyright 2026 Luccas Brandão Bezerra.
