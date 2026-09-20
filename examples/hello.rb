# Phase A sanity check: the gem is linked into mruby.
# A windowed demo lands with the GLFW host (Phase D).
#
#   make hello

puts "Granada #{Granada::VERSION} (Nuklear #{Granada::NUKLEAR_VERSION})"
puts "Native: #{Granada::Native}"
puts "UI:     #{Granada::UI}"
