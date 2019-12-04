#ifndef CHECAGENS_H
#define CHECAGENS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tipos.h"
#include "primitivas.h"

void checar_mempixel (pixel **pixels, int counter);
void checar_mempoligono (poligonal *poligono);

void checar_fopen (FILE *arquivo);
void checar_nome_input (char *nome_input);

int checar_primitiva (char *primitiva);

void checar_formato (char *formato);
void checar_resolucao (imagem *ptr_desenho);
void checar_qualidade (int qualidade);

void checar_cor (int red, int green, int blue, char *comando);
int checar_proxpixel (int X, int Y, pixel ***ptr_pixels);

void checar_coordenadas (int X, int Y, imagem *ptr_desenho, char *comando);
void checar_medidas (int largura, int altura, int X, int Y, imagem *ptr_desenho);
void checar_pontos (poligonal **ptr_poligono);
void checar_raio (imagem *ptr_desenho);

#endif
