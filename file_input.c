#include <stdio.h>

typedef struct
{
    int red;
    int green;
    int blue;
} imagem;

int main()
{
    int X, Y;
    int qualidade;
    FILE *arquivo;

    arquivo = fopen("input.txt", "r");

    fscanf(arquivo, "P3\n%d %d\n%d\n", &X, &Y, &qualidade);

    imagem desenho[X][Y];

    for(int i = 0; i < X; i++)
    {
        for(int j = 0; j < Y; j++)
        {
            fscanf(arquivo, "%d %d %d", &desenho[i][j].red, &desenho[i][j].green, &desenho[i][j].blue);
        }
    }

    for(int i = 0; i < X; i++)
    {
        for(int j = 0; j < Y; j++)
        {
            printf("%d %d %d\n", desenho[i][j].red, desenho[i][j].green, desenho[i][j].blue);
        }
    }

    fclose(arquivo);
    return 0;
}
