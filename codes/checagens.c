#include <string.h>
#include "primitivas.h"

int verificar_primitiva(char *primitiva)
{
    if(strcmp(primitiva, "image") == 0)
    {
        return primitive_image;
    }
    else if(strcmp(primitiva, "color") == 0)
    {
        return primitive_color;
    }
    else if(strcmp(primitiva, "clear") == 0)
    {
        return primitive_clear;
    }
    else if(strcmp(primitiva, "rect") == 0)
    {
        return primitive_rect;
    }
    else if(strcmp(primitiva, "circle") == 0)
    {
        return primitive_circle;
    }
    else if(strcmp(primitiva, "polygon") == 0)
    {
        return primitive_polygon;
    }
    else if(strcmp(primitiva, "fill") == 0)
    {
        return primitive_fill;
    }
    else if(strcmp(primitiva, "save") == 0)
    {
        return primitive_save;
    }
    else if(strcmp(primitiva, "open") == 0)
    {
        return primitive_open;
    }

    return -1;
}
