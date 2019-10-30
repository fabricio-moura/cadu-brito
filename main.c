#include <stdio.h>
#include <stdlib.h>
#include "primitivas.h"
#include "leitura.h"

int main()
{
    char primitiva[8];
    FILE *arquivo_input;
    FILE *arquivo_imagem;
    poligono *polygon;
    polygon = (poligono*) calloc(3, sizeof(polygon));

    arquivo_input = fopen("input.txt", "r");
    image(arquivo_input);
    pixel pixels[imagem.X][imagem.Y];

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
                case primitive_color: break;
                case primitive_clear: clear(arquivo_input, pixels);
                    break;
                case primitive_rect: break;
                case primitive_circle: break;
                case primitive_polygon: break;
                case primitive_fill: break;
                case primitive_save:
                    save(arquivo_input, pixels);
                    break;
                case primitive_open: break;
            }

            free(polygon);
        }


    }

    /*color(23,47,103,pincel);
    fill(X, Y, desenho, pincel);
    printf("batata\n");
    salvar_imagem(X, Y, desenho);*/

    fclose(arquivo_input);
    return 0;
}
