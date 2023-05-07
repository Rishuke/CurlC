#include <gtk/gtk.h>

void on_button_clicked(GtkButton *button, gpointer data)
{
    GtkWidget *window2;
    
    // Création de la deuxième fenêtre
    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window2), "Deuxième fenêtre");
    gtk_window_set_default_size(GTK_WINDOW(window2), 400, 300);
    
    // Affichage de la deuxième fenêtre
    gtk_widget_show_all(window2);
}

int main(int argc, char *argv[])
{
    GtkWidget *window1;
    GtkWidget *button;
    GtkWidget *vbox;
    
    // Initialisation de GTK+
    gtk_init(&argc, &argv);
    
    // Création de la première fenêtre
    window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window1), "Première fenêtre");
    gtk_window_set_default_size(GTK_WINDOW(window1), 400, 300);
    g_signal_connect(window1, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Création d'une boîte verticale pour contenir le bouton
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window1), vbox);
    
    // Création du bouton "Envoyer"
    button = gtk_button_new_with_label("Envoyer");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_container_add(GTK_CONTAINER(vbox), button);
    
    // Affichage de la première fenêtre
    gtk_widget_show_all(window1);
    
    // Lancement de la boucle principale de GTK+
    gtk_main();
    
    return 0;
}

