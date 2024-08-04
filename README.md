# PlutoSVG
plutosvg is a tiny SVG rendering library in C. It can be used for parsing and rendering SVG documents embedded in OpenType fonts.

## Features
- Basic Shapes : rect, circle, ellipse, line, polyline, polygon, path
- Paint Servers : solidColor, linearGradient, radialGradient
- Document Structures: defs, svg, g, use, symbol
- Images

## Basic Usage
```c
#include <plutosvg.h>

#include <stdio.h>

int main(void)
{
    plutosvg_document_t* document = plutosvg_document_load_from_file("camera.svg", -1, -1);
    if(document == NULL) {
        printf("Unable to load: camera.svg\n");
        return -1;
    }

    plutovg_surface_t* surface = plutosvg_document_render_to_surface(document, NULL, -1, -1, NULL, NULL, NULL);
    plutovg_surface_write_to_png(surface, "camera.png");
    plutosvg_document_destroy(document);
    plutovg_surface_destroy(surface);
    return 0;
}
```

![camera.png](camera.png)

## Integrating with FreeType

```c
#include <plutosvg.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MODULE_H

int main(void)
{
    FT_Library library;

    // Initialize the FreeType library
    if (FT_Init_FreeType(&library)) {
        // Handle error
        return -1;
    }

    // Set PlutoSVG hooks for the SVG module
    if (FT_Property_Set(library, "ot-svg", "svg-hooks", plutosvg_ft_svg_hooks())) {
        // Handle error
        return -1;
    }

    // Your code here

    // Clean up
    FT_Done_FreeType(library);

    return 0;
}
```

## Installation

Ensure you have [Meson](http://mesonbuild.com) and [Ninja](http://ninja-build.org) installed.

```bash
git clone https://github.com/sammycage/plutosvg.git
cd plutovg
meson setup build
ninja -C build
ninja -C build install
```
