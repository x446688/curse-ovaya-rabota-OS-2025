#include <gtk/gtk.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
GtkWidget* label;
GtkWidget* entry;
GtkWidget* button;
GtkWidget* tgtoken_input;
GtkWidget* chat_id_input;
struct form {
	GtkSpinButton *refresh_time;
	GtkButton *submit_form_button; 
	GtkPasswordEntry *token_input;
	GtkPasswordEntry *chat_id_input;
};
static void submit_form(GtkButton *btn){
	const char* text = gtk_editable_get_text(GTK_EDITABLE(tgtoken_input));
	gtk_label_set_text(GTK_LABEL(label), text);
}
static void app_activate (GApplication *app, gpointer *user_data) {
	GtkWidget *window = gtk_application_window_new (GTK_APPLICATION (app));
	gtk_window_set_title (GTK_WINDOW (window), "C2rn GUI");
	gtk_window_set_default_size (GTK_WINDOW (window), 280, 320);
	gtk_window_set_resizable(window, FALSE);
	GtkAdjustment *adjustment = gtk_adjustment_new (1, 0.0, 24, 1.0, 5.0, 0.0);
	
	GtkWidget *grid = gtk_grid_new ();
	button = gtk_button_new_with_label("Submit");
	tgtoken_input = gtk_password_entry_new();
	GtkWidget *tgtoken_input_label = gtk_label_new_with_mnemonic("Telegram bot token: ");
	chat_id_input = gtk_password_entry_new();
	GtkWidget *chat_id_input_label = gtk_label_new_with_mnemonic("User chat ID: ");
	GtkWidget *refresh_time_hours_spin_button = gtk_spin_button_new(adjustment, 1.0, 0);
	GtkWidget *refresh_time_hours_spin_button_label = gtk_label_new_with_mnemonic("Refresh time: ");

	const char* text = "";
	gtk_editable_set_text(GTK_EDITABLE(tgtoken_input), text);
	label = gtk_label_new(text);	
	gtk_grid_attach (GTK_GRID (grid), label, 0,8,1,1);

	g_signal_connect (button, "clicked", G_CALLBACK (submit_form), NULL);

	gtk_password_entry_set_show_peek_icon(tgtoken_input, TRUE);
	gtk_password_entry_set_show_peek_icon(chat_id_input, TRUE);
	
	gtk_grid_set_column_homogeneous(GTK_GRID (grid), TRUE);
    	gtk_grid_set_row_homogeneous(GTK_GRID (grid), TRUE);
	gtk_grid_attach (GTK_GRID (grid), tgtoken_input_label, 0,0,1,1);
	gtk_grid_attach (GTK_GRID (grid), tgtoken_input, 0,1,1,1);
	gtk_grid_attach (GTK_GRID (grid), chat_id_input_label, 0,2,1,1);
	gtk_grid_attach (GTK_GRID (grid), chat_id_input, 0,3,1,1);
	gtk_grid_attach (GTK_GRID (grid), refresh_time_hours_spin_button_label, 0,4,1,1);
	gtk_grid_attach (GTK_GRID (grid), refresh_time_hours_spin_button, 0,5,1,1);
	gtk_grid_attach (GTK_GRID (grid), button, 0,6,1,1);
	
	gtk_window_set_child (GTK_WINDOW (window), grid);
	gtk_window_present (GTK_WINDOW (window));
}
int main (int argc, char **argv)
{
	GtkApplication *app = gtk_application_new ("com.github", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
	int status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref(app);
	return status;
}
