#include "primitivas.h"

void image (FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    fscanf (arquivo, " %hu %hu\n", &ptr_desenho->Y, &ptr_desenho->X);
    checar_resolucao (ptr_desenho);

    *ptr_pixels = (pixel**) realloc (
                                *ptr_pixels,
                                (ptr_desenho->X)
                                * sizeof (pixel*));

    checar_mempixel (*ptr_pixels, -1);
    for (int i = 0; i < ptr_desenho->X; i++)
    {
        (*ptr_pixels)[i] = (pixel*) realloc (
                                        (*ptr_pixels)[i],
                                        (ptr_desenho->Y)
                                        * sizeof (pixel));
        checar_mempixel (*ptr_pixels, i);
    }

    printf ("Imagem criada com resolução %dx%d.\n",
            ptr_desenho->Y, ptr_desenho->X);
}

void open (FILE *arquivo_input, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    FILE *input_imagem;
    char nome_imagem[30];
    char formato[3];
    int qualidade;

    fscanf (arquivo_input, "%s", nome_imagem);
    input_imagem = fopen (nome_imagem, "r");
    checar_fopen (input_imagem);

    fscanf (input_imagem, "%s\n%hu %hu\n%d",
            formato, &ptr_desenho->Y,
            &ptr_desenho->X, &qualidade);
    checar_formato (formato);
    checar_resolucao (ptr_desenho);
    checar_qualidade (qualidade);

    *ptr_pixels = (pixel**) realloc (
                                *ptr_pixels,
                                (ptr_desenho->X)
                                * sizeof (pixel*));
    checar_mempixel (*ptr_pixels, -1);
    for (int i = 0; i < ptr_desenho->X; i++)
    {
        (*ptr_pixels)[i] = (pixel*) realloc (
                                        (*ptr_pixels)[i],
                                        (ptr_desenho->Y)
                                        * sizeof (pixel));
        checar_mempixel (*ptr_pixels, i);
    }

    for (int i = 0; i < ptr_desenho->X; i++)
    {
        for (int j = 0; j < ptr_desenho->Y; j++)
        {
            fscanf (input_imagem, "%hhu %hhu %hhu",
                    &(*ptr_pixels)[i][j].RGB.red,
                    &(*ptr_pixels)[i][j].RGB.green,
                    &(*ptr_pixels)[i][j].RGB.blue);
            checar_cor (
                    (*ptr_pixels)[i][j].RGB.red,
                    (*ptr_pixels)[i][j].RGB.green,
                    (*ptr_pixels)[i][j].RGB.blue,
                    "open");
            //printf("%d %d %d %d %d\n", i, j, (*ptr_pixels)[i][j].RGB.red, (*ptr_pixels)[i][j].RGB.green, (*ptr_pixels)[i][j].RGB.blue);
        }
    }

    fclose (input_imagem);
}

void save (FILE *arquivo_input, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    FILE *arquivo_imagem;
    char nome_imagem[30];

    fscanf (arquivo_input, " %s", nome_imagem);
    arquivo_imagem = fopen (nome_imagem, "w");
    checar_fopen (arquivo_imagem);

    fprintf (arquivo_imagem, "P3\n%d %d\n255\n", ptr_desenho->Y, ptr_desenho->X);
    for (int i = 0; i < ptr_desenho->X; i++)
    {
        for (int j = 0; j < ptr_desenho->Y; j++)
        {
            fprintf (arquivo_imagem, "%d %d %d\n",
                    (*ptr_pixels)[i][j].RGB.red,
                    (*ptr_pixels)[i][j].RGB.green,
                    (*ptr_pixels)[i][j].RGB.blue);
        }
    }

    printf ("Imagem salva com nome \"%s\".\n", nome_imagem);
    fclose (arquivo_imagem);
}

