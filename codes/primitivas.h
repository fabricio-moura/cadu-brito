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

void image(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels);
void open(FILE *arquivo_input,imagem *ptr_desenho,  pixel ***ptr_pixels);
void save(FILE *arquivo_input, imagem *ptr_desenho, pixel ***ptr_pixels);

void color(FILE *arquivo);
void paint_pixels(int eixo_x, int eixo_y, pixel ***ptr_pixels);
void color_picker(int X, int Y, pixel ***ptr_pixels);

void clear(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels);
void fill(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels);
void fill_spread_right(unsigned short X, unsigned short Y, unsigned short imagem_X, unsigned short imagem_Y, pixel ***ptr_pixels);
void fill_spread_left(unsigned short X, unsigned short Y, unsigned short imagem_X, unsigned short imagem_Y, pixel ***ptr_pixels);

void line(int x_final, int y_final, int x_inicial, int y_inicial, pixel ***ptr_pixels);
void line_straight(int x_final, int y_final, int x_inicial, int y_inicial, pixel ***ptr_pixels);
void line_dx(int x_final, int y_final, int x_inicial, int y_inicial, pixel ***ptr_pixels);
void line_dy(int x_final, int y_final, int x_inicial, int y_inicial, pixel ***ptr_pixels);

void rect(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels);
void polygon(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels, poligonal **ptr_poligono);
void circle(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels);
void circle_line(int x, int y, int decisao, pixel ***ptr_pixels);

#endif
