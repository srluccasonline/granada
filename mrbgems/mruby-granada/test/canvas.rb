assert('Granada list_view canvas style nine_slice') do
  ctx = Granada::Context.new
  ctx.input_begin
  ctx.input_end

  seen = []
  painted = false
  pushed = false

  ctx.begin("cv", Granada::Rect.new(0, 0, 420, 360)) do
    ctx.layout_row_dynamic(80, 1)
    ctx.list_view("rows", 22, 20) do |i|
      seen << i
      ctx.layout_row_dynamic(22, 1)
      ctx.label("row #{i}")
    end

    ctx.layout_row_dynamic(60, 1)
    bounds = ctx.widget_alloc
    ctx.fill_rect(bounds, Granada::Color.rgb(30, 30, 40), 4)
    ctx.stroke_rect(bounds, Granada::Color.rgb(220, 20, 60), 1.5, 4)
    ctx.stroke_line(bounds.x, bounds.y, bounds.x + bounds.w, bounds.y + bounds.h, Granada::Color.rgb(255, 255, 255), 1)
    ctx.fill_circle(Granada::Rect.new(bounds.x + 8, bounds.y + 8, 16, 16), Granada::Color.rgb(220, 20, 60))
    ctx.draw_text(bounds, "canvas", Granada::Color.rgb(255, 255, 255))
    painted = bounds.w > 0

    ctx.layout_row_dynamic(28, 1)
    ctx.style_push("button.rounding", 8.0) do
      pushed = true
      ctx.button_label("round")
    end
  end

  assert_true(seen.length > 0)
  assert_equal(0, seen[0])
  assert_true(painted)
  assert_true(pushed)

  slice = Granada::Image.id(1).nine_slice(4, 4, 4, 4)
  assert_kind_of(Granada::NineSlice, slice)
  via_native = Granada::Native.nine_slice_id(2, 1, 2, 3, 4)
  assert_kind_of(Granada::NineSlice, via_native)

  ctx.clear
  ctx.free
end

assert('Granada::UI list_view and canvas') do
  ctx = Granada::Context.new
  ctx.input_begin
  ctx.input_end
  ui = Granada::UI.new(ctx, width: 400, height: 300)
  n = 0
  ui.window("dsl-cv", fill: true) do
    ui.list_view("items", 12, row_height: 20, height: 80) do |i|
      n += 1
      ui.row height: 20, cols: 1 do
        ui.label "item #{i}"
      end
    end
    ui.canvas height: 50 do |r|
      ui.fill_rect r, Granada::Color.rgb(10, 10, 12)
    end
    ui.style_push("button.rounding", 2.0) do
      ui.button "ok"
    end
  end
  assert_true(n > 0)
  ctx.clear
  ctx.free
end
