#include <gtk/gtk.h>

GtkWidget	*window;
GtkWidget 	*window_save;
GtkWidget 	*window_about;
GtkWidget 	*window_open;
GtkWidget	*fixed1;
GtkWidget 	*fixed2;
GtkWidget 	*fixed3;
GtkWidget 	*fixed4;
GtkWidget	*button_clean;
GtkWidget	*button_rect;
GtkWidget	*button_circle;
GtkWidget	*button_polygon;
GtkWidget	*button_fill;
GtkWidget	*basic_colors;
GtkWidget 	*popover;
GtkWidget 	*color_button;
GtkWidget	*button_about;
GtkWidget	*button_resolution;
GtkWidget 	*button_save;
GtkWidget 	*button_open;
GtkWidget 	*button_new;
GtkWidget 	*save_name;
GtkBuilder	*builder;

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
}

void on_button_save_activate()
{
	gtk_widget_show(window_save);
}

void save_name_activate_cb()
{
	printf("activate\n");
	gtk_widget_hide(window_save);
}

void on_file_open_activate()
{
	printf("activate\n");
	gtk_widget_hide(window_open);
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

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv); // init Gtk

	builder = gtk_builder_new_from_file ("projeto.glade");

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	window_save = GTK_WIDGET(gtk_builder_get_object(builder, "window_save"));
	window_about = GTK_WIDGET(gtk_builder_get_object(builder, "window_about"));
	window_open = GTK_WIDGET(gtk_builder_get_object(builder, "window_open"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	// Iharob Al Asimi - Stack Overflow
	g_signal_connect(G_OBJECT(window_save), "delete-event", G_CALLBACK(on_widget_deleted), NULL);
	g_signal_connect(G_OBJECT(window_about), "delete-event", G_CALLBACK(on_widget_deleted), NULL);
	g_signal_connect(G_OBJECT(window_open), "delete-event", G_CALLBACK(on_widget_deleted), NULL);

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

    gtk_builder_connect_signals(builder, NULL);

	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	fixed2 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed2"));
	fixed3 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed3"));
	fixed4 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed4"));
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
	save_name = GTK_WIDGET(gtk_builder_get_object(builder, "save_name"));

	gtk_widget_show(window);

	gtk_main();

	return EXIT_SUCCESS;
	}
