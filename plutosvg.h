#ifndef PLUTOSVG_H
#define PLUTOSVG_H

#include <plutovg.h>

#ifdef __cplusplus
extern "C" {
#endif

plutovg_surface_t* plutosvg_load_from_memory(const char* data, int size, const plutovg_font_t* font, int width, int height, double dpi);
plutovg_surface_t* plutosvg_load_from_file(const char* filename, const plutovg_font_t* font, int width, int height, double dpi);
int plutosvg_dimensions_from_memory(const char* data, int size, const plutovg_font_t* font, int* width, int* height, double dpi);
int plutosvg_dimensions_from_file(const char* filename, const plutovg_font_t* font, int* width, int* height, double dpi);

#ifdef __cplusplus
}
#endif

#endif // PLUTOSVG_H
