#include "frontend.h"

GtkWidget *window;
GtkWidget *window_save;
GtkWidget *window_about;
GtkWidget *window_open;
GtkWidget *window_fixed;
GtkWidget *window_new;
GtkWidget *fixed2;
GtkWidget *fixed3;
GtkWidget *fixed4;
GtkWidget *button_clean;
GtkWidget *button_rect;
GtkWidget *button_circle;
GtkWidget *button_polygon;
GtkWidget *button_fill;
GtkWidget *basic_colors;
GtkWidget *popover;
GtkWidget *file_open;
GtkWidget *color_button;
GtkWidget *button_about;
GtkWidget *button_resolution;
GtkWidget *button_save;
GtkWidget *button_open;
GtkWidget *button_new;
GtkWidget *button_undo;
GtkWidget *button_redo;
GtkWidget *button_create;
GtkWidget *save_name;
GtkWidget *image1;
GtkBuilder *builder;

void on_button_clean_clicked()
{
	printf("batata\n");
}

void color_button_rgb(GtkColorButton *button)
{
	GdkRGBA *ptr_color, color;
	int red, green, blue;
	char cor[20];
	ptr_color = &color;

	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(button), ptr_color);
	sprintf(cor, "%s\n", gdk_rgba_to_string(ptr_color));
	sscanf(cor, "%d,%d,%d", &red, &green, &blue);
	printf("%d %d %d\n", red, green, blue);
}

void on_color_button_color_set()
{
	printf("vai vai\n");
	color_button_rgb(GTK_COLOR_BUTTON(color_button));
}

void get_file_name(GtkFileChooserButton *button)
{
	char path[100];
	char file_name[100];
	sprintf(path, "%s", gtk_file_chooser_get_current_name(GTK_FILE_CHOOSER(button)));
	sscanf(path, "%s", file_name);
	printf("%s\n", file_name);
}

void on_button_about_activate()
{
	gtk_widget_show(window_about);
}

void on_button_resolution_activate()
{

}

void on_button_new_activate()
{
	printf("novinho\n");
    gtk_widget_show(window_new);
}

void on_button_create_activate()
{
	gtk_widget_hide(window_new);
}

void on_button_save_activate()
{
	gtk_widget_show(window_save);
}

void on_button_undo_activate()
{
		FILE *arquivo;
		int linha = 0;
		char **historico;
		int tamanho_linha;

		historico = (char**) malloc(1*sizeof(char*));
		historico[0] = (char*) malloc(1*sizeof(char));
		arquivo = fopen("input.txt", "r+");
		while(1)
		{
			fscanf(arquivo, "%*[^\n]s");
			if(fgetc(arquivo) == EOF)
			{
				break;
			}
			linha++;
		}
		historico = (char**) realloc(historico, linha*sizeof(char*));
		fseek(arquivo, 0, SEEK_SET);
		printf("%d\n", linha);
		for(int i = 0; i < linha-1; i++)
		{
			tamanho_linha = 0;
			while(fgetc(arquivo) != '\n')
			{
				tamanho_linha++;
			}
			printf("%d\n", tamanho_linha);
			printf("%d\n", i);
			historico[i] = (char*) realloc(historico[i], tamanho_linha*sizeof(char));
		}
		fseek(arquivo, 0, SEEK_SET);
		for(int i = 0; i < linha-1; i++)
		{
			fscanf(arquivo, "%[^\n]s", historico[i]);
		}
		for(int i = 0; i < linha-1; i++)
		{
			printf("%s\n", historico[i]);
		}
		fclose(arquivo);
}

void on_button_redo_activate()
{

}

void save_name_activate_cb()
{
	char filename[] = "issoai.ppm";
	image1 = gtk_image_new_from_file (filename);
	printf("activate\n");
	gtk_widget_hide(window_save);
	if (image1)
		gtk_container_remove (GTK_CONTAINER (window_fixed), image1);
	gtk_container_add (GTK_CONTAINER (window_fixed), image1);
	gtk_widget_show(image1);
	gtk_fixed_move (GTK_FIXED (window_fixed), image1, 59, 93);
}

void on_file_open_activate()
{
	printf("activate\n");
	gtk_widget_hide(window_open);

}

void get_open_file(gpointer data)
{
    char *nome_imagem;
    FILE *imagem;

    data = (picture) data;
    nome_imagem = (char*) malloc(30 * sizeof(char));

    gtk_editable_delete_text (GTK_EDITABLE(file_open), 0, -1);
    strcpy(nome_imagem, gtk_entry_get_text(GTK_ENTRY(file_open)));

    imagem = fopen(nome_imagem, "r");
    open(imagem, data.ptr_desenho, data.ptr_pixels);

    free(nome_imagem);
}

void basic_colors_rgb(GtkEntry *entry)
{
	char cor[25];
	int red, green, blue;
	sprintf(cor, "%s", gtk_entry_get_text(entry));
	printf("%s\n", cor);
	sscanf(cor, "(%d, %d, %d)", &red, &green, &blue);
	printf("%d %d %d\n", red, green, blue);
}

void on_basic_colors_changed()
{
	printf("colorido ido ido\n");
	basic_colors_rgb(GTK_ENTRY(basic_colors));
}

void on_button_open_activate()
{
	gtk_widget_show(window_open);
}

// Iharob Al Asimi - Stack Overflow (how-do-i-intercept-a-gtk-window-close-button-click)
gboolean on_widget_deleted(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    gtk_widget_hide(widget);
    return TRUE;
}
