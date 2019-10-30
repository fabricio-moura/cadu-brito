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

typedef struct
{
    int X;
    int Y;
} imagem;

typedef struct
{
    int X;
    int Y;
    cor RGB;
} pixel;

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

enum primitivas
{
    primitive_image,
    primitive_color,
    primitive_clear,
    primitive_rect,
    primitive_circle,
    primitive_polygon,
    primitive_fill,
    primitive_save,
    primitive_open
};

void image(FILE *arquivo, pixel **pixels, imagem desenho);
void clear(FILE *arquivo, pixel **pixels, imagem *ptr_desenho);
void color(int red, int green, int blue, cor pincel);
//void fill(int X, int Y, cor desenho[X][Y], cor pincel);
void open(FILE *arquivo_input, pixel **pixels, imagem *ptr_desenho);
void save(FILE *arquivo_input, pixel **pixels, imagem *ptr_desenho);

#endif
