#include <plutosvg.h>

#include <stdio.h>
#include <string.h>
#include <time.h>

static const char* basename(const char* path)
{
    const char* slash1 = strrchr(path, '/');
    const char* slash2 = strrchr(path, '\\');
    const char* last_slash = slash1 > slash2 ? slash1 : slash2;

    return last_slash ? last_slash + 1 : path;
}

static double elapsed_time(clock_t start, clock_t end)
{
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

#define TIMED(label, path, expression) do { \
    clock_t start = clock(); \
    expression; \
    clock_t end = clock(); \
    fprintf(stdout, "Finished %s '%s' in %.3f seconds\n", label, basename(path), elapsed_time(start, end)); \
} while(0)

int main(int argc, char* argv[])
{
    if(argc != 3 && argc != 4) {
        fprintf(stderr, "Usage: svg2png input output [id]\n");
        return -1;
    }

    const char* input = argv[1];
    const char* output = argv[2];
    const char* id = NULL;
    if(argc == 4) {
        id = argv[3];
    }

    plutosvg_document_t* document = NULL;
    plutovg_surface_t* surface = NULL;

    TIMED("loading", input, document = plutosvg_document_load_from_file(input, -1, -1));
    if(document == NULL) {
        fprintf(stderr, "Unable to load '%s'\n", input);
        goto cleanup;
    }

    TIMED("rendering", input, surface = plutosvg_document_render_to_surface(document, id, -1, -1, NULL, NULL, NULL));
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
