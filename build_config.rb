# Build mruby 4.0.0 with the Granada gem compiled in.
# Invoked from the repo root via `make` (MRUBY_CONFIG points here).

MRuby::Build.new do |conf|
  if RUBY_PLATFORM =~ /darwin/
    conf.toolchain :clang
  else
    conf.toolchain :gcc
  end

  conf.gembox 'default'
  conf.enable_debug
  conf.enable_test

  conf.gem File.expand_path('mrbgems/mruby-granada', __dir__)
end
