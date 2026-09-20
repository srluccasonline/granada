# Sanity check: the gem is linked into mruby.
# A windowed demo lands with the GLFW host (Phase D).
#
#   make hello

puts "Granada #{Granada::VERSION} (Nuklear #{Granada::NUKLEAR_VERSION})"

stone = Granada::Native.rgb(220, 20, 60)
puts "gemstone: ##{stone.hex}  #{stone.inspect}"

ctx = Granada::Context.new
puts "context:  #{ctx.alive?}"
ctx.free
puts "freed:    #{!ctx.alive?}"
