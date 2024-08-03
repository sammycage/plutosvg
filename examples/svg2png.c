#include <plutosvg.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc != 3 && argc != 4) {
        printf("Usage : svg2png input output [id]\n");
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

    document = plutosvg_document_load_from_file(input, -1, -1);
    if(document == NULL) {
        printf("Unable to load: %s\n", input);
        goto cleanup;
    }

    surface = plutosvg_document_render_to_surface(document, id, -1, -1, NULL, NULL, NULL);
    if(surface == NULL) {
        printf("Unable to render (%s)\n", id);
        goto cleanup;
    }

    plutovg_surface_write_to_png(surface, output);
    printf("Generated PNG: %s\n", output);
cleanup:
    plutosvg_document_destroy(document);
    plutovg_surface_destroy(surface);
    return 0;
}
