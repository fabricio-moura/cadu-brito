#include <stdio.h>
#include <stdlib.h>
#include "primitivas.h"
#include "checagens.h"
#include "tipos.h"

int main()
{
    char primitiva[8];
    FILE *arquivo_input;
    imagem desenho;
    imagem *ptr_desenho;
    pixel **pixels;
    poligonal *poligono;

    ptr_desenho = &desenho;
    pixels = (pixel**) malloc(1*sizeof(pixel*));
    checar_mempixel(pixels, ptr_desenho, -1);

    pixels[0] = (pixel*) malloc(1*sizeof(pixel));
    checar_mempixel(pixels, ptr_desenho, 0);

    arquivo_input = fopen("input.txt", "r");
    checar_fopen(arquivo_input);

    while(fscanf(arquivo_input,"%s", primitiva) != EOF)
    {
        poligono = (poligonal*) malloc(3*sizeof(poligono));
        if(poligono == NULL)
        {
            printf("Erro! Memória Insuficiente\n");
            exit(1);
        }

        switch(checar_primitiva(primitiva))
        {
            case primitive_image:
                image(arquivo_input, ptr_desenho, pixels);
                break;
            case primitive_color: color(arquivo_input);
                printf("Color setada para %d %d %d\n", pincel.RGB.red, pincel.RGB.green,
                        pincel.RGB.blue);
                break;
            case primitive_clear: clear(arquivo_input, pixels, ptr_desenho);
                break;
            case primitive_rect: rect(arquivo_input);
                printf("Retangulo X Y Tam %d %d %d\n", retangulo.X, retangulo.Y,
                        retangulo.tamanho);
                break;
            case primitive_circle: circle(arquivo_input);
                printf("Circulo X Y Tam %d %d %d\n", circulo.X, circulo.Y, circulo.tamanho);
                break;
            case primitive_polygon:
                polygon(arquivo_input, poligono);
                printf("Poligono com %d pontos\n", poligono->pontos);
                for(int i = 0; i < poligono->pontos; i++)
                {
                    printf("Coordenadas X Y %d %d\n", poligono[i].X, poligono[i].Y);
                }
                free(poligono);
                break;
            case primitive_fill: fill(arquivo_input, pixels, ptr_desenho);
                printf("Pintando tudo de %d %d %d\n", pincel.RGB.red, pincel.RGB.green,
                        pincel.RGB.blue);
                break;
            case primitive_save: save(arquivo_input, pixels, ptr_desenho);
                break;
            case primitive_open:
                open(arquivo_input, pixels, ptr_desenho);

                /*pixels = (pixel**) realloc(pixels, (ptr_desenho->X)*sizeof(pixel*));
                checar_mempixel(pixels, ptr_desenho, -1);

                for(int i = 0; i < ptr_desenho->X; i++)
                {
                    pixels[i] = (pixel*) realloc(pixels[i], (ptr_desenho->Y)*sizeof(pixel));
                    checar_mempixel(pixels, ptr_desenho, i);
                }*/

                //exit(1);
                break;
            default: printf("Primitiva inválida\n");
                exit(1);
        }
    }

    for(int i = 0; i < desenho.X; i++)
    {
        free(pixels[i]);
    }
    free(pixels);
    fclose(arquivo_input);

    return 0;
}
