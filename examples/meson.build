executable('svg2png', 'svg2png.c', dependencies: plutosvg_dep)
if freetype_dep.found()
    executable('emoji2png', 'emoji2png.c', dependencies: [plutosvg_dep, freetype_dep])
endif
