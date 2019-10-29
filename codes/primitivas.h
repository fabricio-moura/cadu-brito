#ifndef PRIMITIVAS_H
#define PRIMITIVAS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int red;
    int green;
    int blue;
} cor;

struct imagem
{
    int X;
    int Y;
} imagem;

struct color
{
    cor RGB;
} pincel;

struct rect
{
    int X;
    int Y;
    int tamanho;
} retangulo;

struct circle
{
    int X;
    int Y;
    int tamanho;
} circulo;

typedef struct
{
    int X;
    int Y;
} poligono;

void color(int red, int green, int blue, cor pincel);
void fill(int X, int Y, cor desenho[X][Y], cor pincel);
FILE open();
void salvar_imagem(int X, int Y, cor desenho[X][Y]);

#endif
