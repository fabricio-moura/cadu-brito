#include "primitivas.h"

void image(FILE *arquivo)
{
    fscanf(arquivo, "image %d %d", &imagem.X, &imagem.Y);
}

void clear(FILE *arquivo, pixel pixels[imagem.X][imagem.Y])
{
    int red, green, blue;
    // Está lendo um número aleatório da memória
    fscanf(arquivo, "%d\n", &red);
    printf("%d %d %d\n", red, green, blue);
    for(int i = 0; i < imagem.X; i++)
    {
        for(int j = 0; j < imagem.Y; j++)
        {
            pixels[i][j].RGB.red = red;
            pixels[i][j].RGB.green = green;
            pixels[i][j].RGB.blue = blue;
        }
    }
}

void color(int red, int green, int blue, cor pincel)
{
    pincel.red = red;
    pincel.green = green;
    pincel.blue = blue;
}

void fill(int X, int Y, cor desenho[imagem.X][imagem.Y], cor pincel)
{
    for(int i = 0; i < imagem.X; i++)
    {
        for(int j = 0; j < imagem.Y; j++)
        {
            desenho[i][j].red = pincel.red;
            desenho[i][j].green = pincel.green;
            desenho[i][j].blue = pincel.blue;
        }
    }
}

// Isso aqui deu errado, ainda tenho que ver como mexe. Ver project board.
/*FILE open()
{
  FILE *file;
  file = fopen("teste.txt", "r");
  if(file == NULL)
  {
    printf( "Erro na abertura do arquivo!\n" );
  }

  return *file;
}*/

void save(FILE *arquivo_input, pixel pixels[imagem.X][imagem.Y])
{
    FILE *arquivo_imagem;
    char nome_imagem[30];

    fscanf(arquivo_input, " %s", nome_imagem);
    arquivo_imagem = fopen(nome_imagem, "w");

    fprintf(arquivo_imagem, "P3\n%d %d\n255\n", imagem.X, imagem.Y);
    for(int i = 0; i < imagem.X; i++)
    {
        for(int j = 0; j < imagem.Y; j++)
        {
            fprintf(arquivo_imagem, "%d %d %d\n", pixels[i][j].RGB.red, pixels[i][j].RGB.green, pixels[i][j].RGB.blue);
        }
    }

    fclose(arquivo_imagem);
}
