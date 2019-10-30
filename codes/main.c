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
    poligono *polygon;

    pixels = (pixel**) calloc(10, sizeof(pixel*));
    if(pixels == NULL)
    {
        printf ("Erro: Memoria Insuficiente");
        exit(1);
    }

    for(int i = 0; i < 10; i++)
    {
        pixels[i] = (pixel*) calloc(10, sizeof(pixel));
        if(pixels[i] == NULL)
        {
            printf("Erro: Memoria Insuficiente");
            exit(1);
        }
    }

    polygon = (poligono*) calloc(3, sizeof(polygon));
    if(polygon == NULL)
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
            switch(verificar_primitiva(primitiva, arquivo_input, polygon))
            {
                case primitive_image: image(arquivo_input, pixels, ptr_desenho);
                    printf("%d\n", desenho.X);
                    break;
                case primitive_color: break;
                case primitive_clear: break;
                case primitive_rect: break;
                case primitive_circle: break;
                case primitive_polygon: break;
                case primitive_fill: break;
                case primitive_save: save(arquivo_input, pixels, ptr_desenho);
                    break;
                case primitive_open: open(arquivo_input, pixels, ptr_desenho);
                    break;
                default: printf("Primitiva inválida\n");
                    exit(1);
            }

            free(polygon);
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
