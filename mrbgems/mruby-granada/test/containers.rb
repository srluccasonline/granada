assert('Granada group tree chart combo menu') do
  ctx = Granada::Context.new
  ctx.input_begin
  ctx.input_end

  grouped = false
  treed = false
  combo_i = 0

  ctx.begin("c", Granada::Rect.new(0, 0, 480, 400)) do
    ctx.menubar_begin do
      ctx.layout_row_begin(Granada::STATIC, 25, 1)
      ctx.layout_row_push(80)
      ctx.menu_begin_label("File", Granada::TEXT_LEFT, Granada::Vec2.new(120, 80)) do
        ctx.layout_row_dynamic(22, 1)
        ctx.menu_item_label("Quit")
      end
      ctx.layout_row_end
    end

    ctx.layout_row_dynamic(80, 1)
    ctx.group_begin("g") do
      grouped = true
      ctx.layout_row_dynamic(22, 1)
      ctx.label("inside group")
    end

    ctx.layout_row_dynamic(60, 1)
    ctx.tree_push_hashed(Granada::TREE_TAB, "Files", "files-id", Granada::MAXIMIZED) do
      treed = true
      ctx.layout_row_dynamic(22, 1)
      ctx.label("leaf")
    end

    ctx.layout_row_dynamic(40, 1)
    ctx.plot(Granada::CHART_LINES, [0.1, 0.4, 0.2, 0.9])
    combo_i = ctx.combo(["red", "green", "blue"], 1, 22, Granada::Vec2.new(160, 80))
  end

  assert_true(grouped)
  assert_true(treed)
  assert_equal(1, combo_i)
  ctx.clear
  ctx.free
end

assert('Granada group ensure closes after raise') do
  ctx = Granada::Context.new
  ctx.input_begin
  ctx.input_end
  assert_raise(RuntimeError) do
    ctx.begin("boom-g", Granada::Rect.new(0, 0, 200, 200)) do
      ctx.layout_row_dynamic(80, 1)
      ctx.group_begin("inner") do
        raise "boom"
      end
    end
  end
  ctx.clear
  ctx.input_begin
  ctx.input_end
  recovered = false
  ctx.begin("boom-g", Granada::Rect.new(0, 0, 200, 200)) do
    recovered = true
    ctx.layout_row_dynamic(16, 1)
  end
  assert_true(recovered)
  ctx.clear
  ctx.free
end
