#include "primitivas.h"

/*int PA(int n)
{
    int soma = 1;
    for(int i = 2; i<n;i++)
    {
        soma = soma + i;
    }

    return soma;
}

void octante(imagem *ptr_desenho, pixel ***ptr_pixels)
{
    int octante_X, octante_Y;
    int k;

    if(ptr_desenho->X % 2 != 0)
    {
        octante_X = (ptr_desenho->X-1)/2;
    }
    else
    {
        octante_X = (ptr_desenho->X-2)/2;
    }
    if(ptr_desenho->Y % 2 != 0)
    {
        octante_Y = (ptr_desenho->Y-1)/2;
    }
    else
    {
        octante_Y = (ptr_desenho->Y-2)/2;
    }
    printf("%d\n", octante_X);
    printf("%d\n", octante_Y);

    k = 0;
    for(int i = ptr_desenho->X - octante_X+2; i <= ptr_desenho->X; i++)
    {
        printf("oi\n");
        for(int j = octante_Y; j > octante_Y-k-1; j--)
        {
            printf("tei\n");
            printf("%d %d", i, j);
            (*ptr_pixels)[j][i].octante = 1;
        }
        k++;
    }
    for(int i = 0; i < octante_X-1; i++)
    {
        for(int j = 1+i; j < octante_Y; j++)
        {
            (*ptr_pixels)[j][i].octante = 4;
        }
    }

    for(int i = 0; i < ptr_desenho->X; i++)
    {
        for(int j = 0; j < ptr_desenho->Y; j++)
        {
            printf("%d %d Octante %d\n", i, j, (*ptr_pixels)[i][j].octante);
        }
    }
}*/
void paint_pixels(int eixo_x, int eixo_y, pixel ***ptr_pixels)
{
    (*ptr_pixels)[eixo_x][eixo_y].RGB.red = pincel.RGB.red;
    (*ptr_pixels)[eixo_x][eixo_y].RGB.green = pincel.RGB.green;
    (*ptr_pixels)[eixo_x][eixo_y].RGB.blue = pincel.RGB.blue;
}

/*void line_circle(int x_centro, int y_centro, int tamanho, pixel ***ptr_pixels)
{



}*/

void line(int x_final, int y_final, int x_inicial, int y_inicial, pixel ***ptr_pixels)
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
        inclinacao = (float)(y_final - y_inicial)/(x_final - x_inicial);
    }
    inclinacao = fabs(inclinacao);

    while(x_inicial <= x_final || y_inicial <= y_final || x_inicial >= x_final || y_inicial >= y_final )
    {
        //printf("X %d Y %d\n", x_inicial, y_inicial);
        acumulado = inclinacao;
        //printf("inclinação %f\n", inclinacao);
        while(acumulado <= 1)
        {
            //printf("inclinação %f\n", inclinacao);
            (*ptr_pixels)[x_inicial][y_inicial].RGB.red = pincel.RGB.red;
            (*ptr_pixels)[x_inicial][y_inicial].RGB.green = pincel.RGB.green;
            (*ptr_pixels)[x_inicial][y_inicial].RGB.blue = pincel.RGB.blue;
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
            //printf("Acumulado %f\n", acumulado);
        }
        if(y_inicial < y_final)
        {
            y_inicial++;
        }
        else if(y_inicial > y_final)
        {
            y_inicial--;
        }
        if(x_inicial == x_final && y_inicial == y_final)
        {
            break;
        }

            //printf("X %d Y %d b\n", x_inicial, y_inicial);
    }
}

void image(FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    fscanf(arquivo, " %d %d\n", &ptr_desenho->X, &ptr_desenho->Y);
    checar_resolucao(ptr_desenho);

    *ptr_pixels = (pixel**) realloc(*ptr_pixels,
                    (ptr_desenho->X)*sizeof(pixel*));

    checar_mempixel(*ptr_pixels, -1);
    for(int i = 0; i < ptr_desenho->X; i++)
    {
        (*ptr_pixels)[i] = (pixel*) realloc((*ptr_pixels)[i],
                            (ptr_desenho->Y)*sizeof(pixel));

        checar_mempixel(*ptr_pixels, i);
    }
}

void color(FILE *arquivo)
{
    fscanf(arquivo, " %d %d %d\n", &pincel.RGB.red, &pincel.RGB.green,
            &pincel.RGB.blue);
}

void clear(FILE *arquivo, pixel ***ptr_pixels, imagem *ptr_desenho)
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

