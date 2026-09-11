config = configuration_data()
config.set_quoted('UIPP_VERSION', meson.project_version())

configure_file(output:        'config.hh',
               configuration: config,
               install_dir:   get_option('includedir') / 'uipp')


headers = files('color.hh', 'draw_list.hh', 'export.hh', 'result.hh', 'surface.hh', 'window.hh')

subdir('math')
headers += math_headers

subdir('traits')
headers += traits_headers

subdir('platform')
headers += platform_headers

subdir('renderer')
headers += renderer_headers

install_headers(headers, preserve_path: true, subdir: 'uipp')