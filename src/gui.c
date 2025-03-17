#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    //Initialize GTK
    gtk_init(&argc, &argv);

    //main application window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "RISC-V Simulator GUI");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    // Make sure window exits when users exit the app
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //Display window
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
