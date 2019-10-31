#include <stdio.h>
#include <stdlib.h>
#include "primitivas.h"
#include "leitura.h"

int main()
{
    char primitiva[8];
    FILE *arquivo_input;
    imagem desenho;
    imagem *ptr_desenho = &desenho;
    pixel **pixels;
    poligonal *poligono;

    pixels = (pixel**) malloc(10*sizeof(pixel*));
    if(pixels == NULL)
    {
        printf ("Erro: Memoria Insuficiente");
        exit(1);
    }

    for(int i = 0; i < 10; i++)
    {
        pixels[i] = (pixel*) malloc(10*sizeof(pixel));
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
    while(1)
    {
        if(fscanf(arquivo_input,"%s", primitiva) == EOF)
        {
            break;
        }
        else
        {
            switch(verificar_primitiva(primitiva))
            {
                case primitive_image: image(arquivo_input, pixels, ptr_desenho);
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
                case primitive_open: open(arquivo_input, pixels, ptr_desenho);
                    break;
                default: printf("Primitiva inválida\n");
                    exit(1);
            }

            free(poligono);
        }


    }

    /*color(23,47,103,pincel);
    fill(X, Y, desenho, pincel);
    printf("batata\n");
    salvar_imagem(X, Y, desenho);*/

    for(int i = 0; i < desenho.X; i++)
    {
        free(pixels[i]);
    }
    free(pixels);
    fclose(arquivo_input);

    return 0;
}