void compress (FILE *arquivo_input)
{
    FILE *imagem, *comprimido;
    int X, Y;
    int red, green, blue;
    int red_atual, green_atual, blue_atual;
    int counter = 0;
    int qualidade;
    char formato[3];
    char nome_imagem[30];

    fscanf (arquivo_input, " %s", nome_imagem);
    imagem = fopen (nome_imagem, "r");
    checar_fopen (imagem);
    comprimido = fopen ("comprimido.txt", "w");
    checar_fopen (comprimido);

    fscanf (imagem,"%s\n%d %d\n%d\n", formato, &Y, &X, &qualidade);
    checar_formato (formato);
    checar_qualidade (qualidade);
    fprintf (comprimido, "P3 %d %d 255", Y, X);

    fscanf (imagem, "%d %d %d", &red, &green, &blue);
    red_atual = red;
    green_atual = green;
    blue_atual = blue;

    while (1)
    {
        if (red != red_atual
            || green != green_atual
            || blue != blue_atual)
        {
            fprintf (comprimido, ", %d %d %d %d",
                    counter, red_atual, green_atual, blue_atual);
            red_atual = red;
            green_atual = green;
            blue_atual = blue;
            counter = 1;
        }
        else
        {
            counter++;
        }

        if (fscanf (imagem, "%d %d %d", &red, &green, &blue) == EOF)
        {
            fprintf (comprimido, ", %d %d %d %d",
                   counter, red_atual, green_atual, blue_atual);
            break;
        }
    }
}

void decompress(FILE *arquivo_input)
{
    FILE *comprimido, *descomprimido;
    int X, Y;
    int red, green, blue;
    int qualidade;
    int counter = 0;
    char nome_comprimido[30], nome_descomprimido[30];
    char formato[3];

    fscanf (arquivo_input, " %s", nome_comprimido);
    comprimido = fopen (nome_comprimido, "r");
    checar_fopen (comprimido);

    fscanf (arquivo_input, " %s", nome_descomprimido);
    descomprimido = fopen (nome_descomprimido, "w");
    checar_fopen (descomprimido);

    fscanf (comprimido, "%s %d %d %d", formato, &Y, &X, &qualidade);
    checar_formato (formato);
    checar_qualidade (qualidade);

    fprintf(descomprimido, "P3\n%d %d\n255\n", Y, X);

    while(fscanf(comprimido, ", %d %d %d %d", &counter, &red, &green, &blue) != EOF)
    {
        for(int i = 0; i < counter; i++)
        {
            fprintf(descomprimido, "%d %d %d\n", red, green, blue);
        }
    }
}

void color (FILE *arquivo)
{
    fscanf (arquivo, " %hhu %hhu %hhu\n",
            &pincel.RGB.red,
            &pincel.RGB.green,
            &pincel.RGB.blue);
    checar_cor (pincel.RGB.red, pincel.RGB.green, pincel.RGB.blue, "color");
}

void paint_pixels (int eixo_x, int eixo_y, pixel ***ptr_pixels)
{
    (*ptr_pixels)[eixo_x][eixo_y].RGB.red = pincel.RGB.red;
    (*ptr_pixels)[eixo_x][eixo_y].RGB.green = pincel.RGB.green;
    (*ptr_pixels)[eixo_x][eixo_y].RGB.blue = pincel.RGB.blue;
}

void color_picker (int X, int Y, pixel ***ptr_pixels)
{
    pincel_fill.RGB.red = (*ptr_pixels)[X][Y].RGB.red;
    pincel_fill.RGB.green = (*ptr_pixels)[X][Y].RGB.green;
    pincel_fill.RGB.blue = (*ptr_pixels)[X][Y].RGB.blue;
}

void clear (FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    int red, green, blue;

    fscanf (arquivo, " %d %d %d\n", &red, &green, &blue);
    checar_cor (red, green, blue, "clear");

    for (int i = 0; i < ptr_desenho->X; i++)
    {
        for (int j = 0; j < ptr_desenho->Y; j++)
        {
            (*ptr_pixels)[i][j].RGB.red = red;
            (*ptr_pixels)[i][j].RGB.green = green;
            (*ptr_pixels)[i][j].RGB.blue = blue;
        }
    }

    printf ("Tudo limpo na cor %d %d %d.\n", red, green, blue);
}

void fill (FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    unsigned short X, Y;

    fscanf (arquivo, " %hu %hu\n", &Y, &X);
    checar_coordenadas (X, Y, ptr_desenho, "fill");

    color_picker (X, Y, ptr_pixels);

    fill_spread_right (X, Y, ptr_desenho->X, ptr_desenho->Y, ptr_pixels);
    fill_spread_left (X, Y, ptr_desenho->X, ptr_desenho->Y, ptr_pixels);
}