void rect(FILE *arquivo, pixel ***ptr_pixels)
{
    fscanf(arquivo, " %d %d %d\n", &retangulo.X, &retangulo.Y,
            &retangulo.tamanho);
    line(0,0,499,499, ptr_pixels);
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
void circle(FILE *arquivo, pixel ***ptr_pixels)
{
    fscanf(arquivo, " %d %d %d\n", &circulo.X, &circulo.Y, &circulo.tamanho);

    circle_line(0, circulo.tamanho, 3-(2*circulo.tamanho), ptr_pixels);
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

void fill_spread(int X, int Y, pixel ***ptr_pixels, imagem *ptr_desenho)
{
    paint_pixels(X, Y, ptr_pixels);

    if(Y+1 < ptr_desenho->Y &&
        (*ptr_pixels)[X][Y+1].RGB.red == pincel_fill.RGB.red &&
        (*ptr_pixels)[X][Y+1].RGB.green == pincel_fill.RGB.green &&
        (*ptr_pixels)[X][Y+1].RGB.blue == pincel_fill.RGB.blue)
    {
        fill_spread(X, Y+1, ptr_pixels, ptr_desenho);
    }

    if(Y-1 >=0 && (*ptr_pixels)[X][Y-1].RGB.red == pincel_fill.RGB.red &&
        (*ptr_pixels)[X][Y-1].RGB.green == pincel_fill.RGB.green &&
        (*ptr_pixels)[X][Y-1].RGB.blue == pincel_fill.RGB.blue)
    {
        (*ptr_pixels)[X][Y].RGB.red = pincel.RGB.red;
        (*ptr_pixels)[X][Y].RGB.green = pincel.RGB.blue;
        (*ptr_pixels)[X][Y].RGB.blue = pincel.RGB.green;
        fill_spread(X, Y-1, ptr_pixels, ptr_desenho);
    }

    if(X+1 < ptr_desenho->X &&
        (*ptr_pixels)[X+1][Y].RGB.red == pincel_fill.RGB.red &&
        (*ptr_pixels)[X+1][Y].RGB.green == pincel_fill.RGB.green &&
        (*ptr_pixels)[X+1][Y].RGB.blue == pincel_fill.RGB.blue)
    {
        (*ptr_pixels)[X][Y].RGB.red = pincel.RGB.red;
        (*ptr_pixels)[X][Y].RGB.green = pincel.RGB.blue;
        (*ptr_pixels)[X][Y].RGB.blue = pincel.RGB.green;
        fill_spread(X+1, Y, ptr_pixels, ptr_desenho);
    }
    if(X-1 >= 0 && (*ptr_pixels)[X-1][Y].RGB.red == pincel_fill.RGB.red &&
        (*ptr_pixels)[X-1][Y].RGB.green == pincel_fill.RGB.green &&
        (*ptr_pixels)[X-1][Y].RGB.blue == pincel_fill.RGB.blue)
    {
        (*ptr_pixels)[X][Y].RGB.red = pincel.RGB.red;
        (*ptr_pixels)[X][Y].RGB.green = pincel.RGB.blue;
        (*ptr_pixels)[X][Y].RGB.blue = pincel.RGB.green;
        fill_spread(X-1, Y, ptr_pixels, ptr_desenho);
    }
}

void fill(FILE *arquivo, pixel ***ptr_pixels, imagem *ptr_desenho)
{
    int X, Y;

    fscanf(arquivo, " %d %d\n", &X, &Y);
    checar_coordenadas(X, Y, ptr_desenho, "fill");

    pincel_fill.RGB.red = (*ptr_pixels)[X][Y].RGB.red;
    pincel_fill.RGB.green = (*ptr_pixels)[X][Y].RGB.green;
    pincel_fill.RGB.blue = (*ptr_pixels)[X][Y].RGB.blue;

    fill_spread(X, Y, ptr_pixels, ptr_desenho);
}

void save(FILE *arquivo_input, pixel ***ptr_pixels, imagem *ptr_desenho)
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

void open(FILE *arquivo_input, pixel ***ptr_pixels, imagem *ptr_desenho)
{
    FILE *input_imagem;
    char nome_imagem[30];
    int qualidade;
    char formato[3];

    fscanf(arquivo_input, "%s", nome_imagem);
    input_imagem = fopen(nome_imagem, "r");
    checar_fopen(input_imagem);

    fscanf(input_imagem, "%s\n%d %d\n%d", formato, &ptr_desenho->X,
            &ptr_desenho->Y, &qualidade);
    checar_formato(formato);
    checar_resolucao(ptr_desenho);
    if(qualidade != 255)
        printf("Qualidade inválida. Abra um arquivo com qualidade 255.\n");

    *ptr_pixels = (pixel**) realloc(*ptr_pixels,
                                    (ptr_desenho->X)*sizeof(pixel*));
    checar_mempixel(*ptr_pixels, -1);
    for(int i = 0; i < ptr_desenho->X; i++)
    {
        (*ptr_pixels)[i] = (pixel*) realloc((*ptr_pixels)[i],
                                            (ptr_desenho->Y)*sizeof(pixel));
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
            printf("%d %d %d %d %d\n", i, j, (*ptr_pixels)[i][j].RGB.red,
            (*ptr_pixels)[i][j].RGB.green,
            (*ptr_pixels)[i][j].RGB.blue);
        }
    }

    fclose(input_imagem);
}
