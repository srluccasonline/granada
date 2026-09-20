assert('Granada::Context begin/end with layout') do
  ctx = Granada::Context.new
  ctx.input_begin
  ctx.input_end

  opened = false
  w = 0.0
  h = 0.0
  result = ctx.begin("demo", Granada::Rect.new(10, 20, 400, 300), 0) do
    opened = true
    w = ctx.window_width
    h = ctx.window_height
    ctx.layout_row_dynamic(32, 1)
    ctx.spacer
    ctx.layout_row_static(24, 80, 2)
    ctx.spacer
    ctx.spacer
    true
  end

  assert_true(opened)
  assert_true(result)
  assert_true(w > 0)
  assert_true(h > 0)
  assert_true(ctx.window_exists?("demo"))

  ctx.clear
  ctx.free
end

assert('Granada window begin without block needs end') do
  ctx = Granada::Context.new
  ctx.input_begin
  ctx.input_end
  open = ctx.begin("manual", Granada::Rect.new(0, 0, 200, 200))
  assert_true(open)
  ctx.layout_row_dynamic(20, 1)
  ctx.end
  ctx.clear
  ctx.free
end

assert('Granada begin ensure calls nk_end after raise') do
  ctx = Granada::Context.new
  ctx.input_begin
  ctx.input_end
  assert_raise(RuntimeError) do
    ctx.begin("boom", Granada::Rect.new(0, 0, 200, 200)) do
      raise "boom"
    end
  end
  ctx.clear
  ctx.input_begin
  ctx.input_end
  recovered = false
  ctx.begin("boom", Granada::Rect.new(0, 0, 200, 200)) do
    recovered = true
    ctx.layout_row_dynamic(16, 1)
  end
  assert_true(recovered)
  ctx.clear
  ctx.free
end

assert('Granada::Native.begin forwards to Context') do
  ctx = Granada::Native.init_default
  ctx.input_begin
  ctx.input_end
  saw = false
  Granada::Native.begin(ctx, "via-native", Granada::Rect.new(0, 0, 180, 120)) do
    saw = true
    Granada::Native.layout_row_dynamic(ctx, 30, 1)
  end
  assert_true(saw)
  Granada::Native.free(ctx)
end
