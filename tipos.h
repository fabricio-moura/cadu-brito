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
    cor RGB;
} pixel;

typedef struct
{
    unsigned short X;
    unsigned short Y;
} imagem;

typedef struct
{
    int X;
    int Y;
    int pontos;
} poligonal;

struct paint
{
    cor RGB;
} pincel, pincel_fill;

struct line
{
    int dx;
    int dy;
    int decisao;
} linha;

struct circle
{
    int X;
    int Y;
    int tamanho;
} circulo;

#endif
