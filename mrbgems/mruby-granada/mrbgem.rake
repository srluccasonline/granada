MRuby::Gem::Specification.new('mruby-granada') do |spec|
  spec.license = 'Apache-2.0'
  spec.author  = 'Luccas Brandão Bezerra'
  spec.summary = 'Nuklear immediate-mode GUI bindings for mruby 4.x'
  spec.version = '0.1.0'

  repo_root = File.expand_path('../..', spec.dir)
  nuklear   = File.join(repo_root, 'vendor/nuklear')

  spec.cc.include_paths << nuklear
  spec.cc.include_paths << File.join(spec.dir, 'include')

  spec.cc.flags << '-Wno-unused-function'
  spec.cc.flags << '-Wno-unused-parameter'
  spec.cc.flags << '-Wno-sign-compare'

  unless RUBY_PLATFORM =~ /darwin/
    spec.linker.libraries << 'm'
  end
end
