#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
extern void ww_call(const char* TOKEN, char *response, size_t response_size);
extern void ww_dial(const char* host, const char* message, char *response, size_t message_size, size_t response_size);
extern void ww_get_self_ip(const char* message, char* ip, size_t response_size, size_t message_size);
extern void ww_get_json(const char* chat_id, const char* text, const char* TOKEN, const char* message, char* json, size_t response_size, size_t message_size);
guint t_h;
guint t_m;
guint t_s;
GtkWidget *label;
GtkWidget *entry;
GtkWidget *button;
GtkWidget *tgtoken_input;
GtkWidget *chat_id_input;
GtkWidget *grid;
GtkWidget *progressBar;
GtkWidget *refresh_time_hours_spin_button;
GtkWidget *refresh_time_minutes_spin_button;
GtkWidget *refresh_time_seconds_spin_button;
GtkApplication *app;
gboolean re2rn(gpointer user_data) {
    const char* TOKEN = gtk_editable_get_text(GTK_EDITABLE(tgtoken_input));
	const char* CHAT_ID = gtk_editable_get_text(GTK_EDITABLE(chat_id_input));
	char response[8192];
	char ip[8192];
	char json[8192];
	ww_get_self_ip(response, ip, sizeof(ip), sizeof(ip));
	ww_get_json(CHAT_ID, ip, TOKEN, response, json, sizeof(ip), sizeof(ip));
	g_print("[HIT]: %s\n",json);
    return TRUE; // continue looping
}
void on_hour_value_changed(GtkSpinButton* self, gpointer user_data) {
    t_h = gtk_spin_button_get_value_as_int(self);
	g_print("[SETH]: %dh\n", t_h);
}
void on_minute_value_changed(GtkSpinButton* self, gpointer user_data) {
    t_m = gtk_spin_button_get_value_as_int(self);
	g_print("[SETM]: %dh\n", t_m);
}
void on_second_value_changed(GtkSpinButton* self, gpointer user_data) {
    t_s = gtk_spin_button_get_value_as_int(self);
	g_print("[SETS]: %dh\n", t_s);
}
static void submit_form(GtkButton *btn){
	if (t_s == 0 && t_h == 0 && t_m == 0) {
		t_s = 1;
	}
	g_print("Running in %dh%dm%ds, every %dh%dm%ds.\n", t_h,t_m,t_s,t_h,t_m,t_s);
	gtk_widget_set_sensitive(button, FALSE); // disable button
	g_timeout_add((guint)(1000)*(t_s+60*t_m+t_h*3600), re2rn, NULL);
	gtk_label_set_text(GTK_LABEL(label), "Running..."); 
}
static void app_activate (GApplication *app, gpointer *user_data) {
	GtkWidget *window = gtk_application_window_new (GTK_APPLICATION (app));
	gtk_window_set_title (GTK_WINDOW (window), "C2rn GUI");
	gtk_window_set_default_size (GTK_WINDOW (window), 280, 320);
	gtk_window_set_resizable(GTK_WINDOW (window), FALSE);
	GtkAdjustment *adjustment_h = gtk_adjustment_new (0, 0.0, 24, 1.0, 5.0, 0.0);
	GtkAdjustment *adjustment_m = gtk_adjustment_new (0, 0.0, 60, 1.0, 5.0, 0.0);
	GtkAdjustment *adjustment_s = gtk_adjustment_new (1, 0.0, 60, 1.0, 5.0, 0.0);
	GtkWidget *grid = gtk_grid_new();
	button = gtk_button_new_with_label("Submit");
	tgtoken_input = gtk_password_entry_new();
	GtkWidget *tgtoken_input_label = gtk_label_new_with_mnemonic("Telegram bot token: ");
	chat_id_input = gtk_password_entry_new();
	GtkWidget *chat_id_input_label = gtk_label_new_with_mnemonic("User chat ID: ");
	GtkWidget *refresh_time_hours_spin_button = gtk_spin_button_new(adjustment_h, 1.0, 0);
	GtkWidget *refresh_time_minutes_spin_button = gtk_spin_button_new(adjustment_m, 1.0, 0);
	GtkWidget *refresh_time_seconds_spin_button = gtk_spin_button_new(adjustment_s, 1.0, 0);
	GtkWidget *refresh_time_hours_spin_button_label = gtk_label_new_with_mnemonic("Refresh time: ");
	gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(refresh_time_hours_spin_button), TRUE);
	gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(refresh_time_minutes_spin_button), TRUE);
	gtk_spin_button_set_wrap(GTK_SPIN_BUTTON(refresh_time_seconds_spin_button), TRUE);
	gtk_orientable_set_orientation(GTK_ORIENTABLE(refresh_time_hours_spin_button), GTK_ORIENTATION_VERTICAL);
	gtk_orientable_set_orientation(GTK_ORIENTABLE(refresh_time_minutes_spin_button), GTK_ORIENTATION_VERTICAL);
	gtk_orientable_set_orientation(GTK_ORIENTABLE(refresh_time_seconds_spin_button), GTK_ORIENTATION_VERTICAL);

	const char* text = "";
	gtk_editable_set_text(GTK_EDITABLE(tgtoken_input), text);
	// label = gtk_label_new(text);	
	// gtk_grid_attach (GTK_GRID (grid), label, 0,8,1,1);

	g_signal_connect (button, "clicked", G_CALLBACK (submit_form), NULL);

	gtk_password_entry_set_show_peek_icon(GTK_PASSWORD_ENTRY (tgtoken_input), TRUE);
	gtk_password_entry_set_show_peek_icon(GTK_PASSWORD_ENTRY (chat_id_input), TRUE);
	
	gtk_grid_set_column_homogeneous(GTK_GRID (grid), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID (grid), TRUE);
	gtk_grid_attach (GTK_GRID (grid), tgtoken_input_label, 0,0,3,1);
	gtk_grid_attach (GTK_GRID (grid), tgtoken_input, 0,1,3,1);
	gtk_grid_attach (GTK_GRID (grid), chat_id_input_label, 0,2,3,1);
	gtk_grid_attach (GTK_GRID (grid), chat_id_input, 0,3,3,1);
	gtk_grid_attach (GTK_GRID (grid), refresh_time_hours_spin_button_label, 0,4,1,1);
	gtk_grid_attach (GTK_GRID (grid), refresh_time_hours_spin_button, 0,5,1,1);
	gtk_grid_attach (GTK_GRID (grid), refresh_time_minutes_spin_button, 1,5,1,1);
	gtk_grid_attach (GTK_GRID (grid), refresh_time_seconds_spin_button, 2,5,1,1);
	gtk_grid_attach (GTK_GRID (grid), button, 0,6,3,1);

	g_signal_connect (refresh_time_hours_spin_button, "value_changed", G_CALLBACK (on_hour_value_changed), label);
	g_signal_connect (refresh_time_minutes_spin_button, "value_changed", G_CALLBACK (on_minute_value_changed), label);
	g_signal_connect (refresh_time_seconds_spin_button, "value_changed", G_CALLBACK (on_second_value_changed), label);

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
