#include "primitivas.h"

void image(FILE *arquivo, imagem *ptr_desenho, pixel **pixels)
{
    fscanf(arquivo, " %d %d", &ptr_desenho->X, &ptr_desenho->Y);
    printf("%d %d\n", ptr_desenho->X, ptr_desenho->Y);
    //checar_resolucao(ptr_desenho);
    pixels = (pixel**) realloc(pixels, (ptr_desenho->X)*sizeof(pixel*));
    checar_mempixel(pixels, ptr_desenho, -1);

    for(int i = 0; i < ptr_desenho->X; i++)
    {
        printf("%d\n",i);
        pixels[i] = (pixel*) malloc((ptr_desenho->Y)*sizeof(pixel));
        checar_mempixel(pixels, ptr_desenho, i);
    }
    printf("Desenho X Y %d %d\n", ptr_desenho->X, ptr_desenho->Y);
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
    printf("Clear na cor %d %d %d\n", red, blue, green);
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

void polygon(FILE *arquivo, poligonal *poligono)
{
    fscanf(arquivo, " %d", &poligono->pontos);

    poligono = realloc(poligono, poligono->pontos * sizeof(poligonal));

    for(int i = 0; i < poligono->pontos; i++)
    {
        fscanf(arquivo, " %d %d", &poligono[i].X, &poligono[i].Y);
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

void save(FILE *arquivo_input, pixel **pixels, imagem *ptr_desenho)
{
    FILE *arquivo_imagem;
    char nome_imagem[30];

    fscanf(arquivo_input, " %s", nome_imagem);
    arquivo_imagem = fopen(nome_imagem, "w");
    checar_fopen(arquivo_imagem);

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

void open(FILE *arquivo_input, pixel **pixels, imagem *ptr_desenho)
{
    FILE *input_imagem;
    char nome_imagem[30];
    int qualidade;
    char formato[3];

    fscanf(arquivo_input, "%s", nome_imagem);
    input_imagem = fopen(nome_imagem, "r");

    checar_fopen(input_imagem);

    fscanf(input_imagem, "%s\n%d %d\n%d", formato, &ptr_desenho->X, &ptr_desenho->Y, &qualidade);
    checar_formato(formato);
    checar_resolucao(ptr_desenho);
    if(qualidade != 255) printf("Qualidade inválida. Abra um arquivo com qualidade 255.\n");

    /*for(int i = 0; i < ptr_desenho->X; i++)
    {
        for(int j = 0; j < ptr_desenho->Y; j++)
        {
            fscanf(input_imagem, "%d %d %d", &pixels[i][j].RGB.red, &pixels[i][j].RGB.green, &pixels[i][j].RGB.blue);
        }
    }*/

    fclose(input_imagem);
}
