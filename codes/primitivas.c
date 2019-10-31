#include "primitivas.h"

void image(FILE *arquivo, imagem *ptr_desenho)
{
    fscanf(arquivo, " %d %d", &ptr_desenho->X, &ptr_desenho->Y);
}

void color(FILE *arquivo)
{
    fscanf(arquivo, " %d %d %d\n", &pincel.RGB.red, &pincel.RGB.green,
            &pincel.RGB.blue);
}

void clear(FILE *arquivo, pixel **pixels, imagem *ptr_desenho)
{
    int red, green, blue;

    fscanf(arquivo, " %d %d %d\n", &red, &blue, &green);

    for(int i = 0; i < ptr_desenho->X; i++)
    {
        for(int j = 0; j < ptr_desenho->Y; j++)
        {
            pixels[i][j].RGB.red = red;
            pixels[i][j].RGB.green = green;
            pixels[i][j].RGB.blue = blue;
        }
    }
}

void rect(FILE *arquivo)
{
    fscanf(arquivo, " %d %d %d\n", &retangulo.X, &retangulo.Y,
            &retangulo.tamanho);
}

void circle(FILE *arquivo)
{
    fscanf(arquivo, " %d %d %d\n", &circulo.X, &circulo.Y, &circulo.tamanho);
}

void polygon(FILE *arquivo, poligonal *polygon)
{
    int pontos;
    fscanf(arquivo, " %d", &pontos);
    polygon = realloc(polygon, pontos * sizeof(polygon));
    for(int i = 0; i < pontos; i++)
    {
        fscanf(arquivo, " %d %d", &polygon[i].X, &polygon[i].Y);
    }
}

void fill(FILE *arquivo, pixel **pixels, imagem *ptr_desenho)
{
    int X, Y;
    fscanf(arquivo, " %d %d\n", &X, &Y);

    for(int i = 0; i < ptr_desenho->X; i++)
    {
        for(int j = 0; j < ptr_desenho->Y; j++)
        {
            pixels[i][j].RGB.red = pincel.RGB.red;
            pixels[i][j].RGB.green = pincel.RGB.green;
            pixels[i][j].RGB.blue = pincel.RGB.blue;
        }
    }
}

void open(FILE *arquivo_input, pixel **pixels, imagem *ptr_desenho)
{
    FILE *input_imagem;
    char nome_imagem[30];

    fscanf(arquivo_input, " %s", nome_imagem);
    input_imagem = fopen(nome_imagem, "r");

    fscanf(input_imagem, "%*s\n%d %d\n%*d\n", &(ptr_desenho->X), &(ptr_desenho->Y));

    for(int i = 0; i < ptr_desenho->X; i++)
    {
        for(int j = 0; j < ptr_desenho->Y; j++)
        {
            fscanf(input_imagem, "%d %d %d\n", &pixels[i][j].RGB.red, &pixels[i][j].RGB.green, &pixels[i][j].RGB.blue);
        }
    }

    fclose(input_imagem);
}

void save(FILE *arquivo_input, pixel **pixels, imagem *ptr_desenho)
{
    FILE *arquivo_imagem;
    char nome_imagem[30];

    fscanf(arquivo_input, " %s", nome_imagem);
    arquivo_imagem = fopen(nome_imagem, "w");

    if(arquivo_imagem == NULL)
    {
        printf("Erro na abertura do arquivo!\n");
    }

    fprintf(arquivo_imagem, "P3\n%d %d\n255\n", ptr_desenho->X, ptr_desenho->Y);
    for(int i = 0; i < ptr_desenho->X; i++)
    {
        for(int j = 0; j < ptr_desenho->Y; j++)
        {
            fprintf(arquivo_imagem, "%d %d %d\n", pixels[i][j].RGB.red, pixels[i][j].RGB.green, pixels[i][j].RGB.blue);
        }
    }

    fclose(arquivo_imagem);
}
