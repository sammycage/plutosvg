executable('svg2png', 'svg2png.c', dependencies: plutosvg_dep)
if cc.has_argument('-DPLUTOSVG_HAS_FREETYPE')
    executable('emoji2png', 'emoji2png.c', dependencies: [plutosvg_dep, freetype_dep])
endif
