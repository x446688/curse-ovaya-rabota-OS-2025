#include <gtk/gtk.h>
static void app_activate (GApplication *app, gpointer *user_data) {
    GtkWidget *window = gtk_window_new();
    gtk_window_set_title (GTK_WINDOW (window), "test");
    gtk_window_set_default_size (GTK_WINDOW (window), 300, 250);
    gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (app));
    gtk_window_present (GTK_WINDOW (window));
}
int main (int argc, char **argv)
{
    GtkApplication *app = gtk_application_new ("com.metanit", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
    int status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref(app); 
    return status;
}
