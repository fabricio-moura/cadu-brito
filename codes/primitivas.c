#include "primitivas.h"

void color(int red, int green, int blue, cor pincel)
{
    pincel.red = red;
    pincel.green = green;
    pincel.blue = blue;
}

void fill(int X, int Y, cor desenho[X][Y], cor pincel)
{
    for(int i = 0; i < X; i++)
    {
        for(int j = 0; j < Y; j++)
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

void salvar_imagem(int X, int Y, cor desenho[X][Y])
{
      FILE *arquivo;
      arquivo = fopen("imagem.ppm", "w");

      fprintf(arquivo, "P3\n%d %d\n255\n", X, Y);
      for(int i = 0; i < X; i++)
      {
        for(int j = 0; j < Y; j++)
        {
            fprintf(arquivo, "%d %d %d\n", desenho[i][j].red,
                    desenho[i][j].green, desenho[i][j].blue);
        }
      }

  fclose(arquivo);
}
