project('uipp', 'cpp',
        version:         '0.1.0',
        meson_version:   '>=1.3.0',
        default_options: [ 'cpp_std=c++23', 'warning_level=3' ])

cxx = meson.get_compiler('cpp')

compile_args = [ '-DUIPP_BUILDING' ]
include_dirs = include_directories('include')

subdir('include/uipp')
subdir('src')

built_lib = get_option('default_library')

library = library(meson.project_name(), src,
                  gnu_symbol_visibility: 'hidden',
                  include_directories:   include_dirs,
                  cpp_args:              compile_args,
                  cpp_shared_args:       compile_args + ['-DUIPP_SHARED'],
                  version:               meson.project_version(),
                  install:               true)

if built_lib == 'both'
    pc_target = library.get_shared_lib()
elif built_lib == 'shared'
    pc_target = library
endif

if built_lib.contains('shared') or built_lib.contains('both')
    pc = import('pkgconfig')
    pc.generate(pc_target,
                description: 'A C++23 GUI library made to be extensible, modular and beautiful.',
                version:      meson.project_version(),
                name:        'uipp')
endif

install_subdir('include/uipp', install_dir: get_option('includedir'))

uipp_dep = declare_dependency(link_with: library, include_directories: include_dirs)

if get_option('build-test')
    subdir('test')
endif