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
    poligonal **ptr_poligono;

    pixels = (pixel**) malloc (1 * sizeof (pixel*));
    checar_mempixel(pixels, -1);
    pixels[0] = (pixel*) malloc (1 * sizeof (pixel));
    checar_mempixel (pixels, 0);

    ptr_pixels = &pixels;

    poligono = (poligonal*) malloc (3 * sizeof (poligono));
    checar_mempoligono (poligono);

    ptr_poligono = &poligono;

    desenho.X = 0;

    checar_nome_input (ptr_input);
    arquivo_input = fopen (nome_input, "r");
    checar_fopen (arquivo_input);

    while (fscanf (arquivo_input,"%s", primitiva) != EOF)
    {
        switch (checar_primitiva (primitiva))
        {
            case primitive_image:
                image (arquivo_input, ptr_desenho, ptr_pixels);
                break;
            case primitive_open:
                open (arquivo_input, ptr_desenho, ptr_pixels);
                break;
            case primitive_save:
                save (arquivo_input, ptr_desenho, ptr_pixels);
                break;
            case primitive_compress:
                compress (arquivo_input);
                break;
            case primitive_decompress:
                decompress (arquivo_input);
                break;
            case primitive_color:
                color (arquivo_input);
                break;
            case primitive_clear:
                clear (arquivo_input, ptr_desenho, ptr_pixels);
                break;
            case primitive_fill:
                fill (arquivo_input, ptr_desenho, ptr_pixels );
                break;
            case primitive_rect:
                rect (arquivo_input, ptr_desenho, ptr_pixels);
                break;
            case primitive_polygon:
                polygon (arquivo_input, ptr_desenho, ptr_pixels, ptr_poligono);
                //free(poligono);
                break;
            case primitive_circle:
                circle (arquivo_input, ptr_desenho, ptr_pixels);
                break; 
            default:
                printf ("Primitiva inválida.\n");
                exit (1);
        }
    }
    
    for (int i = 0; i < desenho.X; i++)
    {
        free (pixels[i]);
    }
    free (pixels);
    free (poligono);
    fclose (arquivo_input);

    return 0;
}
