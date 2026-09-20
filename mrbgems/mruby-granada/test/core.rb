assert('Granada module is defined') do
  assert_true(Object.const_defined?(:Granada))
  assert_equal(Module, Granada.class)
end

assert('Granada::VERSION matches the gem') do
  assert_equal('0.1.0', Granada::VERSION)
end

assert('Granada::NUKLEAR_VERSION is the vendored Nuklear release') do
  assert_equal('4.13.3', Granada::NUKLEAR_VERSION)
end

assert('Granada::Native exists for 1:1 C bindings') do
  assert_true(Granada.const_defined?(:Native))
  assert_equal(Module, Granada::Native.class)
end

assert('Granada::UI exists as the DSL host object') do
  assert_true(Granada.const_defined?(:UI))
  assert_equal(Class, Granada::UI.class)
end
