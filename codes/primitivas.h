#ifndef PRIMITIVAS_H
#define PRIMITIVAS_H

typedef struct
{
    int red;
    int green;
    int blue;
} imagem;

void pintar_imagem(imagem *desenho,int X, int Y);
void salvar_imagem(imagem *desenho,int X, int Y);

#endif
