assert('Granada::Vec2') do
  v = Granada::Vec2.new(1.5, 2.5)
  assert_equal(1.5, v.x)
  assert_equal(2.5, v.y)
  v.x = 3.0
  assert_equal(3.0, v.x)
  assert_equal([3.0, 2.5], v.to_a)
  assert_true(v == Granada::Vec2.new(3.0, 2.5))
  assert_false(v == Granada::Vec2.new(0, 0))
  n = Granada::Native.vec2(4, 5)
  assert_kind_of(Granada::Vec2, n)
  assert_equal(4.0, n.x)
  i = Granada::Native.vec2i(8, 9)
  assert_equal(8.0, i.x)
  assert_equal(9.0, i.y)
end

assert('Granada::Rect') do
  r = Granada::Rect.new(10, 20, 100, 50)
  assert_equal(10.0, r.x)
  assert_equal(20.0, r.y)
  assert_equal(100.0, r.w)
  assert_equal(50.0, r.h)
  assert_equal(100.0, r.width)
  assert_equal([10.0, 20.0, 100.0, 50.0], r.to_a)
  assert_equal(Granada::Vec2.new(10, 20), r.pos)
  assert_equal(Granada::Vec2.new(100, 50), r.size)
  via_native = Granada::Native.rect(1, 2, 3, 4)
  assert_equal(Granada::Rect.new(1, 2, 3, 4), via_native)
  composed = Granada::Native.recta(Granada::Vec2.new(1, 2), Granada::Vec2.new(3, 4))
  assert_equal(Granada::Rect.new(1, 2, 3, 4), composed)
  null = Granada::Native.get_null_rect
  assert_kind_of(Granada::Rect, null)
end

assert('Granada::Color') do
  c = Granada::Color.rgb(255, 0, 128)
  assert_equal(255, c.r)
  assert_equal(0, c.g)
  assert_equal(128, c.b)
  assert_equal(255, c.a)
  c2 = Granada::Native.rgba(1, 2, 3, 4)
  assert_equal([1, 2, 3, 4], c2.to_a)
  hex = Granada::Native.rgb_hex('#ff0000')
  assert_equal(255, hex.r)
  assert_equal(0, hex.g)
  assert_equal(0, hex.b)
  assert_equal('FF0000', hex.hex)
  from_f = Granada::Native.rgb_f(1.0, 0.0, 0.0)
  assert_equal(255, from_f.r)
  cf = c.to_colorf
  assert_kind_of(Granada::ColorF, cf)
  assert_true((cf.r - 1.0).abs < 0.01)
end

assert('Granada::ColorF') do
  f = Granada::ColorF.new(0.25, 0.5, 0.75, 1.0)
  assert_equal(0.25, f.r)
  c = f.to_color
  assert_kind_of(Granada::Color, c)
  back = Granada::Native.rgba_cf(f)
  assert_kind_of(Granada::Color, back)
end

assert('Granada::Image') do
  img = Granada::Image.id(7)
  assert_equal(7, img.id)
  assert_false(img.subimage?)
  n = Granada::Native.image_id(9)
  assert_equal(9, n.id)
end
