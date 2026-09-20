assert('Granada::UI headless window/row/widgets') do
  ctx = Granada::Context.new
  ctx.input_begin
  ctx.input_end
  ui = Granada::UI.new(ctx, width: 400, height: 300)

  opened = false
  on = false
  vol = 0.25
  name = "Granada"
  n = 2

  ui.window("demo", fill: true) do
    opened = true
    ui.row height: 28, cols: 1 do
      ui.label "hello", align: :center
      ui.button("Ok")
      on = ui.checkbox("Enabled", on)
      vol = ui.slider(vol, min: 0.0, max: 1.0, step: 0.05)
      n = ui.property("#n", n, min: 0, max: 10, step: 1)
      ui.edit(name)
      ui.spacer
    end
  end

  assert_true(opened)
  assert_equal(false, on)
  assert_true(vol >= 0.0)
  assert_equal(2, n)
  assert_equal("Granada", name)
  ctx.clear
  ctx.free
end

assert('Granada.app without a block raises') do
  assert_raise(ArgumentError) { Granada.app }
end

assert('Granada::UI label with color accepts a string') do
  ctx = Granada::Context.new
  ctx.input_begin
  ctx.input_end
  ui = Granada::UI.new(ctx, width: 200, height: 100)
  ui.window("lbl", fill: true) do
    ui.label "tinted", align: :left, color: Granada::Color.rgb(220, 20, 60)
    ui.label nil, color: Granada::Color.rgb(255, 255, 255)
  end
  assert_true(true)
  ctx.clear
  ctx.free
end
