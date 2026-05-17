#include <plutosvg.h>

#include <stdio.h>
#include <time.h>

#define TIMED(label, filename, expression) do { \
    clock_t start = clock(); \
    expression; \
    clock_t end = clock(); \
    fprintf(stdout, "Finished %s '%s' in %.3f seconds\n", label, filename, ((double)(end - start)) / CLOCKS_PER_SEC); \
} while(0)

int main(void)
{
    const char* input = "camera.svg";
    const char* output = "camera.png";

    plutosvg_document_t* document = NULL;
    plutovg_surface_t* surface = NULL;

    TIMED("loading", input, document = plutosvg_document_load_from_file(input, -1, -1));
    if(document == NULL) {
        fprintf(stderr, "Unable to load '%s'\n", input);
        goto cleanup;
    }

    TIMED("rendering", input, surface = plutosvg_document_render_to_surface(document, NULL, -1, -1, NULL, NULL, NULL));
    if(surface == NULL) {
        fprintf(stderr, "Unable to render '%s'\n", input);
        goto cleanup;
    }

    TIMED("writing", output, if(!plutovg_surface_write_to_png(surface, output)) {
        fprintf(stderr, "Unable to write '%s'\n", output);
        goto cleanup;
    });

cleanup:
    plutovg_surface_destroy(surface);
    plutosvg_document_destroy(document);
    return 0;
}
