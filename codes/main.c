#include "main.h"

int main()
{
  int X = 600, Y = 400;
  imagem desenho[X][Y];

  pintar_imagem(X, Y, desenho);
  printf("batata\n");
  salvar_imagem(X, Y, desenho);

  return 0;
}
