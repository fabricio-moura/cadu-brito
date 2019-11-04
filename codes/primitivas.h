#ifndef PRIMITIVAS_H
#define PRIMITIVAS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
//void line_circle(int x_centro, int y_centro, int tamanho, pixel ***ptr_pixels);
void circle_line(int x, int y, int decisao, pixel ***ptr_pixels);
void fill_spread(int X, int Y, pixel ***ptr_pixels, imagem *ptr_desenho);
void paint_pixels(int eixo_x, int eixo_y, pixel ***ptr_pixels);
void line(int x_final, int y_final, int x_inicial, int y_inicial, pixel ***ptr_pixels);
void image(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels);
void color(FILE *arquivo);
void clear(FILE *arquivo, pixel ***ptr_pixels, imagem *ptr_desenho);
void rect(FILE *arquivo, pixel ***ptr_pixels);
void circle(FILE *arquivo, pixel ***ptr_pixels);
void polygon(FILE *arquivo, poligonal *poligono);
void fill(FILE *arquivo, pixel ***ptr_pixels, imagem *ptr_desenho);
void save(FILE *arquivo_input, pixel ***ptr_pixels, imagem *ptr_desenho);
void open(FILE *arquivo_input, pixel ***ptr_pixels, imagem *ptr_desenho);

#endif
