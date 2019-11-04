#ifndef CHECAGENS_H
#define CHECAGENS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tipos.h"
#include "primitivas.h"

int checar_primitiva(char *primitiva);
void checar_formato(char *formato);
void checar_resolucao(imagem *ptr_desenho);
void checar_mempixel(pixel **pixels, int counter);
void checar_fopen(FILE *arquivo);
void checar_nome_input(char *nome_input);
void checar_coordenadas(int X, int Y, imagem *ptr_desenho, char *comando);

#endif
