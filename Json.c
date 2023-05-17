#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

GtkWidget *window1, *window2;

// Fonction qui permet de fermer une fenêtre GTK
void close_window(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(GTK_WIDGET(data));
}

// Fonction de rappel qui se déclenche lorsque le bouton est cliqué
void on_button_clicked(GtkButton *button, gpointer user_data) {
    if (g_strcmp0(gtk_button_get_label(button), "Recipes") == 0) {
        // Code à exécuter pour le bouton Recipes
        g_print("Bouton Recipes a été cliqué.\n");
        // Ouverture de la fenêtre 2
        gtk_widget_show_all(window2);
    } else if (g_strcmp0(gtk_button_get_label(button), "Ingredients") == 0) {
        // Code à exécuter pour le bouton Ingredients
        g_print("Bouton Ingredients a été cliqué.\n");
        // Ouverture de la fenêtre 2
        gtk_widget_show_all(window2);
    }
}

int main(int argc, char *argv[]) {
    GtkWidget *button1, *button2, *vbox1;

    gtk_init(&argc, &argv);

    // Création de la fenêtre 1
    window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window1), "Accueil");
    gtk_window_set_default_size(GTK_WINDOW(window1), 400, 400);
    g_signal_connect(window1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Création d'une boîte verticale pour contenir les boutons
    vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window1), vbox1);

    // Création des boutons
    button1 = gtk_button_new_with_label("Recipes");
    button2 = gtk_button_new_with_label("Ingredients");

    // Connexion des signaux "clicked" des boutons à la fonction de rappel
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button_clicked), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), NULL);

    // Ajout des boutons à la boîte verticale
    gtk_box_pack_start(GTK_BOX(vbox1), button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox1), button2, TRUE, TRUE, 0);

    // Création de la fenêtre 2
    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window2), "Fenêtre 2");
    gtk_window_set_default_size(GTK_WINDOW(window2), 400, 400);
    g_signal_connect(window2, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Affichage des fenêtres
    gtk_widget_show_all(window1);
    gtk_widget_hide(window2); // Masquer la fenêtre 2 initialement

    gtk_main();

    return 0;
}

