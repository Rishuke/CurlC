#include <gtk/gtk.h>

GtkWidget *window = NULL;

void open_new_window()
{
    if (window != NULL) {
        gtk_widget_destroy(window);
        window = NULL;
    }

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Nouvelle fenêtre");

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Fenêtre principale");

    //g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *button = gtk_button_new_with_label("Ouvrir une nouvelle fenêtre");

    g_signal_connect(button, "clicked", G_CALLBACK(open_new_window), NULL);

    gtk_container_add(GTK_CONTAINER(window), button);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

