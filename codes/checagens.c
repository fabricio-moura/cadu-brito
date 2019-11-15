#include "checagens.h"

int checar_primitiva(char *primitiva)
{
    if(strcmp(primitiva, "image") == 0)
    {
        return primitive_image;
    }
    else if(strcmp(primitiva, "color") == 0)
    {
        return primitive_color;
    }
    else if(strcmp(primitiva, "clear") == 0)
    {
        return primitive_clear;
    }
    else if(strcmp(primitiva, "rect") == 0)
    {
        return primitive_rect;
    }
    else if(strcmp(primitiva, "circle") == 0)
    {
        return primitive_circle;
    }
    else if(strcmp(primitiva, "polygon") == 0)
    {
        return primitive_polygon;
    }
    else if(strcmp(primitiva, "fill") == 0)
    {
        return primitive_fill;
    }
    else if(strcmp(primitiva, "save") == 0)
    {
        return primitive_save;
    }
    else if(strcmp(primitiva, "open") == 0)
    {
        return primitive_open;
    }

    return -1;
}

void checar_formato(char *formato)
{
    if(strcmp(formato, "P3") != 0)
    {
        printf("Formato de arquivo inválido!\n");
        exit(1);
    }
}

void checar_qualidade(int qualidade)
{
    if(qualidade != 255)
    {
        printf("Qualidade inválida. Abra um arquivo com qualidade 255.\n");
        exit(1);
    }
}

void checar_resolucao(imagem *ptr_desenho)
{
    if(ptr_desenho->X < 1 || ptr_desenho->Y < 1 ||
        ptr_desenho->X > 4000 || ptr_desenho->Y > 4000)
    {
        printf("Resolução inválida! Insira uma resolução entre 1 e 4000.\n");
        exit(1);
    }
}

void checar_mempixel(pixel **pixels, int counter)
{
    if(counter == -1)
    {
        if(pixels == NULL)
        {
            printf ("Erro! Memória Insuficiente\n");
            exit(1);
        }
    }
    else
    {
        if(pixels[counter] == NULL)
        {
            printf("Erro! Memória Insuficiente\n");
            exit(1);
        }
    }
}

void checar_mempoligono(poligonal *poligono)
{
    if(poligono == NULL)
    {
        printf ("Erro! Memória Insuficiente\n");
        exit(1);
    }
}

void checar_fopen(FILE *arquivo)
{
    if(arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
}

void checar_nome_input(char *ptr_input)
{
    printf("Insira o nome do arquivo txt ou 0 para default: ");
    scanf("%s", ptr_input);
    if(strcmp(ptr_input, "0") == 0)
    {
        strcpy(ptr_input, "input.txt");
    }
}

void checar_coordenadas(int X, int Y, imagem *ptr_desenho, char *comando)
{
    if(X < 0 || Y < 0 || X > ptr_desenho->X-1 || Y > ptr_desenho->Y-1)
    {
        printf("Posição de coordenada do comando %s inválida.\n", comando);
        exit(1);
    }
}

int checar_proxpixel(int X, int Y, pixel ***ptr_pixels)
{
    if((*ptr_pixels)[X][Y].RGB.red != pincel_fill.RGB.red
        || (*ptr_pixels)[X][Y].RGB.green != pincel_fill.RGB.green
        || (*ptr_pixels)[X][Y].RGB.blue != pincel_fill.RGB.blue)
    {
        return 0;
    }

    return 1;
}

void checar_cor(int red, int green, int blue, char *comando)
{
    if( red > 255 || red < 0
        || green > 255 || green < 0
        || blue > 255 || blue < 0)
    {
        printf("Cor inválida no comando %s.\n", comando);
        exit(1);
    }
}

void checar_pontos(poligonal **ptr_poligono)
{
    if((*ptr_poligono)->pontos < 3)
    {
        printf("Quantidade de pontos inválida.\n");
        exit(1);
    }
}

void checar_medidas(int largura, int altura, int X, int Y, imagem *ptr_desenho)
{
    if(largura > ptr_desenho->Y || largura < 1)
    {
        printf("Largura do retângulo inválida.\n");
        exit(1);
    }
    else if(altura > ptr_desenho->X || altura < 1)
    {
        printf("Altura do retângulo inválida.\n");
        exit(1);
    }
    else if(largura + Y > ptr_desenho->Y - 1)
    {
        printf("Largura maior que o desenho.\n");
        exit(1);
    }
    else if(altura + X > ptr_desenho->X - 1)
    {
        printf("Altura maior que o desenho.\n");
        exit(1);
    }
}

void checar_raio(imagem *ptr_desenho)
{
    if(circulo.X + circulo.tamanho > ptr_desenho->X - 1)
    {
        printf("Circulo passando da imagem embaixo.\n");
        exit(1);
    }
    else if(circulo.X - circulo.tamanho < 0)
    {
        printf("Circulo passando da imagem em cima.\n");
        exit(1);
    }
    else if(circulo.Y + circulo.tamanho > ptr_desenho->Y - 1)
    {
        printf("Circulo passando da imagem pela direita.\n");
        exit(1);
    }
    else if(circulo.Y - circulo.tamanho < 0)
    {
        printf("Circulo passando da imagem pela esquerda.\n");
        exit(1);
    }
}
