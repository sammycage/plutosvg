#include <plutosvg.h>

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    plutovg_surface_t* surface = plutosvg_load_from_file("camera.svg", NULL, 0, 0, 96.0);
    if(surface == NULL)
    {
        printf("Load failed\n");
        return -1;
    }

    plutovg_surface_write_to_png(surface, "camera.png");
    plutovg_surface_destroy(surface);
    return 0;
}
