#include <gtk/gtk.h>

GtkWidget *window1, *window2, *window3;

void open_window2() {
    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window2), "Window 2");
    gtk_window_set_default_size(GTK_WINDOW(window2), 200, 200);
    gtk_widget_show_all(window2);
}

void open_window3() {
    window3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window3), "Window 3");
    gtk_window_set_default_size(GTK_WINDOW(window3), 200, 200);
    gtk_widget_show_all(window3);
}

void close_window(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(data);
}

int main(int argc, char *argv[]) {
    GtkWidget *button1, *button2, *button3;
    GtkWidget *vbox;

    gtk_init(&argc, &argv);

    window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window1), "Window 1");
    gtk_window_set_default_size(GTK_WINDOW(window1), 200, 200);

    button1 = gtk_button_new_with_label("Open Window 2");
    g_signal_connect(button1, "clicked", G_CALLBACK(open_window2), NULL);

    button2 = gtk_button_new_with_label("Open Window 3");
    g_signal_connect(button2, "clicked", G_CALLBACK(open_window3), NULL);

    button3 = gtk_button_new_with_label("Close Window 1");
    g_signal_connect(button3, "clicked", G_CALLBACK(close_window), window1);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button3, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window1), vbox);

    gtk_widget_show_all(window1);

    gtk_main();

    return 0;
}
