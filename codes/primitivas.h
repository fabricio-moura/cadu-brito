#ifndef PRIMITIVAS_H
#define PRIMITIVAS_H

#include <stdio.h>

typedef struct
{
    int red;
    int green;
    int blue;
} imagem;

void pintar_imagem(int X, int Y, imagem desenho[X][Y]);
void salvar_imagem(int X, int Y, imagem desenho[X][Y]);

#endif
