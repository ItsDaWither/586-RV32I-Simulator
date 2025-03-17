#include <gtk/gtk.h>
//defining global variables
    GtkWidget *entry_mem      = NULL;
    GtkWidget *entry_start    = NULL;
    GtkWidget *entry_stack    = NULL;
    GtkWidget *check_verbose  = NULL;

//Prototype for run function
static void on_run_clicked(GtkButton *button, gpointer user_data);

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
    gtk_grid_attach(GTK_GRID(grid), label_mem, 0, 0, 1, 1);

    //Create a text entry field with a default value
    entry_mem = gtk_entry_new(); 
    gtk_entry_set_text(GTK_ENTRY(entry_mem), "program.mem");
    gtk_grid_attach(GTK_GRID(grid), entry_mem, 1, 0, 1, 1);
    
    // Start Address label
    GtkWidget *label_start = gtk_label_new("Start Address:");
    gtk_grid_attach(GTK_GRID(grid), label_start, 0, 1, 1, 1); // column=0, row=1, width=1, height=1

    // Start Address entry
    entry_start = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_start), "0x0");
    gtk_grid_attach(GTK_GRID(grid), entry_start, 1, 1, 1, 1);// column=1, row=1, width=1, height=1

    // Stack Address
    GtkWidget *label_stack = gtk_label_new("Stack Address:");
    gtk_grid_attach(GTK_GRID(grid), label_stack, 0, 2, 1, 1);

    entry_stack = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry_stack), "65536");
    gtk_grid_attach(GTK_GRID(grid), entry_stack, 1, 2, 1, 1);

    // Verbose Mode check button
    check_verbose = gtk_check_button_new_with_label("Verbose Mode");
    gtk_grid_attach(GTK_GRID(grid), check_verbose, 0, 3, 2, 1);

    //Run button to print values to terminal (for now)
    GtkWidget *run_button = gtk_button_new_with_label("Run");
    gtk_grid_attach(GTK_GRID(grid), run_button, 0, 4, 2, 1);
    g_signal_connect(run_button, "clicked", G_CALLBACK(on_run_clicked), NULL);
    
    //Display window
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
static void on_run_clicked(GtkButton *button, gpointer user_data) {

    extern GtkWidget *entry_mem, *entry_start, *entry_stack, *check_verbose;

    const char *memfile   = gtk_entry_get_text(GTK_ENTRY(entry_mem));
    const char *start_str = gtk_entry_get_text(GTK_ENTRY(entry_start));
    const char *stack_str = gtk_entry_get_text(GTK_ENTRY(entry_stack));
    gboolean verbose      = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_verbose));

    g_print("Memory file: %s\n", memfile);
    g_print("Start addr : %s\n", start_str);
    g_print("Stack addr : %s\n", stack_str);
    g_print("Verbose?   : %d\n", (int)verbose);
}
