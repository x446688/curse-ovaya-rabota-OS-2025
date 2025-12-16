#ifndef C2RN_GUI_H
#define C2RN_GUI_H
#include <gtk/gtk.h>
gboolean re2rn(gpointer user_data);
void on_hour_value_changed(
	GtkSpinButton* self, 
	gpointer user_data
);
void on_minute_value_changed(
	GtkSpinButton* self, 
	gpointer user_data
);
void on_seconds_value_changed(
	GtkSpinButton* self, 
	gpointer user_data
);
static void submit_form(
	GtkButton *btn
);
void app_activate(GApplication *app, gpointer *user_data);
#endif