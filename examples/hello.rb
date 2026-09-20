# Windowed hello. Requires a Granada build with GLFW + GLEW.
# Headless smoke path if the host was not compiled in.
#
#   make hello

puts "Granada #{Granada::VERSION} (Nuklear #{Granada::NUKLEAR_VERSION})"
puts "host:    #{Granada::Host.available? ? 'GLFW+GL3' : 'not built'}"

if Granada::Host.available?
  Granada.app title: "Granada", width: 640, height: 420 do
    @on = true if @on.nil?
    @vol ||= 0.6
    window "demo", fill: true, border: true do
      row height: 32, cols: 2 do
        label "Granada", align: :center
        button("Quit") { quit }
      end
      row height: 28, cols: 1 do
        @on = checkbox("Enabled", @on)
        @vol = slider(@vol, min: 0.0, max: 1.0, step: 0.01)
        label "volume #{@vol}"
      end
    end
  end
else
  stone = Granada::Native.rgb(220, 20, 60)
  puts "gemstone: ##{stone.hex}  #{stone.inspect}"
  Granada::Context.open do |ctx|
    puts "context:  #{ctx.alive?}"
  end
  puts "(Context.open frees the native heap for you)"
  puts "(rebuild with glfw3 + glew to open a window)"
end
