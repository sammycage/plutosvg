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

freetype_dep = dependency('freetype2',
    required: get_option('freetype'),
    version: '>=2.12',
    allow_fallback: false
)

plutosvg_compile_args = []
plutosvg_deps = [plutovg_dep]

cc = meson.get_compiler('c')
if freetype_dep.found() and cc.has_type('SVG_RendererHooks', dependencies: freetype_dep, prefix: '#include <freetype/otsvg.h>')
    plutosvg_deps += [freetype_dep]
    plutosvg_compile_args += ['-DPLUTOSVG_HAS_FREETYPE']
    add_project_arguments('-DPLUTOSVG_HAS_FREETYPE', language: ['c', 'cpp'])
else
    freetype_dep = disabler()
endif

if get_option('default_library') == 'static'
    plutosvg_compile_args += ['-DPLUTOSVG_BUILD_STATIC']
    add_project_arguments('-DPLUTOSVG_BUILD_STATIC', language: ['c', 'cpp'])
endif

plutosvg_lib = library('plutosvg', 'source/plutosvg.c',
    include_directories: include_directories('source'),
    dependencies: plutosvg_deps,
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
