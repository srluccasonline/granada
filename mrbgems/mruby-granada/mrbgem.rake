MRuby::Gem::Specification.new('mruby-granada') do |spec|
  spec.license = 'Apache-2.0'
  spec.author  = 'Luccas Brandão Bezerra'
  spec.summary = 'Nuklear immediate-mode GUI bindings for mruby 4.x'
  spec.version = '0.1.0'

  repo_root = File.expand_path('../..', spec.dir)
  nuklear   = File.join(repo_root, 'vendor/nuklear')

  spec.cc.include_paths << nuklear
  spec.cc.include_paths << File.join(nuklear, 'demo/glfw_opengl3')
  spec.cc.include_paths << File.join(repo_root, 'vendor/stb')
  spec.cc.include_paths << File.join(spec.dir, 'include')

  spec.cc.flags << '-Wno-unused-function'
  spec.cc.flags << '-Wno-unused-parameter'
  spec.cc.flags << '-Wno-sign-compare'
  spec.cc.flags << '-Wno-deprecated-declarations'

  unless RUBY_PLATFORM =~ /darwin/
    spec.linker.libraries << 'm'
  end

  has_glfw = system('pkg-config --exists glfw3 >/dev/null 2>&1')
  has_glew = system('pkg-config --exists glew >/dev/null 2>&1')
  if has_glfw && has_glew
    spec.cc.defines << 'GRANADA_HAS_GLFW'
    spec.cc.flags.concat(`pkg-config --cflags glfw3 glew`.split)
    spec.linker.flags.concat(`pkg-config --libs glfw3 glew`.split)
    if RUBY_PLATFORM =~ /darwin/
      spec.linker.flags << '-framework' << 'OpenGL'
    else
      spec.linker.libraries << 'GL'
    end
  end
end
