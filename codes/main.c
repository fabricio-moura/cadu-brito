#include <stdio.h>
#include <stdlib.h>
#include "primitivas.h"
#include "checagens.h"
#include "tipos.h"

int main()
{
    pixel **pixels;
    pixel ***ptr_pixels;
    char primitiva[8];
    char nome_input[30];
    char *ptr_input = nome_input;
    FILE *arquivo_input;
    imagem desenho;
    imagem *ptr_desenho = &desenho;
    poligonal *poligono;

    pixels = (pixel**) malloc(1*sizeof(pixel*));
    checar_mempixel(pixels, ptr_desenho, -1);
    pixels[0] = (pixel*) malloc(1*sizeof(pixel));
    checar_mempixel(pixels, ptr_desenho, 0);

    ptr_pixels = &pixels;

    checar_nome_input(ptr_input);
    arquivo_input = fopen(nome_input, "r");
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
                image(arquivo_input, ptr_desenho, ptr_pixels);
                //octante(ptr_desenho, ptr_pixels);

                break;
            case primitive_color: color(arquivo_input);
                printf("Color setada para %d %d %d\n", pincel.RGB.red, pincel.RGB.green,
                        pincel.RGB.blue);
                break;
            case primitive_clear: clear(arquivo_input, ptr_pixels, ptr_desenho);
                break;
            case primitive_rect: rect(arquivo_input, ptr_pixels);
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
            case primitive_fill: fill(arquivo_input, ptr_pixels, ptr_desenho);
                printf("Pintando tudo de %d %d %d\n", pincel.RGB.red, pincel.RGB.green,
                        pincel.RGB.blue);
                break;
            case primitive_save:
                save(arquivo_input, ptr_pixels, ptr_desenho);
                break;
            case primitive_open:
                open(arquivo_input, ptr_pixels, ptr_desenho);
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
