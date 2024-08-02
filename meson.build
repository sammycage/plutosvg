project('plutosvg', 'c',
    version: '0.0.1',
    license: 'MIT',
    meson_version: '>=0.59.0',
    default_options: ['c_std=c99']
)

plutovg_dep = dependency('plutovg',
    required: true,
    fallback: ['plutovg', 'plutovg_dep']
)

plutosvg_compile_args = []
if get_option('default_library') == 'static'
    plutosvg_compile_args += ['-DPLUTOSVG_BUILD_STATIC']
    add_project_arguments('-DPLUTOSVG_BUILD_STATIC', language: ['c', 'cpp'])
endif

plutosvg_lib = library('plutosvg', 'source/plutosvg.c',
    include_directories: include_directories('source'),
    dependencies: plutovg_dep,
    version: meson.project_version(),
    c_args: ['-DPLUTOSVG_BUILD'],
    cpp_args: ['-DPLUTOSVG_BUILD'],
    link_args: ['-lm'],
    gnu_symbol_visibility: 'hidden',
    install: true
)

plutosvg_dep = declare_dependency(
    link_with: plutosvg_lib,
    dependencies: plutovg_dep,
    include_directories: include_directories('source'),
    compile_args: plutosvg_compile_args
)

meson.override_dependency('plutosvg', plutosvg_dep)
install_headers('source/plutosvg.h', subdir: 'plutosvg')

if not get_option('examples').disabled()
    subdir('examples')
endif

pkgmod = import('pkgconfig')
pkgmod.generate(plutosvg_lib,
    name: 'PlutoSVG',
    description: 'Tiny SVG rendering library',
    filebase: 'plutosvg',
    subdirs: 'plutosvg'
)
