#include "main.h"

int main()
{
  int X = 600, Y = 400;
  imagem desenho[X][Y];
  imagem *ptr_desenho;

  pintar_imagem(ptr_desenho, X, Y);
  printf("batata\n");
  salvar_imagem(ptr_desenho, X, Y);

  return 0;
}
