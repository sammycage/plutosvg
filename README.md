# PlutoSVG
plutosvg is a tiny SVG rendering library in C

## Features
- Basic Shapes : rect, circle, ellipse, line, polyline, polygon, path
- Paint Servers : solidColor, linearGradient, radialGradient
- Document Structures: defs, svg, g, use, symbol
- Image

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

## Installation

Ensure you have [Meson](http://mesonbuild.com) and [Ninja](http://ninja-build.org) installed.

```bash
git clone https://github.com/sammycage/plutosvg.git
cd plutovg
meson setup build
ninja -C build
ninja -C build install
```
