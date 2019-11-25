#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "primitivas.h"
#include "checagens.h"
#include "tipos.h"
#include "frontend.c"

int main(int argc, char *argv[])
{
    pixel **pixels;
    pixel ***ptr_pixels;
    FILE *arquivo_input;
    char primitiva[8];
    imagem desenho;
    imagem *ptr_desenho = &desenho;
    poligonal *poligono;
    poligonal **ptr_poligono;

    pixels = (pixel**) malloc(1*sizeof(pixel*));
    checar_mempixel(pixels, -1);
    pixels[0] = (pixel*) malloc(1*sizeof(pixel));
    checar_mempixel(pixels, 0);

    ptr_pixels = &pixels;

    poligono = (poligonal*) malloc(3 * sizeof(poligono));
    checar_mempoligono(poligono);

    ptr_poligono = &poligono;

    desenho.X = 0;

    picture.ptr_desenho = ptr_desenho;
    picture.ptr_pixels = ptr_pixels;

    arquivo_input = fopen("input.txt", "w+");
    checar_fopen(arquivo_input);

    gtk_init(&argc, &argv); // init Gtk

	builder = gtk_builder_new_from_file ("projeto.glade");

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	window_save = GTK_WIDGET(gtk_builder_get_object(builder, "window_save"));
	window_about = GTK_WIDGET(gtk_builder_get_object(builder, "window_about"));
	window_open = GTK_WIDGET(gtk_builder_get_object(builder, "window_open"));
    window_new = GTK_WIDGET(gtk_builder_get_object(builder, "window_new"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	// Iharob Al Asimi - Stack Overflow
	g_signal_connect(G_OBJECT(window_save), "delete-event", G_CALLBACK(on_widget_deleted), NULL);
	g_signal_connect(G_OBJECT(window_about), "delete-event", G_CALLBACK(on_widget_deleted), NULL);
	g_signal_connect(G_OBJECT(window_open), "delete-event", G_CALLBACK(on_widget_deleted), NULL);
    g_signal_connect(G_OBJECT(file_open), "activate", G_CALLBACK(get_open_file), &picture);

 	gtk_builder_add_callback_symbol(builder, "on_button_clean_clicked", on_button_clean_clicked);
	gtk_builder_add_callback_symbol(builder, "on_button_about_activate", on_button_about_activate);
	gtk_builder_add_callback_symbol(builder, "on_button_resolution_activate", on_button_resolution_activate);
	gtk_builder_add_callback_symbol(builder, "save_name_activate_cb", save_name_activate_cb);
	gtk_builder_add_callback_symbol(builder, "on_button_save_activate", on_button_save_activate);
	gtk_builder_add_callback_symbol(builder, "on_basic_colors_changed", on_basic_colors_changed);
	gtk_builder_add_callback_symbol(builder, "on_color_button_color_set", on_color_button_color_set);
	gtk_builder_add_callback_symbol(builder, "on_button_open_activate", on_button_open_activate);
	gtk_builder_add_callback_symbol(builder, "on_file_open_activate", on_file_open_activate);
	gtk_builder_add_callback_symbol(builder, "on_button_new_activate", on_button_new_activate);
	gtk_builder_add_callback_symbol(builder, "on_button_undo_activate", on_button_undo_activate);
	gtk_builder_add_callback_symbol(builder, "on_button_redo_activate", on_button_redo_activate);
    gtk_builder_add_callback_symbol(builder, "on_button_create_activate", on_button_create_activate);

    gtk_builder_connect_signals(builder, NULL);

	window_fixed = GTK_WIDGET(gtk_builder_get_object(builder, "window_fixed"));
	fixed2 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed2"));
	fixed3 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed3"));
	fixed4 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed4"));
    file_open = GTK_WIDGET(gtk_builder_get_object(builder, "file_open"));
	button_clean = GTK_WIDGET(gtk_builder_get_object(builder, "button_clean"));
	button_rect = GTK_WIDGET(gtk_builder_get_object(builder, "button_rect"));
	button_circle = GTK_WIDGET(gtk_builder_get_object(builder, "button_circle"));
	button_polygon = GTK_WIDGET(gtk_builder_get_object(builder, "button_polygon"));
	color_button = GTK_WIDGET(gtk_builder_get_object(builder, "color_button"));
	button_fill = GTK_WIDGET(gtk_builder_get_object(builder, "button_fill"));
	popover = GTK_WIDGET(gtk_builder_get_object(builder, "clear_color"));
	basic_colors = GTK_WIDGET(gtk_builder_get_object(builder, "basic_colors"));
	button_about = GTK_WIDGET(gtk_builder_get_object(builder, "button_about"));
	button_resolution = GTK_WIDGET(gtk_builder_get_object(builder, "button_resolution"));
	button_save = GTK_WIDGET(gtk_builder_get_object(builder, "button_save"));
	button_open = GTK_WIDGET(gtk_builder_get_object(builder, "button_open"));
	button_new = GTK_WIDGET(gtk_builder_get_object(builder, "button_new"));
	button_undo = GTK_WIDGET(gtk_builder_get_object(builder, "button_undo"));
	button_redo = GTK_WIDGET(gtk_builder_get_object(builder, "button_redo"));
    button_create = GTK_WIDGET(gtk_builder_get_object(builder, "button_create"));
	save_name = GTK_WIDGET(gtk_builder_get_object(builder, "save_name"));
	image1 = GTK_WIDGET(gtk_builder_get_object(builder, "image1"));

	gtk_widget_show(window);

	image1 = NULL;

	gtk_main();

    while(fscanf(arquivo_input,"%s", primitiva) != EOF)
    {
        switch(checar_primitiva(primitiva))
        {
            case primitive_image:
                image(arquivo_input, ptr_desenho, ptr_pixels);
                break;
            case primitive_color:
                color(arquivo_input);
                printf("Cor %d %d %d.\n", pincel.RGB.red, pincel.RGB.green,
                        pincel.RGB.blue);
                break;
            case primitive_clear:
                clear(arquivo_input, ptr_desenho, ptr_pixels);
                break;
            case primitive_rect:
                rect(arquivo_input, ptr_desenho, ptr_pixels);
                break;
            case primitive_circle:
                circle(arquivo_input, ptr_desenho, ptr_pixels);
                printf("Circulo %d %d Raio %d.\n", circulo.Y, circulo.X,
                        circulo.tamanho);
                break;
            case primitive_polygon:
                polygon(arquivo_input, ptr_desenho, ptr_pixels, ptr_poligono);
                printf("Poligono com %d pontos.\n", poligono->pontos);
                //free(poligono);
                break;
            case primitive_fill:
                fill(arquivo_input, ptr_desenho, ptr_pixels );
                printf("Fill %d %d %d.\n", pincel.RGB.red, pincel.RGB.green,
                        pincel.RGB.blue);
                break;
            case primitive_save:
                save(arquivo_input, ptr_desenho, ptr_pixels);
                break;
            case primitive_open:
                open(arquivo_input, ptr_desenho, ptr_pixels);
                break;
            case primitive_compress:
                compress(arquivo_input);
                break;
            case primitive_decompress:
                decompress(arquivo_input);
                break;
            default:
                printf("Primitiva inválida.\n");
                exit(1);
        }
    }
    for(int i = 0; i < desenho.X; i++)
    {
        free(pixels[i]);
    }
    free(pixels);
    free(poligono);
    fclose(arquivo_input);

    return EXIT_SUCCESS;
}
