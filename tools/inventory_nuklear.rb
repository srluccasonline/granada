#!/usr/bin/env ruby
# frozen_string_literal: true
#
# Parse vendor/nuklear/nuklear.h and write docs/api-map.md.
# Status starts as unbound; later phases update this file (or re-run and merge).
#
# Usage: ruby tools/inventory_nuklear.rb
#        (also `make inventory`)

require "fileutils"

ROOT = File.expand_path("..", __dir__)
HEADER = File.join(ROOT, "vendor/nuklear/nuklear.h")
OUT = File.join(ROOT, "docs/api-map.md")

abort "missing #{HEADER}" unless File.file?(HEADER)

SKIP_REASON = {
  vararg: "Ruby interpolates strings; not bound (`...` / va_list)",
}.freeze

def ruby_name(c_name)
  name = c_name.sub(/\A__/, "_")
  name = name.sub(/\Ank_/, "")
  name
end

def classify(_name, args)
  return :skip_vararg if args.include?("...") || args.include?("va_list")
  :bind
end

section = "Preamble"
sections = Hash.new { |h, k| h[k] = { functions: [], enums: [], structs: [] } }
pending_section = nil

File.foreach(HEADER) do |line|
  break if line.start_with?("#ifdef NK_IMPLEMENTATION")

  if pending_section
    # Banner body looks like: " *                                  CONTEXT"
    if (m = line.match(/^\s*\*\s+([A-Z][A-Z0-9][A-Z0-9 \/_-]{1,})\s*$/))
      title = m[1].strip.gsub(/\s+/, " ")
      unless title.match?(/\A[=*]+/)
        section = title.split.map(&:capitalize).join(" ")
      end
    elsif line.match?(%r{={10,}})
      pending_section = nil
    end
    next
  end

  if line.match?(%r{/\* ={10,}})
    pending_section = true
    next
  end

  if (m = line.match(/^\s*NK_API\s+(.+?)\s+(nk_\w+|nk__\w+)\s*\((.*)\)\s*;/))
    ret = m[1].gsub(/\s+/, " ").strip
    name = m[2]
    args = m[3].strip
    args = args.sub(/\s*NK_PRINTF_\w+\s*\([^)]*\)\s*\z/, "").strip
    kind = classify(name, args)
    sections[section][:functions] << {
      ret: ret,
      name: name,
      args: args,
      ruby: ruby_name(name),
      kind: kind,
      status: kind == :bind ? "unbound" : "skip",
    }
    next
  end

  if (m = line.match(/^\s*(?:typedef\s+)?enum\s+(nk_\w+)/))
    sections[section][:enums] << m[1]
    next
  end

  if (m = line.match(/^\s*(?:typedef\s+)?struct\s+(nk_\w+)/))
    struct = m[1]
    unless sections[section][:structs].include?(struct)
      sections[section][:structs] << struct
    end
  end
end

total_fn = sections.values.sum { |s| s[:functions].size }
bindable = sections.values.sum { |s| s[:functions].count { |f| f[:kind] == :bind } }
skipped = total_fn - bindable
total_en = sections.values.sum { |s| s[:enums].uniq.size }
total_st = sections.values.sum { |s| s[:structs].uniq.size }

FileUtils.mkdir_p(File.dirname(OUT))

File.open(OUT, "w") do |io|
  io.puts "# API map — Nuklear v4.13.3 → Granada"
  io.puts
  io.puts "Gerado por `tools/inventory_nuklear.rb` a partir de `vendor/nuklear/nuklear.h`."
  io.puts "Não edite a tabela de funções à mão: rode `make inventory` de novo depois de atualizar o header."
  io.puts "Status: `unbound` (ainda não ligado), `native` (Granada::Native), `dsl` (também na DSL), `skip` (proposital)."
  io.puts
  io.puts "- Funções `NK_API`: **#{total_fn}** (#{bindable} para bind, #{skipped} skip vararg/printf)"
  io.puts "- Enums nomeados: **#{total_en}**"
  io.puts "- Structs nomeados: **#{total_st}**"
  io.puts
  io.puts "## Status global"
  io.puts
  io.puts "| Seção | Funções | unbound | native | dsl | skip |"
  io.puts "|---|---:|---:|---:|---:|---:|"

  sections.each do |name, data|
    fns = data[:functions]
    next if fns.empty? && data[:enums].empty? && data[:structs].empty?
    counts = Hash.new(0)
    fns.each { |f| counts[f[:status]] += 1 }
    io.puts "| #{name} | #{fns.size} | #{counts["unbound"]} | #{counts["native"]} | #{counts["dsl"]} | #{counts["skip"]} |"
  end

  sections.each do |name, data|
    fns = data[:functions]
    next if fns.empty? && data[:enums].empty? && data[:structs].empty?

    io.puts
    io.puts "## #{name}"
    io.puts
    unless data[:structs].empty?
      io.puts "Structs: " + data[:structs].uniq.map { |s| "`#{s}`" }.join(", ")
      io.puts
    end
    unless data[:enums].empty?
      io.puts "Enums: " + data[:enums].uniq.map { |s| "`#{s}`" }.join(", ")
      io.puts
    end
    next if fns.empty?

    io.puts "| Status | C | Ruby Native | Retorno |"
    io.puts "|---|---|---|---|"
    fns.each do |f|
      note = f[:kind] == :skip_vararg ? " (#{SKIP_REASON[:vararg]})" : ""
      io.puts "| `#{f[:status]}` | `#{f[:name]}` | `#{f[:ruby]}` | `#{f[:ret]}`#{note} |"
    end
  end
end

puts "wrote #{OUT}"
puts "  functions=#{total_fn} bindable=#{bindable} skip=#{skipped} enums=#{total_en} structs=#{total_st} sections=#{sections.size}"
