config = configuration_data()
config.set_quoted('UIPP_VERSION', meson.project_version())

configure_file(output:        'config.hh',
               configuration: config,
               install_dir:   get_option('includedir') / 'uipp')