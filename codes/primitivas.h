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

struct paint
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
} poligonal;

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

void image(FILE *arquivo, imagem *ptr_desenho);
void color(FILE *arquivo);
void clear(FILE *arquivo, pixel **pixels, imagem *ptr_desenho);
void rect(FILE *arquivo);
void circle(FILE *arquivo);
void polygon(FILE *arquivo, poligonal *poligono);
void fill(FILE *arquivo, pixel **pixels, imagem *ptr_desenho);
void open(FILE *arquivo_input, pixel **pixels, imagem *ptr_desenho);
void save(FILE *arquivo_input, pixel **pixels, imagem *ptr_desenho);

#endif
