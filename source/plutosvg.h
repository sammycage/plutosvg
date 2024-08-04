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
 * @brief Callback function type for resolving CSS color variables in SVG documents.
 * @param closure A pointer to user-defined data passed to the callback function.
 * @param name A pointer to the string representing the name of the color variable.
 * @param length The length of the color variable name string.
 * @param color A pointer to a `plutovg_color_t` structure where the resolved color will be stored.
 * @return `true` if the color variable was successfully resolved and stored in the `color` structure; `false` otherwise.
 */
typedef bool(*plutosvg_palette_func_t)(void* closure, const char* name, int length, plutovg_color_t* color);

/**
 * @brief Loads an SVG document from a data buffer.
 * @param data A pointer to a buffer containing the SVG data.
 * @param length The length of the data buffer.
 * @param width The container width for the SVG document. This is used to resolve the initial viewport when the root SVG width is specified in relative units.
 * @param height The container height for the SVG document. This is used to resolve the initial viewport when the root SVG height is specified in relative units.
 * @param destroy_func A function pointer to a custom destroy function that will be called when the document is destroyed.
 * @param closure A pointer to user-defined data that will be passed to the destroy function.
 * @return A pointer to a `plutosvg_document_t` structure representing the loaded SVG document, or NULL if the loading fails.
 */
PLUTOSVG_API plutosvg_document_t* plutosvg_document_load_from_data(const char* data, int length, float width, float height,
    plutovg_destroy_func_t destroy_func, void* closure);

/**
 * @brief Loads an SVG document from a file.
 * @param A pointer to a null-terminated string representing the path to the file containing the SVG data.
 * @param width The container width for the SVG document. This is used to resolve the initial viewport when the root SVG width is specified in relative units.
 * @param height The container height for the SVG document. This is used to resolve the initial viewport when the root SVG height is specified in relative units.
 * @return A pointer to a `plutosvg_document_t` structure representing the loaded SVG document, or NULL if the loading fails.
 */
PLUTOSVG_API plutosvg_document_t* plutosvg_document_load_from_file(const char* filename, float width, float height);

/**
 * @brief Renders an SVG document or a specific element onto a canvas.
 *
 * This function renders either a specific element identified by `id` or the entire SVG document if `id` is `NULL`.
 * The rendering process takes into account the optional color and palette function for variable resolution.
 *
 * @param document A pointer to a `plutosvg_document_t` structure representing the SVG document..
 * @param id A pointer to a null-terminated string specifying the ID of the SVG element to render. If `NULL`, the entire SVG document is rendered.
 * @param canvas A pointer to the `plutovg_canvas_t` structure representing the canvas onto which the SVG element or document will be rendered.
 * @param current_color A pointer to a `plutovg_color_t` structure used to resolve CSS current color values.
 * @param palette_func A callback function of type `plutosvg_palette_func_t` used to resolve CSS color variables (custom properties) defined in the SVG.
 * @param closure A pointer to user-defined data that will be passed to the `palette_func` callback.
 * @return `true` if the rendering operation was successful; `false` otherwise.
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
 * @brief Returns the intrinsic width of the SVG document.
 * @param document A pointer to a `plutosvg_document_t` structure representing the SVG document..
 * @return The intrinsic width of the SVG document.
 */
PLUTOSVG_API float plutosvg_document_get_width(const plutosvg_document_t* document);

/**
 * @brief Returns the intrinsic height of the SVG document.
 * @param document A pointer to a `plutosvg_document_t` structure representing the SVG document..
 * @return The intrinsic height of the SVG document.
 */
PLUTOSVG_API float plutosvg_document_get_height(const plutosvg_document_t* document);

/**
 * @brief Retrieves the extents of a specific element within the SVG document or the whole document if the ID is NULL.
 *
 * This function calculates and retrieves the bounding box (extents) of an element identified by its ID within the given SVG document.
 * If the ID is NULL, the extents of the entire SVG document are retrieved. The extents are returned as a `plutovg_rect_t` structure.
 *
 * @param document A pointer to a `plutosvg_document_t` structure representing the SVG document..
 * @param id A string representing the ID of the element whose extents are to be retrieved, or NULL to retrieve the extents of the entire document.
 * @param extents A pointer to a `plutovg_rect_t` structure where the extents will be stored.
 * @return `true` if the extents were successfully retrieved, `false` otherwise.
 */
PLUTOSVG_API bool plutosvg_document_extents(const plutosvg_document_t* document, const char* id, plutovg_rect_t* extents);

/**
 * @brief Destroys an SVG document and frees associated resources.
 * @param document A pointer to a `plutosvg_document_t` structure representing the SVG document to be destroyed. If the pointer is NULL, the function does nothing.
 */
PLUTOSVG_API void plutosvg_document_destroy(plutosvg_document_t* document);

/**
 * @brief Returns a pointer to a structure containing PlutoSVG hooks for integration with FreeType's SVG module.
 *
 * These hooks enable FreeType to use PlutoSVG for rendering SVG graphics embedded in fonts.
 *
 * @return a pointer to a structure containing PlutoSVG hooks for integration with FreeType's SVG module.
 */
PLUTOSVG_API const void* plutosvg_ft_svg_hooks(void);

#ifdef __cplusplus
}
#endif

#endif // PLUTOSVG_H
