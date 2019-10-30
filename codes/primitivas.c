#include "primitivas.h"

void image(FILE *arquivo, pixel **pixels, imagem desenho)
{
    fscanf(arquivo, " %d %d", &desenho.X, &desenho.Y);
    printf("%d\n", desenho.X);
    pixels = (pixel**) realloc(pixels, 10*sizeof(pixel*));
    if(pixels == NULL)
    {
        printf ("Erro: Memoria Insuficiente");
        exit(1);
    }

    for(int i = 0; i < 10; i++)
    {
        pixels[i] = (pixel*) realloc(pixels[i], 10*sizeof(pixel));
        if(pixels[i] == NULL)
        {
            printf("Erro: Memoria Insuficiente");
            exit(1);
        }
    }
}

void clear(FILE *arquivo, pixel **pixels, imagem *ptr_desenho)
{
    int red, green, blue;
    // Está lendo um número aleatório da memória
    fscanf(arquivo, "%d %d %d\n", &red, &blue, &green);
    printf("%d %d %d\n", red, green, blue);
    for(int i = 0; i < ptr_desenho->X; i++)
    {
        for(int j = 0; j < ptr_desenho->Y; j++)
        {
            pixels[i][j].RGB.red = 100;
            pixels[i][j].RGB.green = 100;
            pixels[i][j].RGB.blue = 100;
        }
    }
}

void color(int red, int green, int blue, cor pincel)
{
    pincel.red = red;
    pincel.green = green;
    pincel.blue = blue;
}

/*void fill(int X, int Y, cor ptr_desenho[ptr_desenho->X][ptr_desenho->Y], cor pincel, imagem ptr_desenho)
{
    for(int i = 0; i < ptr_desenho->X; i++)
    {
        for(int j = 0; j < ptr_desenho->Y; j++)
        {
            ptr_desenho[i][j].red = pincel.red;
            ptr_desenho[i][j].green = pincel.green;
            ptr_desenho[i][j].blue = pincel.blue;
        }
    }
}*/

void open(FILE *arquivo_input, pixel **pixels, imagem *ptr_desenho)
{
    FILE *input_imagem;
    char nome_imagem[30];
    fscanf(arquivo_input, " %s", nome_imagem);
    input_imagem = fopen(nome_imagem, "r");

    fscanf(input_imagem, "%*s\n%d %d\n", &(ptr_desenho->X), &(ptr_desenho->Y));
    printf("%d %d\n", ptr_desenho->X, ptr_desenho->Y);

    /*pixels = (pixel**) realloc(pixels, (ptr_desenho->X)*sizeof(pixel*));
    if(pixels == NULL)
    {
        printf ("Erro: Memoria Insuficiente");
        exit(1);
    }

    for(int i = 0; i < ptr_desenho->X; i++)
    {
        pixels[i] = (pixel*) realloc(pixels[i], (ptr_desenho->Y)*sizeof(pixel));
        if(pixels[i] == NULL)
        {
            printf("Erro: Memoria Insuficiente");
            exit(1);
        }
    }

    for(int i = 0; i < ptr_desenho->X; i++)
    {
        for(int j = 0; j < ptr_desenho->Y; j++)
        {
            fscanf(input_imagem, "%d %d %d\n", &pixels[i][j].RGB.red, &pixels[i][j].RGB.green, &pixels[i][j].RGB.blue);
        }
    }*/

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
