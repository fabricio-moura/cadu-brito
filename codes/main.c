#include <stdio.h>
#include <stdlib.h>
#include "primitivas.h"
#include "verificar_primitiva.h"

int main()
{
    char primitiva[8];
    FILE *arquivo_input;
    imagem desenho;
    imagem *ptr_desenho = &desenho;
    pixel **pixels;
    poligonal *poligono;

    pixels = (pixel**) malloc(1000*sizeof(pixel*));
    if(pixels == NULL)
    {
        printf ("Erro: Memoria Insuficiente");
        exit(1);
    }

    for(int i = 0; i < 10; i++)
    {
        pixels[i] = (pixel*) malloc(1000*sizeof(pixel));
        if(pixels[i] == NULL)
        {
            printf("Erro: Memoria Insuficiente");
            exit(1);
        }
    }

    poligono = (poligonal*) malloc(3*sizeof(poligono));
    if(poligono == NULL)
    {
        printf("Erro: Memoria Insuficiente");
        exit(1);
    }

    arquivo_input = fopen("input.txt", "r");

    while(fscanf(arquivo_input,"%s", primitiva) != EOF)
    {
        switch(verificar_primitiva(primitiva))
        {
            case primitive_image:
                image(arquivo_input, ptr_desenho);
                pixels = (pixel**) realloc(pixels, (ptr_desenho->X)*sizeof(pixel*));
                if(pixels == NULL)
                {
                    printf ("Erro: Memoria Insuficiente");
                    exit(1);
                }
                for(int i = 0; i < ptr_desenho->X; i++)
                {
                    pixels[i] = (pixel*) realloc(pixels[i], (ptr_desenho->Y)*sizeof(pixel));
                    if(pixels[i] == NULL)
                    {
                        printf("Erro: Memoria Insuficiente");
                        exit(1);
                    }
                }
                break;
            case primitive_color: color(arquivo_input);
                break;
            case primitive_clear: clear(arquivo_input, pixels, ptr_desenho);
                break;
            case primitive_rect: rect(arquivo_input);
                break;
            case primitive_circle: circle(arquivo_input);
                break;
            case primitive_polygon: polygon(arquivo_input, poligono);
                break;
            case primitive_fill: fill(arquivo_input, pixels, ptr_desenho);
                break;
            case primitive_save: save(arquivo_input, pixels, ptr_desenho);
                break;
            case primitive_open:
                open(arquivo_input, pixels, ptr_desenho);
                pixels = (pixel**) realloc(pixels, (ptr_desenho->X)*sizeof(pixel*));
                if(pixels == NULL)
                {
                    printf ("Erro: Memoria Insuficiente");
                    exit(1);
                }

                for(int i = 0; i < ptr_desenho->X; i++)
                {
                    pixels[i] = (pixel*) realloc(pixels[i], (ptr_desenho->Y)*sizeof(pixel));
                    if(pixels[i] == NULL)
                    {
                        printf("Erro: Memoria Insuficiente");
                        exit(1);
                    }
                }
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
    free(poligono);
    fclose(arquivo_input);

    return 0;
}
