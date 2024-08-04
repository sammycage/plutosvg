/*
 * Copyright (c) 2020-2024 Samuel Ugochukwu <sammycageagle@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#ifndef PLUTOSVG_H
#define PLUTOSVG_H

#include <plutovg.h>

#if !defined(PLUTOSVG_BUILD_STATIC) && (defined(_WIN32) || defined(__CYGWIN__))
#define PLUTOSVG_EXPORT __declspec(dllexport)
#define PLUTOSVG_IMPORT __declspec(dllimport)
#elif defined(__GNUC__) && (__GNUC__ >= 4)
#define PLUTOSVG_EXPORT __attribute__((__visibility__("default")))
#define PLUTOSVG_IMPORT
#else
#define PLUTOSVG_EXPORT
#define PLUTOSVG_IMPORT
#endif

#ifdef PLUTOSVG_BUILD
#define PLUTOSVG_API PLUTOSVG_EXPORT
#else
#define PLUTOSVG_API PLUTOSVG_IMPORT
#endif

#define PLUTOSVG_VERSION_MAJOR 0
#define PLUTOSVG_VERSION_MINOR 0
#define PLUTOSVG_VERSION_MICRO 1

#define PLUTOSVG_VERSION PLUTOVG_VERSION_ENCODE(PLUTOSVG_VERSION_MAJOR, PLUTOSVG_VERSION_MINOR, PLUTOSVG_VERSION_MICRO)
#define PLUTOSVG_VERSION_STRING PLUTOVG_VERSION_STRINGIZE(PLUTOSVG_VERSION_MAJOR, PLUTOSVG_VERSION_MINOR, PLUTOSVG_VERSION_MICRO)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief plutosvg_version
 * @return
 */
PLUTOSVG_API int plutosvg_version(void);

/**
 * @brief plutosvg_version_string
 * @return
 */
PLUTOSVG_API const char* plutosvg_version_string(void);

/**
 * @brief plutosvg_document_t
 */
typedef struct plutosvg_document plutosvg_document_t;

/**
 * @brief plutosvg_palette_func_t
 * @param closure
 * @param name
 * @param length
 * @param color
 * @return
 */
typedef bool(*plutosvg_palette_func_t)(void* closure, const char* name, int length, plutovg_color_t* color);

/**
 * @brief plutosvg_document_load_from_data
 * @param data
 * @param length
 * @param width
 * @param height
 * @param destroy_func
 * @param closure
 * @return
 */
PLUTOSVG_API plutosvg_document_t* plutosvg_document_load_from_data(const char* data, int length, float width, float height,
    plutovg_destroy_func_t destroy_func, void* closure);

/**
 * @brief plutosvg_document_load_from_file
 * @param filename
 * @param width
 * @param height
 * @return
 */
PLUTOSVG_API plutosvg_document_t* plutosvg_document_load_from_file(const char* filename, float width, float height);

/**
 * @brief plutosvg_document_render
 * @param document
 * @param id
 * @param canvas
 * @param current_color
 * @param palette_func
 * @param closure
 * @return
 */
PLUTOSVG_API bool plutosvg_document_render(const plutosvg_document_t* document, const char* id, plutovg_canvas_t* canvas,
    const plutovg_color_t* current_color, plutosvg_palette_func_t palette_func, void* closure);

/**
 * @brief plutosvg_document_render_to_surface
 * @param document
 * @param id
 * @param width
 * @param height
 * @param current_color
 * @param palette_func
 * @param closure
 * @return
 */
PLUTOSVG_API plutovg_surface_t* plutosvg_document_render_to_surface(const plutosvg_document_t* document, const char* id, int width, int height,
    const plutovg_color_t* current_color, plutosvg_palette_func_t palette_func, void* closure);

/**
 * @brief plutosvg_document_get_width
 * @param document
 * @return
 */
PLUTOSVG_API float plutosvg_document_get_width(const plutosvg_document_t* document);

/**
 * @brief plutosvg_document_get_height
 * @param document
 * @return
 */
PLUTOSVG_API float plutosvg_document_get_height(const plutosvg_document_t* document);

/**
 * @brief plutosvg_document_extents
 * @param document
 * @param id
 * @param extents
 * @return
 */
PLUTOSVG_API bool plutosvg_document_extents(const plutosvg_document_t* document, const char* id, plutovg_rect_t* extents);

/**
 * @brief plutosvg_document_destroy
 * @param document
 */
PLUTOSVG_API void plutosvg_document_destroy(plutosvg_document_t* document);

/**
 * @brief plutosvg_ft_svg_hooks
 * @return
 */
PLUTOSVG_API const void* plutosvg_ft_svg_hooks(void);

#ifdef __cplusplus
}
#endif

#endif // PLUTOSVG_H
