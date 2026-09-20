# Exercise the DSL: window, row, widgets, group, tree, combo, property, edit.
#   vendor/mruby/bin/mruby examples/kitchen_sink.rb

raise "Granada was built without GLFW" unless Granada::Host.available?

@on = true
@vol = 0.35
@count = 4
@name = "Granada"
@choice = 0
@items = ["ruby", "mruby", "nuklear"]

Granada.app title: "Granada kitchen sink", width: 720, height: 520 do
  window "sink", fill: true do
    menubar do
      row height: 25, static: 80, cols: 1 do
        menu "File", size: Granada::Vec2.new(140, 80) do
          row height: 22, cols: 1 do
            menu_item("Quit") { quit }
          end
        end
      end
    end

    row height: 28, cols: 2 do
      label "kitchen sink", align: :left
      button("Close") { quit }
    end

    row height: 28, cols: 1 do
      @on = checkbox("Enabled", @on)
    end
    row height: 28, cols: 2 do
      label "volume"
      @vol = slider(@vol, min: 0.0, max: 1.0)
    end
    row height: 28, cols: 1 do
      @count = property("#count", @count, min: 0, max: 20, step: 1)
    end
    row height: 28, cols: 1 do
      edit(@name)
    end
    row height: 28, cols: 1 do
      @choice = combo(@items, @choice)
    end

    row height: 120, cols: 1 do
      group "notes" do
        row height: 22, cols: 1 do
          label "immediate mode: this block runs every frame"
          label "state lives in Ruby ivars"
        end
      end
    end

    row height: 80, cols: 1 do
      tree "More", id: "more-tab" do
        row height: 22, cols: 1 do
          label "tree id is stable across frames"
        end
      end
    end

    list_view "rows", 40, row_height: 22, height: 90 do |i|
      row height: 22, cols: 1 do
        label "row #{i}"
      end
    end

    canvas height: 64 do |r|
      fill_rect r, Granada::Color.rgb(24, 24, 32), 6
      stroke_rect r, Granada::Color.rgb(220, 20, 60), 1.5, 6
    end
  end
end
