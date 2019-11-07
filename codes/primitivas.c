#include "primitivas.h"

void paint_pixels(int eixo_x, int eixo_y, pixel ***ptr_pixels)
{
    (*ptr_pixels)[eixo_x][eixo_y].RGB.red = pincel.RGB.red;
    (*ptr_pixels)[eixo_x][eixo_y].RGB.green = pincel.RGB.green;
    (*ptr_pixels)[eixo_x][eixo_y].RGB.blue = pincel.RGB.blue;
}

void line(
    int x_final,
    int y_final,
    int x_inicial,
    int y_inicial,
    pixel ***ptr_pixels)
{
    float inclinacao;
    float acumulado;
    if(y_final - y_inicial == 0)
    {
        inclinacao = 1;
    }
    else if(x_final - x_inicial == 0)
    {
        inclinacao = 1;
    }
    else
    {
        inclinacao = (float) (y_final - y_inicial)/(x_final - x_inicial);
    }
    inclinacao = fabs(inclinacao);

    while(
        x_inicial <= x_final
        || y_inicial <= y_final
        || x_inicial >= x_final
        || y_inicial >= y_final)
    {
        printf("X %d Y %d\n", x_inicial, y_inicial);
        acumulado = inclinacao;
        printf("inclinação %f\n", inclinacao);
        while(acumulado <= 1)
        {
            //printf("inclinação %f\n", inclinacao);
            paint_pixels(x_inicial, x_final, ptr_pixels);
            if(x_inicial < x_final)
            {
                x_inicial++;
            }
            else if(x_inicial > x_final)
            {
                x_inicial--;
            }
            else
            {
                break;
            }
            acumulado += inclinacao;
            printf("Acumulado %f\n", acumulado);
        }
        if(y_inicial < y_final)
        {
            y_inicial++;
        }
        else if(y_inicial > y_final)
        {
            y_inicial--;
        }
        if(x_inicial == x_final || y_inicial == y_final)
        {
            break;
        }

        printf("X %d Y %d b\n", x_inicial, y_inicial);
    }
}

void image(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    fscanf(arquivo, " %d %d\n", &ptr_desenho->X, &ptr_desenho->Y);
    checar_resolucao(ptr_desenho);

    *ptr_pixels = (pixel**) realloc(
                                *ptr_pixels,
                                (ptr_desenho->X)
                                * sizeof(pixel*));

    checar_mempixel(*ptr_pixels, -1);
    for(int i = 0; i < ptr_desenho->X; i++)
    {
        (*ptr_pixels)[i] = (pixel*) realloc(
                                        (*ptr_pixels)[i],
                                        (ptr_desenho->Y)
                                        * sizeof(pixel));
        checar_mempixel(*ptr_pixels, i);
    }
}

void color(FILE *arquivo)
{
    fscanf(arquivo, " %d %d %d\n",
            &pincel.RGB.red,
            &pincel.RGB.green,
            &pincel.RGB.blue);
}

void clear(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    int red, green, blue;

    fscanf(arquivo, " %d %d %d\n", &red, &blue, &green);
    printf("Clear na cor %d %d %d\n", red, blue, green);
    for(int i = 0; i < ptr_desenho->X; i++)
    {
        for(int j = 0; j < ptr_desenho->Y; j++)
        {
            (*ptr_pixels)[i][j].RGB.red = red;
            (*ptr_pixels)[i][j].RGB.green = green;
            (*ptr_pixels)[i][j].RGB.blue = blue;
        }
    }
}

void rect(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    fscanf(arquivo, " %d %d %d\n",
            &retangulo.X,
            &retangulo.Y,
            &retangulo.tamanho);
    checar_coordenadas(retangulo.X, retangulo.Y, ptr_desenho, "rect");
}

void circle_line(int x, int y, int decisao, pixel ***ptr_pixels)
{
    if(y >= x)
    {
        paint_pixels(circulo.X+x, circulo.Y+y, ptr_pixels);
        paint_pixels(circulo.X+x, circulo.Y-y, ptr_pixels);
        paint_pixels(circulo.X-x, circulo.Y+y, ptr_pixels);
        paint_pixels(circulo.X-x, circulo.Y-y, ptr_pixels);
        paint_pixels(circulo.X+y, circulo.Y+x, ptr_pixels);
        paint_pixels(circulo.X+y, circulo.Y-x, ptr_pixels);
        paint_pixels(circulo.X-y, circulo.Y+x, ptr_pixels);
        paint_pixels(circulo.X-y, circulo.Y-x, ptr_pixels);

        if(decisao > 0)
        {
            decisao = decisao + 4 * (x - y) + 10;
            y--;
        }
        else
        {
            decisao = decisao + 4 * x + 6;
        }
        x++;
        circle_line(x, y, decisao, ptr_pixels);
    }
}

// Algoritmo de Bresenham copiado.
void circle(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    fscanf(arquivo, " %d %d %d\n", &circulo.X, &circulo.Y, &circulo.tamanho);
    checar_coordenadas(circulo.X, circulo.Y, ptr_desenho, "circle");

    circle_line(0, circulo.tamanho, 3-(2*circulo.tamanho), ptr_pixels);
}

