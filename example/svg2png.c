#include <plutosvg.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int help()
{
    puts("Usage: \n   svg2png [filename] [resolution]\n\nExamples: \n    $ svg2png input.svg\n    $ svg2png input.svg 512x512\n");
    return 1;
}

static const char* basename (const char* filename)
{
    const char* p = strrchr(filename, '/');
    if(p == NULL)
        p = strrchr(filename, '\\');
    return p ? p + 1 : filename;
}

int main(int argc, char** argv)
{
    char* path = NULL;
    int width = 0;
    int height = 0;

    if(argc > 1) path = argv[1];
    if(argc > 2)
    {
        char* x = strstr(argv[2], "x");
        if(x)
        {
            char buf[20];
            snprintf(buf, (size_t)(x - argv[2] + 1), "%s", argv[2]);
            width = atoi(buf);
            snprintf(buf, sizeof(buf), "%s", x + 1);
            height = atoi(buf);
        }
    }

    if(!path) return help();

    plutovg_surface_t* surface = plutosvg_load_from_file(path, NULL, width, height, 96.0);

    if(!surface) return help();

    char filename[256];

    strcpy(filename, basename(path));
    strcat(filename, ".png");
    printf("Generated PNG file : %s\n", filename);

    plutovg_surface_write_to_png(surface, filename);
    plutovg_surface_destroy(surface);

    return 0;
}
