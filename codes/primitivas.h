#ifndef PRIMITIVAS_H
#define PRIMITIVAS_H

#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "checagens.h"

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

/*int PA(int n);

void octante(imagem *ptr_desenho, pixel ***ptr_pixel);*/
void image(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels);
void color(FILE *arquivo);
void clear(FILE *arquivo, pixel ***ptr_pixels, imagem *ptr_desenho);
void rect(FILE *arquivo, pixel ***ptr_pixels);
void circle(FILE *arquivo);
void polygon(FILE *arquivo, poligonal *poligono);
void fill(FILE *arquivo, pixel ***ptr_pixels, imagem *ptr_desenho);
void save(FILE *arquivo_input, pixel ***ptr_pixels, imagem *ptr_desenho);
void open(FILE *arquivo_input, pixel ***ptr_pixels, imagem *ptr_desenho);

#endif
