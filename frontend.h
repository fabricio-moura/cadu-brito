#ifndef FRONTEND_H
#define FRONTEND_H

#include <gtk/gtk.h>
#include <stdlib.h>

void on_button_clean_clicked();
void color_button_rgb(GtkColorButton *button);
void on_color_button_color_set();
void get_file_name(GtkFileChooserButton *button);
void on_button_about_activate();
void on_button_resolution_activate();
void on_button_new_activate();
void on_button_save_activate();
void on_button_undo_activate();
void on_button_redo_activate();
void save_name_activate_cb();
void on_file_open_activate();
void basic_colors_rgb(GtkEntry *entry);
void on_basic_colors_changed();
void on_button_open_activate();
gboolean on_widget_deleted(GtkWidget *widget, GdkEvent *event, gpointer data);
void on_button_create_activate();

#endif
