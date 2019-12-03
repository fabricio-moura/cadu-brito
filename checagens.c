#include "checagens.h"

// Recebe um vetor da matriz pixels alocada dinamicamente e encerra o programa
// caso o vetor seja nulo.
void checar_mempixel (pixel **pixels, int counter)
{
    if (counter == -1)
    {
        if (pixels == NULL)
        {
            printf ("Erro! Memória Insuficiente.\n");
            exit(1);
        }
    }
    else
    {
        if (pixels[counter] == NULL)
        {
            printf("Erro! Memória Insuficiente.\n");
            exit(1);
        }
    }
}

// Recebe um vetor poligono alocado dinamicamente e encerra o programa caso ele
// seja nulo.
void checar_mempoligono (poligonal *poligono)
{
    if (poligono == NULL)
    {
        printf ("Erro! Memória Insuficiente.\n");
        exit (1);
    }
}

// Recebe um arquivo e encerra o programa caso ele seja nulo.
void checar_fopen (FILE *arquivo)
{
    if (arquivo == NULL)
    {
        printf ("Erro ao abrir arquivo!\n");
        exit (1);
    }
}

// Recebe do usuário o nome do arquivo .txt que será utilizado para leitura dos
// comandos.
void checar_nome_input (char *ptr_input)
{
    printf ("Insira o nome do arquivo .txt ou o digito '0' para padrão: ");
    scanf ("%s", ptr_input);

    if (strcmp (ptr_input, "0") == 0)
    {
        strcpy (ptr_input, "input.txt");
    }
}

// Recebe uma string contendo o comando lido do arquivo .txt e retorna o
// resultado da análise.
int checar_primitiva (char *primitiva)
{
    if (strcmp (primitiva, "image") == 0)
    {
        return primitive_image;
    }
    else if (strcmp (primitiva, "open") == 0)
    {
        return primitive_open;
    }
    else if (strcmp (primitiva, "save") == 0)
    {
        return primitive_save;
    }
    else if (strcmp (primitiva, "compress") == 0)
    {
        return primitive_compress;
    }
    else if (strcmp (primitiva, "decompress") == 0)
    {
        return primitive_decompress;
    }
    else if (strcmp (primitiva, "color") == 0)
    {
        return primitive_color;
    }
    else if (strcmp (primitiva, "clear") == 0)
    {
        return primitive_clear;
    }
    else if (strcmp (primitiva, "fill") == 0)
    {
        return primitive_fill;
    }
    else if (strcmp (primitiva, "rect") == 0)
    {
        return primitive_rect;
    }
    else if (strcmp (primitiva, "polygon") == 0)
    {
        return primitive_polygon;
    }
    else if (strcmp (primitiva, "circle") == 0)
    {
        return primitive_circle;
    }

    return -1;
}

// Recebe um formato e encerra o programa em caso de invalidez.
void checar_formato (char *formato)
{
    if (strcmp (formato, "P3") != 0)
    {
        printf ("Formato de arquivo inválido!\n");
        exit (1);
    }
}

// Recebe um ponteiro struct contendo a resolução do desenho e encerra o
// programa em caso de resolução inválida.
void checar_resolucao (imagem *ptr_desenho)
{
    if (ptr_desenho->X < 1 || ptr_desenho->Y < 1
        || ptr_desenho->X > 4000 || ptr_desenho->Y > 4000)
    {
        printf ("Resolução inválida! Insira uma resolução entre 1 e 4000.\n");
        exit (1);
    }
}

// Recebe um valor de qualidade e encerra o programa em caso de invalidez.
void checar_qualidade(int qualidade)
{
    if (qualidade != 255)
    {
        printf ("Qualidade inválida. Abra um arquivo com qualidade 255.\n");
        exit (1);
    }
}

// Recebe uma cor e encerra o programa caso ela seja inválida.
void checar_cor (int red, int green, int blue, char *comando)
{
    if ( red > 255 || red < 0
        || green > 255 || green < 0
        || blue > 255 || blue < 0)
    {
        printf ("Cor inválida no comando %s.\n", comando);
        exit (1);
    }
}

// Recebe uma coordenada, um ponteiro de uma matriz de pixels alocada
// dinamicamente e checa se a cor do pixel nessa coordenada da matriz é
// diferente da cor do pincel_fill.
int checar_proxpixel (int X, int Y, pixel ***ptr_pixels)
{
    if ((*ptr_pixels)[X][Y].RGB.red != pincel_fill.RGB.red
        || (*ptr_pixels)[X][Y].RGB.green != pincel_fill.RGB.green
        || (*ptr_pixels)[X][Y].RGB.blue != pincel_fill.RGB.blue)
    {
        return 0;
    }

    return 1;
}

// Recebe uma coordenada, um ponteiro struct contendo a resolução do desenho e
// verifica se a coordenada está dentro da resolução do desenho.
void checar_coordenadas (int X, int Y, imagem *ptr_desenho, char *comando)
{
    if (X < 0 || Y < 0 || X > ptr_desenho->X-1 || Y > ptr_desenho->Y-1)
    {
        printf ("Posição de coordenada do comando %s inválida.\n", comando);
        exit (1);
    }
}

// Recebe uma coordenadas, as medidas de largura e altura, um ponteiro struct
// contendo a resolução do desenho e encerra o programa caso o retângulo não
// caiba na imagem.
void checar_medidas (int largura, int altura, int X, int Y, imagem *ptr_desenho)
{
    if (largura >= ptr_desenho->Y || largura < 1)
    {
        printf ("Largura do retângulo inválida.\n");
        exit (1);
    }
    else if (altura >= ptr_desenho->X || altura < 1)
    {
        printf ("Altura do retângulo inválida.\n");
        exit (1);
    }
}

// Recebe um ponteiro do vetor poligono alocado dinamicamente e encerra o
// programa caso a quantidade de pontos seja inválida.
void checar_pontos (poligonal **ptr_poligono)
{
    if ((*ptr_poligono)->pontos < 3)
    {
        printf("Quantidade de pontos inválida.\n");
        exit(1);
    }
}

// Recebe um ponteiro struct contendo a resolução do desenho e encerra o
// programa caso o circulo não caiba na imagem.
void checar_raio (imagem *ptr_desenho)
{
    if (circulo.X + circulo.tamanho > ptr_desenho->X - 1)
    {
        printf ("Circulo passando da imagem embaixo.\n");
        exit (1);
    }
    else if (circulo.X - circulo.tamanho < 0)
    {
        printf ("Circulo passando da imagem em cima.\n");
        exit (1);
    }
    else if (circulo.Y + circulo.tamanho > ptr_desenho->Y - 1)
    {
        printf ("Circulo passando da imagem pela direita.\n");
        exit (1);
    }
    else if (circulo.Y - circulo.tamanho < 0)
    {
        printf ("Circulo passando da imagem pela esquerda.\n");
        exit (1);
    }
}
