# Granada — Nuklear bindings for mruby 4.x
#
# VERSION and NUKLEAR_VERSION come from C. This file is the Ruby surface:
# Granada.app / Granada::UI (DSL) on top of Context + optional Host.

module Granada
  ALIGN = {
    left: TEXT_LEFT,
    center: TEXT_CENTERED,
    centred: TEXT_CENTERED,
    right: TEXT_RIGHT,
  }.freeze

  class UI
    attr_reader :ctx, :width, :height

    def initialize(ctx = nil, width: 800, height: 600)
      @ctx = ctx
      @width = width
      @height = height
    end

    def prepare!(ctx, width, height)
      @ctx = ctx
      @width = width
      @height = height
      self
    end

    def quit
      Host.quit!
    end

    def window(name, bounds = nil, **opts, &block)
      flags = window_flags(opts)
      rect = window_rect(bounds, opts)
      @ctx.begin(name, rect, flags, &block)
    end

    def row(height: 30, cols: 1, static: nil, ratios: nil, &block)
      if ratios
        @ctx.layout_row(DYNAMIC, height, ratios)
      elsif static
        @ctx.layout_row_static(height, static, cols)
      else
        @ctx.layout_row_dynamic(height, cols)
      end
      yield if block
    end

    def group(name, **opts, &block)
      @ctx.group_begin(name, window_flags(opts), &block)
    end

    def tree(title, id: title, type: TREE_TAB, state: MAXIMIZED, &block)
      @ctx.tree_push_hashed(type, title, id, state, &block)
    end

    def menubar(&block)
      @ctx.menubar_begin(&block)
    end

    def menu(title, size: Vec2.new(140, 200), align: TEXT_LEFT, &block)
      @ctx.menu_begin_label(title, align_value(align), size, &block)
    end

    def menu_item(title, align: TEXT_LEFT, &block)
      @ctx.menu_item_label(title, align_value(align), &block)
    end

    def label(text, align: :left, color: nil, wrap: false)
      text = text.to_s
      a = align_value(align)
      if wrap && color
        @ctx.label_colored_wrap(text, color)
      elsif wrap
        @ctx.label_wrap(text)
      elsif color
        @ctx.label_colored(text, a, color)
      else
        @ctx.label(text, a)
      end
    end

    def button(text, &block)
      @ctx.button_label(text, &block)
    end

    def checkbox(text, value)
      @ctx.checkbox_label(text, value)
    end

    def option(text, active)
      @ctx.option_label(text, active)
    end

    def selectable(text, value, align: TEXT_LEFT)
      @ctx.selectable_label(text, align_value(align), value)
    end

    def slider(value, min: 0.0, max: 1.0, step: 0.01)
      if value.is_a?(Float) || min.is_a?(Float) || max.is_a?(Float) || step.is_a?(Float)
        @ctx.slider_float(min, value, max, step)
      else
        @ctx.slider_int(min, value, max, step)
      end
    end

    def progress(value, max, modify: false)
      @ctx.progress(value, max, modify)
    end

    def property(name, value, min:, max:, step: 1, inc: nil)
      inc = step if inc.nil?
      if value.is_a?(Float)
        @ctx.propertyf(name, min, value, max, step, inc)
      else
        @ctx.propertyi(name, min, value, max, step, inc)
      end
    end

    def edit(text, flags: EDIT_FIELD, max: 256, filter: :default)
      @ctx.edit_string(text, flags, max, filter)
      text
    end

    def combo(items, selected, item_height: 25, size: Vec2.new(200, 200))
      @ctx.combo(items, selected, item_height, size)
    end

    def color_picker(color, format: RGBA)
      @ctx.color_picker(color, format)
    end

    def spacer
      @ctx.spacer
    end

    def spacing(cols)
      @ctx.spacing(cols)
    end

    def tooltip(text)
      @ctx.tooltip(text)
    end

    def rule(color = Color.rgb(220, 20, 60), rounding: false)
      @ctx.rule_horizontal(color, rounding)
    end

    def plot(values, type: CHART_LINES)
      @ctx.plot(type, values)
    end

    def list_view(id, count, row_height: 24, height: 180, **opts, &block)
      @ctx.layout_row_dynamic(height, 1)
      @ctx.list_view(id, row_height, count, window_flags(opts), &block)
    end

    def canvas(height: 120)
      row height: height, cols: 1 do
        bounds = @ctx.widget_alloc
        yield bounds
      end
    end

    def fill_rect(rect, color, rounding = 0)
      @ctx.fill_rect(rect, color, rounding)
    end

    def stroke_rect(rect, color, thickness = 1.0, rounding = 0)
      @ctx.stroke_rect(rect, color, thickness, rounding)
    end

    def stroke_line(x0, y0, x1, y1, color, thickness = 1.0)
      @ctx.stroke_line(x0, y0, x1, y1, color, thickness)
    end

    def fill_circle(rect, color)
      @ctx.fill_circle(rect, color)
    end

    def draw_text(rect, text, color, background = nil)
      if background
        @ctx.draw_text(rect, text, color, background)
      else
        @ctx.draw_text(rect, text, color)
      end
    end

    def style_push(slot, value, &block)
      @ctx.style_push(slot, value, &block)
    end

    def disable(&block)
      @ctx.disable(&block)
    end

    def image_file(path)
      Host.image(path)
    end

    def popup(name, bounds, type: POPUP_STATIC, **opts, &block)
      @ctx.popup_begin(type, name, bounds, window_flags(opts), &block)
    end

    private

    def align_value(align)
      return align if align.is_a?(Integer)
      ALIGN[align] || TEXT_LEFT
    end

    def window_flags(opts)
      flags = opts[:flags] || 0
      flags |= WINDOW_BORDER if opts[:border].nil? ? true : opts[:border]
      flags |= WINDOW_MOVABLE if opts[:movable].nil? ? true : opts[:movable]
      flags |= WINDOW_SCALABLE if opts[:scalable].nil? ? true : opts[:scalable]
      flags |= WINDOW_TITLE if opts[:title].nil? ? true : opts[:title]
      flags |= WINDOW_CLOSABLE if opts[:closable]
      flags |= WINDOW_MINIMIZABLE if opts[:minimizable]
      flags |= WINDOW_NO_SCROLLBAR if opts[:no_scrollbar]
      flags |= WINDOW_BACKGROUND if opts[:background]
      flags
    end

    def window_rect(bounds, opts)
      return bounds if bounds
      return Rect.new(opts[:x], opts[:y], opts[:w] || opts[:width], opts[:h] || opts[:height]) if opts[:x] && opts[:y]
      fill = opts[:fill]
      fill = true if fill.nil?
      if fill
        Rect.new(0, 0, @width, @height)
      else
        Rect.new(opts[:x] || 50, opts[:y] || 50, opts[:w] || opts[:width] || 400, opts[:h] || opts[:height] || 300)
      end
    end
  end

  # Native heap (nk_context + font atlas). GC also frees it; the block form is
  # the Ruby idiom so you never call #free by hand.
  class Context
    def self.open
      ctx = new
      return ctx unless block_given?
      begin
        yield ctx
      ensure
        ctx.free if ctx.alive?
      end
    end
  end

  def self.app(title: "Granada", width: 800, height: 600, vsync: true, font: nil, font_size: 13, &block)
    raise ArgumentError, "Granada.app requires a block" unless block
    unless Host.available?
      raise RuntimeError, "Granada was built without GLFW (install glfw3 + glew and rebuild)"
    end
    ui = UI.new(nil, width: width, height: height)
    Host.run(title, width, height, vsync, font, font_size.to_f) do |ctx, w, h|
      ui.prepare!(ctx, w, h)
      ui.instance_eval(&block)
    end
  end
end
