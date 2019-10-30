#include "leitura.h"

int verificar_primitiva(char *primitiva, FILE *arquivo, poligono *polygon)
{
    if(strcmp(primitiva, "image") == 0)
    {
        // Talvez não precise de struct e possa botar direto na função.
        return primitive_image;
    }
    else if(strcmp(primitiva, "color") == 0)
    {
        fscanf(arquivo, " %d %d %d\n", &pincel.RGB.red, &pincel.RGB.green,
                &pincel.RGB.blue);
        return primitive_color;
    }
    else if(strcmp(primitiva, "clear") == 0)
    {
        fscanf(arquivo, " %d %d %d\n", &pincel.RGB.red, &pincel.RGB.green,
                &pincel.RGB.blue);
        return primitive_clear;
    }
    else if(strcmp(primitiva, "rect") == 0)
    {
        fscanf(arquivo, " %d %d %d\n", &retangulo.X, &retangulo.Y,
                &retangulo.tamanho);
        return primitive_rect;
    }
    else if(strcmp(primitiva, "circle") == 0)
    {
        fscanf(arquivo, " %d %d %d\n", &circulo.X, &circulo.Y, &circulo.tamanho);
        return primitive_circle;
    }
    else if(strcmp(primitiva, "polygon") == 0)
    {
        int N;
        fscanf(arquivo, " %d", &N);
        polygon = realloc(polygon, N * sizeof(polygon));
        for(int i = 0; i < N; i++)
        {
            fscanf(arquivo, " %d %d", &polygon[i].X, &polygon[i].Y);
        }
        return primitive_polygon;
    }
    else if(strcmp(primitiva, "fill") == 0)
    {
        int X, Y;
        fscanf(arquivo, " %d %d\n", &X, &Y);
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

    return 0;
}
