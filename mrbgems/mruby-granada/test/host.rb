assert('Granada::Host is defined') do
  assert_true(Granada.const_defined?(:Host))
  assert_true(Granada::Host.respond_to?(:available?))
  assert_true(Granada::Host.respond_to?(:run))
  assert_true(Granada::Host.respond_to?(:quit!))
end

assert('Granada::Host.size is a pair') do
  s = Granada::Host.size
  assert_equal(2, s.length)
end

assert('Granada::Host.image without a window raises') do
  assert_raise(RuntimeError) { Granada::Host.image("missing.png") }
end
