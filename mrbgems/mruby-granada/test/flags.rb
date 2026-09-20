assert('Granada window flags') do
  assert_true(Granada::WINDOW_BORDER != 0)
  assert_true(Granada::WINDOW_MOVABLE != 0)
  assert_true((Granada::WINDOW_BORDER | Granada::WINDOW_TITLE) != Granada::WINDOW_BORDER)
end

assert('Granada text flags') do
  assert_true(Granada::TEXT_LEFT != 0)
  assert_true(Granada::TEXT_CENTERED != 0)
  assert_true(Granada::TEXT_RIGHT != 0)
end

assert('Granada keys and mouse') do
  assert_equal(0, Granada::KEY_NONE)
  assert_true(Granada::KEY_ENTER > Granada::KEY_NONE)
  assert_equal(0, Granada::MOUSE_LEFT)
  assert_true(Granada::MOUSE_RIGHT > Granada::MOUSE_LEFT)
end

assert('Granada layout / widget enums') do
  assert_true(Granada.const_defined?(:DYNAMIC))
  assert_true(Granada.const_defined?(:STATIC))
  assert_true(Granada.const_defined?(:TREE_NODE))
  assert_true(Granada.const_defined?(:SYMBOL_X))
end
