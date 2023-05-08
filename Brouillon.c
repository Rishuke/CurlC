#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <gtk/gtk.h>

const gchar* texte_saisi = NULL;

void on_button_clicked(GtkWidget* widget, gpointer data) {
    GtkWidget* entry = (GtkWidget*)data;
    texte_saisi = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Texte saisi : %s\n", texte_saisi);
}

int main(int argc, char *argv[]) {
    // Définition de la locale pour l'affichage
    setlocale(LC_ALL, "en_US.UTF-8");

    // Initialisation de GTK
    gtk_init(&argc, &argv);

    // Création de la fenêtre et des widgets
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *grid = gtk_grid_new();
    GtkWidget *entry = gtk_entry_new();
    GtkWidget *button = gtk_button_new_with_label("Valider");

    // Ajout des widgets à la grille et connexion du signal clicked du bouton
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry);

    // Affichage de la fenêtre
    gtk_widget_show_all(window);

    // Boucle principale de GTK
    gtk_main();

    // Affichage du texte saisi dans la console
    if (texte_saisi != NULL) {
        printf("Le texte saisi est : %s\n", texte_saisi);
    }

    return EXIT_SUCCESS;
}

