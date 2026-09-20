# mruby 4.0 — o que o binding Granada usa

Pin: tag **4.0.0** (`https://github.com/mruby/mruby`, 2026-04-20).
Não usamos master nem 4.1.0-rc: a DSL e o C ficam na superfície estável.

O PoC `nuklear_ruby` já puxava um tree 4.x no vendor, mas o C era um sketch de ~10 métodos e misturava GLFW no mesmo arquivo. Granada **não** reaproveita esse C.

## C API — cuidados

| 3.x / hábito antigo | 4.0 |
|---|---|
| `mrb_alloca()` | `mrb_temp_alloc()` |
| `mruby/ext/io.h` | `mruby/io.h` |
| `MRB_NO_PRESYM` | removido; presym **sempre** ligado |
| begin/end manual + `mrb_protect` | preferir `MRB_ENSURE(mrb, result, body, data) { cleanup }` |
| `mrb_open` ignora falha de init | checar `mrb->exc` / `MRB_OPEN_FAILURE()` |

`MRB_ENSURE` (em `mruby/error.h`) chama o body com `mrb_protect_error` e **sempre** executa o bloco seguinte — o `nk_end*` mora aí. Se o body levantou, o ensure re-raise depois do cleanup.

## Ruby 4 / mruby 4 que a DSL pode usar

- keyword arguments (`title:`, `align:`)
- pattern matching `case` / `in` (docs de UI, não obrigatório no core)
- trailing comma em parâmetros
- `&nil` para recusar bloco

Não usar sintaxe que só existe no 4.1 (brace-less interpolation `#$global`, etc.).

## Gem

Nome: `mruby-granada`

```
void mrb_mruby_granada_gem_init(mrb_state *mrb);
void mrb_mruby_granada_gem_final(mrb_state *mrb);
```

Build: `build_config.rb` + `make` clona a tag 4.0.0 em `vendor/mruby` (gitignored).

## Testes

`mrbgems/mruby-granada/test/*.rb` no formato `assert('nome') do ... end`.
`make test` → `rake test` do mruby com `conf.enable_test`.
