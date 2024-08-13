![emoji-collection.png](https://github.com/user-attachments/assets/a5de9b70-39a8-4a15-a012-22ab3cb93054)

# PlutoSVG

PlutoSVG is a compact and efficient SVG rendering library in C, designed for parsing and rendering SVG documents embedded in OpenType fonts. It is optimized for speed and minimal memory usage. It supports all elements specified in the [OpenType SVG specifications](https://learn.microsoft.com/en-us/typography/opentype/spec/svg) except `clipPath`. It also supports the [CSS `var()` function](https://www.w3.org/TR/css-variables/#using-variables) for referencing colors defined in the [CPAL table](https://learn.microsoft.com/en-us/typography/opentype/spec/cpal) as custom properties. Additionally, it supports the `style` attribute, the CSS `inherit` keyword, and the `<symbol>` element. This ensures compatibility with most SVG files exported from popular vector editors such as Illustrator, Sketch, Inkscape, Xara, and Corel Draw.

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

![camera.png](https://github.com/sammycage/plutosvg/blob/master/camera.png)

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
    if(FT_Init_FreeType(&library)) {
        // Handle error
        return -1;
    }

    // Set PlutoSVG hooks for the SVG module
    if(FT_Property_Set(library, "ot-svg", "svg-hooks", plutosvg_ft_svg_hooks())) {
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
