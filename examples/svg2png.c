#include <plutosvg.h>

#include <stdio.h>

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

    fprintf(stdout, "Loading: %s\n", input);
    document = plutosvg_document_load_from_file(input, -1, -1);
    if(document == NULL) {
        fprintf(stderr, "Unable to load: %s\n", input);
        goto cleanup;
    }

    fprintf(stdout, "Rendering: %s\n", input);
    surface = plutosvg_document_render_to_surface(document, id, -1, -1, NULL, NULL, NULL);
    if(surface == NULL) {
        fprintf(stderr, "Unable to render: %s\n", input);
        goto cleanup;
    }

    fprintf(stdout, "Writing: %s\n", output);
    if(!plutovg_surface_write_to_png(surface, output)) {
        fprintf(stderr, "Unable to write: %s\n", output);
        goto cleanup;
    }

cleanup:
    plutovg_surface_destroy(surface);
    plutosvg_document_destroy(document);
    return 0;
}
