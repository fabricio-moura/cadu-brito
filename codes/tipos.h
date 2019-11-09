#ifndef TIPOS_H
#define TIPOS_H

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} cor;

typedef struct
{
    unsigned short X;
    unsigned short Y;
} imagem;

typedef struct
{
    unsigned short X;
    unsigned short Y;
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
    int lado_menor;
    int lado_maior;
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