void fill_spread_right (
    unsigned short X,
    unsigned short Y,
    unsigned short imagem_X,
    unsigned short imagem_Y,
    pixel ***ptr_pixels)
{
    paint_pixels (X, Y, ptr_pixels);

    if (Y+1 < imagem_Y && checar_proxpixel (X, Y+1, ptr_pixels))
    {
        fill_spread_right (X, Y+1, imagem_X, imagem_Y, ptr_pixels);
    }

    if (X+1 < imagem_X && checar_proxpixel (X+1, Y, ptr_pixels))
    {
        fill_spread_right (X+1, Y, imagem_X, imagem_Y, ptr_pixels);
    }

    if (X-1 >= 0 && checar_proxpixel (X-1, Y, ptr_pixels))
    {
        fill_spread_right (X-1, Y, imagem_X, imagem_Y, ptr_pixels);
    }
}

void fill_spread_left (
    unsigned short X,
    unsigned short Y,
    unsigned short imagem_X,
    unsigned short imagem_Y,
    pixel ***ptr_pixels)
{
    paint_pixels (X, Y, ptr_pixels);

    if (Y-1 >= 0 && checar_proxpixel (X, Y-1, ptr_pixels))
    {
        fill_spread_left (X, Y-1, imagem_X, imagem_Y, ptr_pixels);
    }

    if (X+1 < imagem_X && checar_proxpixel (X+1, Y, ptr_pixels))
    {
        fill_spread_left (X+1, Y, imagem_X, imagem_Y, ptr_pixels);
    }

    if (X-1 >= 0 && checar_proxpixel (X-1, Y, ptr_pixels))
    {
        fill_spread_left (X-1, Y, imagem_X, imagem_Y, ptr_pixels);
    }

    if (Y+1 < imagem_Y && checar_proxpixel (X, Y+1, ptr_pixels))
    {
        fill_spread_right (X, Y+1, imagem_X, imagem_Y, ptr_pixels);
    }
}

void line (
    int x_final,
    int y_final,
    int x_inicial,
    int y_inicial,
    pixel ***ptr_pixels)
{
    float inclinacao;

    inclinacao = (float) (y_final - y_inicial)/ (x_final - x_inicial);

    linha.dx = abs (x_final - x_inicial);
    linha.dy = abs (y_final - y_inicial);
    linha.decisao = 2*linha.dy - linha.dx;
    //printf("dx %d dy %d\n", linha.dx, linha.dy);
    if (linha.dy == 0 || linha.dx == 0) inclinacao = 1;
    //printf("inc %f\n", inclinacao);
    if (inclinacao >= 1 || inclinacao <= -1)
    {
        //printf ("dx\n");
        line_dx (x_final, y_final, x_inicial, y_inicial, ptr_pixels);
    }
    else if (inclinacao == 1 && (x_inicial == x_final || y_inicial == y_final))
    {
        line_straight (x_final, y_final, x_inicial, y_inicial, ptr_pixels);
    }
    else if ((inclinacao < 1 && inclinacao > 0)
            || (inclinacao < 0 && inclinacao > -1))
    {
        //printf("dy\n");
        line_dy (x_final, y_final, x_inicial, y_inicial, ptr_pixels);
    }

}

void line_straight (
    int x_final,
    int y_final,
    int x,
    int y,
    pixel ***ptr_pixels)
{
    paint_pixels (x, y, ptr_pixels);
    //printf("de %d %d para %d %d\n", x, y, x_final, y_final);
    if (x != x_final || y != y_final)
    {
        if (x_final > x)
        {
            line_straight (x_final, y_final, x+1, y, ptr_pixels);
        }
        else if (y_final > y)
        {
            line_straight (x_final, y_final, x, y+1, ptr_pixels);
        }
        else if (x_final < x)
        {
            line_straight (x_final, y_final, x-1, y, ptr_pixels);
        }
        else if (y_final < y)
        {
            line_straight (x_final, y_final, x, y-1, ptr_pixels);
        }
    }
}

