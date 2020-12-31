# PlutoSVG
plutosvg is a tiny SVG rendering library in C

## Features
- Basic Shapes : rect, circle, ellipse, line, polyline, polygon, path
- Paint Servers : solidColor(TODO), linearGradient, radialGradient, pattern(TODO)
- Document Structures: defs, svg, g, use, symbol
- Coordinate Systems, Transformations and Units
- Texts (TODO) : text, tspan

## Example
```c
#include <plutosvg.h>

int main(void)
{
    plutovg_surface_t* surface = plutosvg_load_from_file("tiger.svg", NULL, 0, 0, 96.0);
    plutovg_surface_write_to_png(surface, "tiger.png");
    plutovg_surface_destroy(surface);

    return 0;
}

```
