assert('Granada widgets: label button checkbox slider property edit') do
  ctx = Granada::Context.new
  ctx.input_begin
  ctx.input_end

  clicked = false
  checked = false
  vol = 0.0
  count = 0
  name = "Ada"
  events = 0

  ctx.begin("widgets", Granada::Rect.new(0, 0, 420, 360)) do
    ctx.layout_row_dynamic(28, 1)
    ctx.label("hello")
    ctx.label("center", Granada::TEXT_CENTERED)
    ctx.label_wrap("a long wrapping label")
    clicked = ctx.button_label("Ok")
    ctx.button("also") { clicked = true }
    checked = ctx.checkbox_label("On", false)
    checked = ctx.check_label("Off", true)
    vol = ctx.slider_float(0.0, 0.5, 1.0, 0.01)
    count = ctx.propertyi("#int", 0, 3, 10, 1, 1.0)
    events = ctx.edit_string(name, Granada::EDIT_FIELD, 64, :default)
    ctx.progress(40, 100)
    ctx.option_label("A", true)
    ctx.option_label("B", false)
    ctx.select_label("pick", Granada::TEXT_LEFT, false)
    ctx.value_int("n", 7)
    ctx.spacer
  end

  assert_equal(false, clicked)
  assert_kind_of(Float, vol)
  assert_true(vol >= 0.0)
  assert_equal(3, count)
  assert_equal("Ada", name)
  assert_kind_of(Integer, events)
  assert_true(ctx.window_exists?("widgets"))

  ctx.clear
  ctx.free
end

assert('Granada::Native.button_label forwards') do
  ctx = Granada::Native.init_default
  ctx.input_begin
  ctx.input_end
  saw = false
  Granada::Native.begin(ctx, "nb", Granada::Rect.new(0, 0, 200, 120)) do
    Granada::Native.layout_row_dynamic(ctx, 24, 1)
    Granada::Native.label(ctx, "via native")
    saw = Granada::Native.button_label(ctx, "Go")
  end
  assert_equal(false, saw)
  Granada::Native.free(ctx)
end

assert('Granada widget disable begin/end with block') do
  ctx = Granada::Context.new
  ctx.input_begin
  ctx.input_end
  ctx.begin("dis", Granada::Rect.new(0, 0, 200, 120)) do
    ctx.layout_row_dynamic(24, 1)
    ctx.disable do
      ctx.button_label("no")
    end
    assert_true(true)
  end
  ctx.clear
  ctx.free
end
