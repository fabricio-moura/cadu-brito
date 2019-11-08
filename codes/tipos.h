#ifndef TIPOS_H
#define TIPOS_H

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
} pincel, pincel_fill;

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

struct line
{
    int dx;
    int dy;
    int decisao;
} linha;

typedef struct
{
    int X;
    int Y;
    int pontos;
} poligonal;

#endif
