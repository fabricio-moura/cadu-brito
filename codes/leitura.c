#include "leitura.h"

void verificar_primitiva(char *primitiva, FILE *arquivo, poligono *polygon)
{
    if(strcmp(primitiva, "image") == 0)
    {
        // Talvez não precise de struct e possa botar direto na função.
        fscanf(arquivo, " %d %d\n", &imagem.X, &imagem.Y);
        //image();
    }
    else if(strcmp(primitiva, "color") == 0)
    {
        fscanf(arquivo, " %d %d %d\n", &pincel.RGB.red, &pincel.RGB.green,
                &pincel.RGB.blue);
        //color();
    }
    else if(strcmp(primitiva, "clear") == 0)
    {
        fscanf(arquivo, " %d %d %d\n", &pincel.RGB.red, &pincel.RGB.green,
                &pincel.RGB.blue);
        //clear();
    }
    else if(strcmp(primitiva, "rect") == 0)
    {
        fscanf(arquivo, " %d %d %d\n", &retangulo.X, &retangulo.Y,
                &retangulo.tamanho);
        //rect();
    }
    else if(strcmp(primitiva, "circle") == 0)
    {
        fscanf(arquivo, " %d %d %d\n", &circulo.X, &circulo.Y, &circulo.tamanho);
        //circle();
    }
    else if(strcmp(primitiva, "polygon") == 0)
    {
        int N;
        fscanf(arquivo, " %d", &N);
        polygon = realloc(polygon, N * sizeof(poligono));
        for(int i = 0; i < N; i++)
        {
            fscanf(arquivo, " %d %d", &polygon[i].X, &polygon[i].Y);
        }
    }
    else if(strcmp(primitiva, "fill") == 0)
    {
        int X, Y;
        fscanf(arquivo, " %d %d\n", &X, &Y);
        //fill(X, Y);
    }
    else if(strcmp(primitiva, "save") == 0)
    {
        char save_name[30];
        fscanf(arquivo, " %s\n", save_name);
        //save(save_name);
    }
    else if(strcmp(primitiva, "open") == 0)
    {
        // Não sei o que fazer aqui ainda...
    }
}
