# Granada Studio — UI completa de teste (DSL).
#   make studio
#   vendor/mruby/bin/mruby examples/studio.rb
#
# Esc / Ctrl+Q / Cmd+Q / File→Quit fecha. Não precisa de #free:
# Granada.app entrega o Context do host e o shutdown C limpa tudo.

raise "Granada was built without GLFW (brew install glfw glew && make)" unless Granada::Host.available?

RED   = Granada::Color.rgb(220, 20, 60)
DARK  = Granada::Color.rgb(24, 24, 32)
INK   = Granada::Color.rgb(255, 255, 255)
MUTED = Granada::Color.rgb(160, 160, 176)

@tab      = 0
@mute     = false
@vol      = 0.62
@gain     = 4
@name     = "Granada"
@device   = 0
@devices  = ["Default", "Headphones", "Monitor"]
@quality  = 1
@tint     = Granada::ColorF.new(0.86, 0.08, 0.24, 1.0)
@hist     = Array.new(40) { 0.15 }
@tracks   = (0...80).map { |i| "track %02d — take #{(i % 7) + 1}" % i }
@status   = "ready"

Granada.app title: "Granada Studio", width: 860, height: 620 do
  window "studio", fill: true do
    menubar do
      row height: 25, static: 70, cols: 2 do
        menu "File", size: Granada::Vec2.new(140, 90) do
          row height: 22, cols: 1 do
            menu_item("Reset") { @vol = 0.62; @mute = false; @status = "reset" }
            menu_item("Quit")  { quit }
          end
        end
        menu "Help", size: Granada::Vec2.new(160, 60) do
          row height: 22, cols: 1 do
            menu_item("About") { @tab = 3 }
          end
        end
      end
    end

    row height: 28, cols: 2 do
      label "Granada Studio  v#{Granada::VERSION}", align: :left, color: RED
      label @status, align: :right, color: MUTED
    end

    row height: 28, cols: 4 do
      @tab = 0 if option("Mixer",   @tab == 0)
      @tab = 1 if option("Library", @tab == 1)
      @tab = 2 if option("Canvas",  @tab == 2)
      @tab = 3 if option("About",   @tab == 3)
    end

    rule RED

    case @tab
    when 0
      row height: 28, cols: 2 do
        @mute = checkbox("Mute", @mute)
        label(@mute ? "output silent" : "output live", color: @mute ? MUTED : INK)
      end

      row height: 28, cols: 2 do
        label "volume"
        disable { slider(@vol, min: 0.0, max: 1.0) } if @mute
        @vol = slider(@vol, min: 0.0, max: 1.0) unless @mute
      end

      row height: 22, cols: 1 do
        progress((@mute ? 0.0 : @vol * 100).to_i, 100)
      end

      row height: 28, cols: 1 do
        @gain = property("#gain dB", @gain, min: -12, max: 12, step: 1)
      end

      row height: 28, cols: 2 do
        label "device"
        @device = combo(@devices, @device)
      end

      row height: 28, cols: 3 do
        @quality = 0 if option("Draft",  @quality == 0)
        @quality = 1 if option("Studio", @quality == 1)
        @quality = 2 if option("Master", @quality == 2)
      end

      row height: 28, cols: 1 do
        edit(@name)
      end

      row height: 90, cols: 1 do
        @hist.shift
        @hist.push(@mute ? 0.05 : (@vol * 0.7 + 0.1))
        plot @hist
      end

      row height: 110, cols: 1 do
        @tint = color_picker(@tint)
      end

      row height: 32, cols: 3 do
        style_push("button.rounding", 8.0) do
          button("Play") { @status = "playing #{@name}" }
          button("Stop") { @status = "stopped" }
          button("Quit") { quit }
        end
      end

    when 1
      row height: 70, cols: 1 do
        tree "Sessions", id: "sess-tree" do
          row height: 22, cols: 1 do
            label "2026-09 / demo.granada"
            label "#{@tracks.length} takes on disk"
          end
        end
      end

      list_view "library", @tracks.length, row_height: 22, height: 280 do |i|
        row height: 22, cols: 1 do
          label @tracks[i]
        end
      end

      row height: 32, cols: 2 do
        button("Load selected") { @status = "loaded take" }
        button("Delete") { @status = "noop — demo" }
      end

    when 2
      label "custom drawing — volume as a bar", color: MUTED
      canvas height: 220 do |r|
        fill_rect r, DARK, 8
        stroke_rect r, RED, 1.6, 8
        inner = Granada::Rect.new(r.x + 16, r.y + r.h * 0.35, (r.w - 32) * (@mute ? 0.0 : @vol), r.h * 0.3)
        fill_rect inner, @tint.to_color, 4
        cx = r.x + 28
        cy = r.y + 28
        fill_circle Granada::Rect.new(cx, cy, 18, 18), RED
        draw_text Granada::Rect.new(r.x + 52, r.y + 10, 200, 24),
                  "vol #{(@vol * 100).to_i}%", INK
      end
      row height: 28, cols: 1 do
        @vol = slider(@vol, min: 0.0, max: 1.0) unless @mute
      end

    else
      group "about" do
        row height: 24, cols: 1 do
          label "Granada #{Granada::VERSION}  (Nuklear #{Granada::NUKLEAR_VERSION})"
          label "Write the UI in Ruby. The host is C and per platform.", wrap: true
          label "This window never calls #free — Granada.app owns the context.", wrap: true
        end
      end
      row height: 32, cols: 1 do
        disable { button("Can't click — disabled") }
      end
      row height: 32, cols: 1 do
        button("Back to mixer") { @tab = 0 }
      end
    end
  end
end
