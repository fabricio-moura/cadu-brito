#include "primitivas.h"

void pintar_imagem(int X, int Y, imagem desenho[X][Y])
{
  for(int i = 0; i < X; i++)
  {
    for(int j = 0; j < Y; j++)
    {
        desenho[i][j].red = 243;
        desenho[i][j].green = 41;
        desenho[i][j].blue = 127;
    }
  }
}

void salvar_imagem(int X, int Y, imagem desenho[X][Y])
{
  FILE *arquivo;
  arquivo = fopen("imagem.ppm", "w");

  fprintf(arquivo, "P3\n%d %d\n255\n", X, Y);
  for(int i = 0; i < X; i++)
  {
    for(int j = 0; j < Y; j++)
    {
        fprintf(arquivo, "%d %d %d\n", desenho[i][j].red, desenho[i][j].green, desenho[i][j].blue);
    }
  }

  fclose(arquivo);
}
