# Como construir UIs com Granada

Este guia é o ponto de partida quando formos desenhar telas de verdade (menus, HUD, editores). Granada é Nuklear: **immediate mode**. Se você vier de Qt, HTML ou de um scene graph, a regra muda.

## O loop

```
cada frame:
  1. o host lê mouse/teclado e chama nk_input_*
  2. o bloco Ruby de Granada.app roda de novo, do zero
  3. cada chamada de widget *declara* o que existe neste frame
  4. Nuklear gera comandos de desenho
  5. o host renderiza e troca o buffer
```

Não existe `on_click` registrado uma vez. `button("Ok")` retorna `true` **só no frame em que o clique aconteceu**.

```ruby
# todo frame este if é reavaliado
if button("Save")
  save_game(@state)
end
```

## Onde mora o estado

| Tipo de dado | Onde guardar |
|---|---|
| “o checkbox está ligado?” | ivar / local / struct da *aplicação* (`@vsync`) |
| texto do campo | `String` Ruby (`@name`) |
| valor do slider | `Float` / `Integer` (`@fov`) |
| “esta janela está aberta?” | bool da aplicação; se for falso, **não chame** `window` |
| estilo / tema | uma vez no host, ou `style_push` no frame |

Nuklear *também* guarda um pouco de estado interno (qual campo tem foco, scroll da janela, se uma árvore está aberta quando você usa a API hashed). Mesmo assim, trate a aplicação como a fonte da verdade para qualquer valor que você precise ler fora da UI.

## Layout

Nuklear não é CSS. Você declara linhas:

```ruby
row height: 32, cols: 2 do
  label "Volume"
  @volume = slider(@volume, min: 0.0, max: 1.0)
end
```

- `row` dinâmico: colunas dividem a largura
- `row_static`: largura fixa por item
- `group` / `tree`: regiões aninhadas com scroll próprio
- `window fill: true`: um painel do tamanho da janela nativa (bom para “tela cheia” de menu)

Se um label “centralizado” não parece no meio, falta altura na row. Texto alinhado ao centro vertical usa a altura da célula.

## Identidade de janelas e trees

`nk_begin` identifica a janela pelo **nome** (`"demo"`). Não crie nomes novos a cada frame (`"demo #{rand}"`) — o Nuklear perde o estado interno (posição, scroll).

Trees hashed precisam de um `id:` estável na DSL (arquivo/linha do C não atravessam o binding).

## Input e o jogo

`nk_item_is_any_active` (exposto depois no Native) diz se a UI “comeu” o clique. No jogo: se a UI está por cima, não atire neste frame.

## Estilo

Primeiro passo: `nk_style_from_table` / constantes de cor. Skinning com imagens (nine-slice, atlas) vem depois, quando uma tela concreta pedir. Não bloqueie o binding por causa de um tema.

## Checklist de uma tela nova

1. Qual estado a aplicação já tem? (lista de ivars)
2. Uma `window` por painel, nome estável
3. Rows de altura explícita
4. Widgets só lêem/escrevem esses ivars
5. Ações (salvar, fechar) no `if button` / bloco, não em callbacks guardados
6. Conferir o frame: abrir, clicar, reabrir — o estado Ruby ainda está certo?

Quando a DSL existir, os exemplos `examples/hello.rb` e `examples/kitchen_sink.rb` são o código a copiar. Até lá, Native + este guia.
