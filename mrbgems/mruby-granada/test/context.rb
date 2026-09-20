assert('Granada::Context init/clear/free') do
  ctx = Granada::Context.new
  assert_true(ctx.alive?)
  ctx.style_default
  ctx.clear
  assert_true(ctx.alive?)
  ctx.free
  assert_false(ctx.alive?)
  ctx.free # second free is a no-op
  assert_false(ctx.alive?)
end

assert('Granada::Native.init_default') do
  ctx = Granada::Native.init_default
  assert_kind_of(Granada::Context, ctx)
  assert_true(ctx.alive?)
  Granada::Native.clear(ctx)
  Granada::Native.free(ctx)
  assert_false(ctx.alive?)
end