void line_dx (
    int x_final,
    int y_final,
    int x,
    int y,
    pixel ***ptr_pixels)
{
    paint_pixels (x, y, ptr_pixels);
    //printf ("de %d %d para %d %d\n", x, y, x_final, y_final);
    if (x != x_final || y_final != y)
    {
        //printf ("dec %d\n", linha.decisao);
        if (x_final == x || y_final == y)
        {
            //printf ("oi");
            line_straight (x_final, y_final, x, y, ptr_pixels);
        }
        else if (linha.decisao < 0 && y_final > y)
        {
            linha.decisao += 2 * linha.dx;
            line_dx (x_final, y_final, x, y+1, ptr_pixels);
        }
        else if (linha.decisao < 0 && y_final < y)
        {
            linha.decisao += 2 * linha.dx;
            line_dx (x_final, y_final, x, y-1, ptr_pixels);
        }
        else if (linha.decisao >= 0 && x_final > x && y_final > y)
        {
            linha.decisao += 2*linha.dx - 2*linha.dy;
            line_dx (x_final, y_final, x+1, y+1, ptr_pixels);
        }
        else if (linha.decisao >= 0 && x_final < x && y_final < y)
        {
            linha.decisao += 2*linha.dx - 2*linha.dy;
            line_dx (x_final, y_final, x-1, y-1, ptr_pixels);
        }
        else if (linha.decisao >= 0 && x_final < x && y_final > y)
        {
            linha.decisao += 2*linha.dx - 2*linha.dy;
            line_dx (x_final, y_final, x-1, y+1, ptr_pixels);
        }
        else if (linha.decisao >= 0 && x_final > x && y_final < y)
        {
            linha.decisao += 2*linha.dx - 2*linha.dy;
            line_dx (x_final, y_final, x+1, y-1, ptr_pixels);
        }
    }
}

void line_dy (
    int x_final,
    int y_final,
    int x,
    int y,
    pixel ***ptr_pixels)
{
    paint_pixels (x, y, ptr_pixels);
    //printf ("de %d %d para %d %d\n", x, y, x_final, y_final);
    //printf ("decisao %d\n", linha.decisao);
    if (x != x_final || y_final != y)
    {
        if (x_final == x || y_final == y)
        {
            printf ("oi");
            line_straight (x_final, y_final, x, y, ptr_pixels);
        }
        else if (linha.decisao < 0 && x_final > x)
        {
            linha.decisao += 2 * linha.dy;
            line_dy (x_final, y_final, x+1, y, ptr_pixels);
        }
        else if (linha.decisao < 0 && x_final < x)
        {
            linha.decisao += 2 * linha.dy;
            line_dy (x_final, y_final, x-1, y, ptr_pixels);
        }
        else if (linha.decisao >= 0 && x_final > x && y_final > y)
        {
            linha.decisao += 2*linha.dy - 2*linha.dx;
            line_dy (x_final, y_final, x+1, y+1, ptr_pixels);
        }
        else if (linha.decisao >= 0 && x_final < x && y_final < y)
        {
            linha.decisao += 2*linha.dy - 2*linha.dx;
            line_dy (x_final, y_final, x-1, y-1, ptr_pixels);
        }
        else if (linha.decisao >= 0 && x_final < x && y_final > y)
        {
            linha.decisao += 2*linha.dy - 2*linha.dx;
            line_dy (x_final, y_final, x-1, y+1, ptr_pixels);
        }
        else if (linha.decisao >= 0 && x_final > x && y_final < y)
        {
            linha.decisao += 2*linha.dy - 2*linha.dx;
            line_dy (x_final, y_final, x+1, y-1, ptr_pixels);
        }
    }
}

void rect (FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    int X, Y;
    int largura, altura;

    fscanf (arquivo, " %d %d %d %d\n", &Y, &X, &largura, &altura);
    checar_coordenadas (X, Y, ptr_desenho, "rect");
    checar_medidas (largura, altura, X, Y, ptr_desenho);

    if (X + altura < ptr_desenho->X && Y + largura < ptr_desenho->Y)
    {
        line_straight (X, Y + largura, X, Y, ptr_pixels);
        line_straight (X + altura, Y + largura, X, Y + largura, ptr_pixels);
        line_straight (X + altura, Y, X + altura, Y + largura, ptr_pixels);
        line_straight (X, Y, X + altura, Y, ptr_pixels);
    }
    else if (X + altura > ptr_desenho->X && Y + largura < ptr_desenho->Y)
    {
        line_straight (X, Y + largura, X, Y, ptr_pixels);
        line_straight (X - altura, Y + largura, X, Y + largura, ptr_pixels);
        line_straight (X - altura, Y, X - altura, Y + largura, ptr_pixels);
        line_straight (X, Y, X - altura, Y, ptr_pixels);
    }
    else if (X + altura > ptr_desenho->X
            && Y + largura > ptr_desenho->Y
            && X - altura >= 0
            && Y - largura >= 0)
    {
        line_straight (X, Y - largura, X, Y, ptr_pixels);
        line_straight (X - altura, Y - largura, X, Y - largura, ptr_pixels);
        line_straight (X - altura, Y, X - altura, Y - largura, ptr_pixels);
        line_straight (X, Y, X - altura, Y, ptr_pixels);
    }
    else if (X + altura < ptr_desenho->X && Y + largura > ptr_desenho->Y)
    {
        line_straight (X, Y - largura, X, Y, ptr_pixels);
        line_straight (X + altura, Y - largura, X, Y - largura, ptr_pixels);
        line_straight (X + altura, Y, X + altura, Y - largura, ptr_pixels);
        line_straight (X, Y, X + altura, Y, ptr_pixels);
    }
    else
    {
        printf ("Retângulo saindo do desenho.\n");
    }

    printf ("Retângulo %d %d Largura %d Altura %d.\n", X, Y, largura, altura);
}