void polygon(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels, poligonal **ptr_poligono)
{
    fscanf(arquivo, " %d", &(*ptr_poligono)->pontos);

    *ptr_poligono = (poligonal*) realloc(
                                    *ptr_poligono,
                                    (*ptr_poligono)->pontos
                                    * sizeof(poligonal));

    for(int i = 0; i < (*ptr_poligono)->pontos; i++)
    {
        fscanf(arquivo, " %d %d", &(*ptr_poligono)[i].X, &(*ptr_poligono)[i].Y);
        checar_coordenadas(
                        (*ptr_poligono)[i].X,
                        (*ptr_poligono)[i].Y,
                        ptr_desenho, "polygon");
                        printf("%d %d\n", (*ptr_poligono)[i].X, (*ptr_poligono)[i].Y);
    }

    int i;
    while((*ptr_poligono)->pontos > 1)
    {
        i = (*ptr_poligono)->pontos-1;
        printf("vai\n");

        line((*ptr_poligono)[i].X, (*ptr_poligono)[i].Y, (*ptr_poligono)[i-1].X, (*ptr_poligono)[i-1].Y, ptr_pixels);
        printf("%d %d %d %d\n",(*ptr_poligono)[i].X, (*ptr_poligono)[i].Y, (*ptr_poligono)[0].X, (*ptr_poligono)[0].Y);
        (*ptr_poligono)->pontos--;
        *ptr_poligono = (poligonal*) realloc(
                                        *ptr_poligono,
                                        (*ptr_poligono)->pontos
                                        * sizeof(poligonal));
        printf("%d\n", i);
    }
    printf("banana");
}

void fill_spread(int X, int Y, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    printf("%d %d\n", X, Y);
    paint_pixels(X, Y, ptr_pixels);

    if(Y+1 < ptr_desenho->Y && checar_proxpixel(X, Y+1, ptr_pixels))
    {
        fill_spread(X, Y+1, ptr_desenho, ptr_pixels);
    }

    if(Y-1 >= 0 && checar_proxpixel(X, Y-1, ptr_pixels))
    {
        fill_spread(X, Y-1, ptr_desenho, ptr_pixels);
    }

    if(X+1 < ptr_desenho->X && checar_proxpixel(X+1, Y, ptr_pixels))
    {
        fill_spread(X+1, Y, ptr_desenho, ptr_pixels);
    }

    if(X-1 >= 0 && checar_proxpixel(X-1, Y, ptr_pixels))
    {
        fill_spread(X-1, Y, ptr_desenho, ptr_pixels);
    }

}

void fill(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    int X, Y;

    fscanf(arquivo, " %d %d\n", &X, &Y);
    checar_coordenadas(X, Y, ptr_desenho, "fill");

    pincel_fill.RGB.red = (*ptr_pixels)[X][Y].RGB.red;
    pincel_fill.RGB.green = (*ptr_pixels)[X][Y].RGB.green;
    pincel_fill.RGB.blue = (*ptr_pixels)[X][Y].RGB.blue;

    fill_spread(X, Y,ptr_desenho, ptr_pixels );
}

void save(FILE *arquivo_input, imagem *ptr_desenho, pixel ***ptr_pixels)
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
            fprintf(arquivo_imagem, "%d %d %d\n",
                    (*ptr_pixels)[i][j].RGB.red,
                    (*ptr_pixels)[i][j].RGB.green,
                    (*ptr_pixels)[i][j].RGB.blue);
        }
    }

    fclose(arquivo_imagem);
}

void open(FILE *arquivo_input, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    FILE *input_imagem;
    char nome_imagem[30];
    int qualidade;
    char formato[3];

    fscanf(arquivo_input, "%s", nome_imagem);
    input_imagem = fopen(nome_imagem, "r");
    checar_fopen(input_imagem);

    fscanf(input_imagem, "%s\n%d %d\n%d",
            formato, &ptr_desenho->X,
            &ptr_desenho->Y, &qualidade);
    checar_formato(formato);
    checar_resolucao(ptr_desenho);
    if(qualidade != 255)
    {
        printf("Qualidade inválida. Abra um arquivo com qualidade 255.\n");
    }

    *ptr_pixels = (pixel**) realloc(
                                *ptr_pixels,
                                (ptr_desenho->X)
                                * sizeof(pixel*));
    checar_mempixel(*ptr_pixels, -1);
    for(int i = 0; i < ptr_desenho->X; i++)
    {
        (*ptr_pixels)[i] = (pixel*) realloc(
                                        (*ptr_pixels)[i],
                                        (ptr_desenho->Y)
                                        * sizeof(pixel));
        checar_mempixel(*ptr_pixels, i);
    }

    for(int i = 0; i < ptr_desenho->X; i++)
    {
        for(int j = 0; j < ptr_desenho->Y; j++)
        {
            fscanf(input_imagem, "%d %d %d",
                    &(*ptr_pixels)[i][j].RGB.red,
                    &(*ptr_pixels)[i][j].RGB.green,
                    &(*ptr_pixels)[i][j].RGB.blue);
            printf("%d %d %d %d %d\n",
                    i, j, (*ptr_pixels)[i][j].RGB.red,
                    (*ptr_pixels)[i][j].RGB.green,
                    (*ptr_pixels)[i][j].RGB.blue);
        }
    }

    fclose(input_imagem);
}
