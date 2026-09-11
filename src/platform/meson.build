platform_src = files()

if get_option('platform-sdl3')
    platform_src += files('sdl3.cc')
    dependencies += [ dependency('sdl3', fallback: [ 'sdl3', 'sdl3_dep' ]),
                      dependency('sdl3_ttf', fallback: [ 'sdl3_ttf', 'sdl3_ttf_dep' ]) ]
endif