void polygon (
    FILE *arquivo,
    imagem *ptr_desenho,
    pixel ***ptr_pixels,
    poligonal **ptr_poligono)
{
    fscanf (arquivo, " %d", &(*ptr_poligono)->pontos);
    checar_pontos (ptr_poligono);

    *ptr_poligono = (poligonal*) realloc (
                                    *ptr_poligono,
                                    ((*ptr_poligono)->pontos+1)
                                    * sizeof (poligonal));
    checar_mempoligono (*ptr_poligono);

    for (int i = 1; i < (*ptr_poligono)->pontos+1; i++)
    {
        fscanf (arquivo, "%d %d", &(*ptr_poligono)[i].Y, &(*ptr_poligono)[i].X);
        checar_coordenadas (
                        (*ptr_poligono)[i].X,
                        (*ptr_poligono)[i].Y,
                        ptr_desenho, "polygon");
                        //printf("%d %d\n", (*ptr_poligono)[i].Y, (*ptr_poligono)[i].X);
        if (i == (*ptr_poligono)->pontos)
        {
            (*ptr_poligono)[0].Y = (*ptr_poligono)[i].Y;
            (*ptr_poligono)[0].X = (*ptr_poligono)[i].X;
        }
    }

    for (int i = (*ptr_poligono)->pontos; i > 0; i--)
    {
        //printf("Final %d %d Inicial %d %d\n",(*ptr_poligono)[i-1].X, (*ptr_poligono)[i-1].Y, (*ptr_poligono)[i].X, (*ptr_poligono)[i].Y);
        line ((*ptr_poligono)[i-1].X,
            (*ptr_poligono)[i-1].Y,
            (*ptr_poligono)[i].X,
            (*ptr_poligono)[i].Y,
            ptr_pixels);

        *ptr_poligono = (poligonal*) realloc (
                                        *ptr_poligono,
                                        i * sizeof (poligonal));
        checar_mempoligono (*ptr_poligono);
    }
}

void circle (FILE *arquivo, imagem *ptr_desenho, pixel ***ptr_pixels)
{
    fscanf (arquivo, " %d %d %d\n", &circulo.Y, &circulo.X, &circulo.tamanho);
    checar_coordenadas (circulo.X, circulo.Y, ptr_desenho, "circle");
    checar_raio (ptr_desenho);

    circle_line (0, circulo.tamanho, 3 - (2 * circulo.tamanho), ptr_pixels);
}

// Algoritmo de Bresenham copiado.
void circle_line (int x, int y, int decisao, pixel ***ptr_pixels)
{
    if (y >= x)
    {
        paint_pixels (circulo.X+x, circulo.Y+y, ptr_pixels);
        paint_pixels (circulo.X+x, circulo.Y-y, ptr_pixels);
        paint_pixels (circulo.X-x, circulo.Y+y, ptr_pixels);
        paint_pixels (circulo.X-x, circulo.Y-y, ptr_pixels);
        paint_pixels (circulo.X+y, circulo.Y+x, ptr_pixels);
        paint_pixels (circulo.X+y, circulo.Y-x, ptr_pixels);
        paint_pixels (circulo.X-y, circulo.Y+x, ptr_pixels);
        paint_pixels (circulo.X-y, circulo.Y-x, ptr_pixels);

        if (decisao > 0)
        {
            decisao = decisao + 4 * (x - y) + 10;
            y--;
        }
        else
        {
            decisao = decisao + 4 * x + 6;
        }
        x++;
        circle_line (x, y, decisao, ptr_pixels);
    }
}
