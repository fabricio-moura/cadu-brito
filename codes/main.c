#include "main.h"

int main()
{
    int X = 600, Y = 400, N;
    cor desenho[X][Y];
    char primitiva[8];
    FILE *arquivo;
    poligono *polygon;
    polygon = (poligono*) calloc(3, sizeof(poligono));

    arquivo = fopen("teste.txt", "r");

    while(1)
    {
        if(fscanf(arquivo,"%s", primitiva) == EOF)
        {
            break;
        }
        else
        {
            verificar_primitiva(primitiva, arquivo, polygon);
            for(int i = 0; i < sizeof(poligono)/sizeof(polygon); i++)
            {
                printf("%d %d\n", polygon[i].X, polygon[i].Y);
            }
            free(polygon);
        }


    }

    /*color(23,47,103,pincel);
    fill(X, Y, desenho, pincel);
    printf("batata\n");
    salvar_imagem(X, Y, desenho);*/

    fclose(arquivo);
    return 0;
}
