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

void checar_resolucao(imagem *ptr_desenho)
{
    if(ptr_desenho->X < 1 || ptr_desenho->Y < 1 ||
        ptr_desenho->X > 4000 || ptr_desenho->Y > 4000)
    {
        printf("%d %d\n", ptr_desenho->X, ptr_desenho->Y);
        printf("Resolução inválida! Insira uma resolução entre 1 e 4000.\n");
        exit(-1);
    }
}

void checar_mempixel(pixel **pixels, imagem *ptr_desenho, int counter)
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
