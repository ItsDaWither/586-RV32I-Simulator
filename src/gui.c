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
    
    //Create a grid layout and add it to the window
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    //Create a label for “Memory File”
    GtkWidget *label_mem = gtk_label_new("Memory File:");
    gtk_grid_attach(GTK_GRID(grid),label_mem,0, 0, 1, 1);  // column=0, row=0, width=1, height=1

    //Create a text entry field with a default value
    GtkWidget *entry_mem = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_mem), "program.mem");
    gtk_grid_attach(GTK_GRID(grid),entry_mem,1, 0, 1, 1);  // column=1, row=0, width=1, height=1
    
    //Display window
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
