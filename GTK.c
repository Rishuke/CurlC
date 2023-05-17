#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdarg.h>
#include <curl/curl.h>

GtkWidget *window1, *window2, *window3, *window4, *window5, *window6, *window7, *window8, *window9;

// Déclaration du pointeur de fichier global
FILE *data;

// Fonction qui permet de fermer une fenetre gtk
void close_window(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(data);
}

// Fonction de rappel qui se declenche lorsque le bouton est cliqué et affichage d'un print dans le Terminal
void on_button_name(GtkButton *button, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Le nom saisi est : %s\n", name);
    if (data == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
    }
    fprintf(data, "%s\n", name);
}

// Fonction de rappel qui se declenche lorsque le bouton est cliqué et affichage d'un print dans le Terminal
void on_button_mail(GtkButton *button, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    const gchar *mail = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Le mail saisi est : %s\n", mail);
    if (data == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
    }
    fprintf(data, "%s\n", mail);
}

void open_window9(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox9;
    window9 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window9), "API6");
    gtk_window_set_default_size(GTK_WINDOW(window9), 400, 400);
    g_signal_connect(window9, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "findByIngredients?apiKey=759b7e6c793c4ec8bff63b4940a952ed", NULL);
    
    g_print("%s\n", concatenated);
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox9 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window9), vbox9);
	
	
	
    
    
    
    gtk_widget_show_all(window9);
    
}

void open_window8(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox8;
    window8 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window8), "API5");
    gtk_window_set_default_size(GTK_WINDOW(window8), 400, 400);
    g_signal_connect(window8, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "substitutes?apiKey=759b7e6c793c4ec8bff63b4940a952ed", NULL);
    
    g_print("%s\n", concatenated);
    
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox8 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window8), vbox8);
	
	
	
    
    
    
    gtk_widget_show_all(window8);
    
}

void open_window7(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox7;
    window7 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window7), "API4");
    gtk_window_set_default_size(GTK_WINDOW(window7), 400, 400);
    g_signal_connect(window7, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "findByNutrients?apiKey=759b7e6c793c4ec8bff63b4940a952ed", NULL);
    
    g_print("%s\n", concatenated);
    
    
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox7 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window7), vbox7);
	
	
	
    
    
    
    gtk_widget_show_all(window7);
    
}

void open_window6(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox6;
    window6 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window6), "API3");
    gtk_window_set_default_size(GTK_WINDOW(window6), 400, 400);
    g_signal_connect(window6, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "autocomplete?apiKey=759b7e6c793c4ec8bff63b4940a952ed", NULL);
    
    g_print("%s\n", concatenated);
    
    
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox6 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window6), vbox6);
	
	
	
    
    
    
    gtk_widget_show_all(window6);
    
}

void open_window5(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox5;
    window5 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window5), "API2");
    gtk_window_set_default_size(GTK_WINDOW(window5), 400, 400);
    g_signal_connect(window5, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "complexSearch?apiKey=759b7e6c793c4ec8bff63b4940a952ed", NULL);
    
    g_print("%s\n", concatenated);
    
    
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window5), vbox5);
	
	
	
    
    
    
    gtk_widget_show_all(window5);
    
}

void open_window4(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox4;
    window4 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window4), "API1");
    gtk_window_set_default_size(GTK_WINDOW(window4), 400, 400);
    g_signal_connect(window4, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    
    
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "search?apiKey=759b7e6c793c4ec8bff63b4940a952ed", NULL);
    
    g_print("%s\n", concatenated);
    
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window4), vbox4);
	
	
	
    
    
    gtk_widget_show_all(window4);
    
}


// Fonction de rappel qui se déclenche lorsque le bouton est cliqué
void on_button_clicked_triple_R(GtkButton *button, gpointer user_data) {
    if (g_strcmp0(gtk_button_get_label(button), "ComplexSearch") == 0) {
        // Code à exécuter pour le bouton Recipes
        g_print("Bouton ComplexSearch a été cliqué.\n");

      

        // Ouverture de la fenêtre 3
        
    } else if (g_strcmp0(gtk_button_get_label(button), "FindByNutrients") == 0) {
        // Code à exécuter pour le bouton Ingredients
        g_print("Bouton FindByNutrients a été cliqué.\n");

       
    }else{
    	g_print("Bouton FindByIngredients a été cliqué.\n");
    }
    	
}

// Fonction de rappel qui se déclenche lorsque le bouton est cliqué
void on_button_clicked_triple_I(GtkButton *button, gpointer user_data) {
    if (g_strcmp0(gtk_button_get_label(button), "Search") == 0) {
        // Code à exécuter pour le bouton Recipes
        g_print("Bouton Search a été cliqué.\n");

      

        // Ouverture de la fenêtre 3
        
    } else if (g_strcmp0(gtk_button_get_label(button), "Autocomplete") == 0) {
        // Code à exécuter pour le bouton Ingredients
        g_print("Bouton Autocomplete a été cliqué.\n");

       
    }else{
    	g_print("Bouton Substitutes a été cliqué.\n");
    }
}


void open_window3(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox3;
    GtkWidget *box3;
    GtkWidget  *button8, *button9, *button10;
    window3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window3), "Ingredients");
    gtk_window_set_default_size(GTK_WINDOW(window3), 400, 400);
    g_signal_connect(window3, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window3), box3);
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "food/ingredients/", NULL);
    
    g_print("%s\n", concatenated);
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window3), vbox3);
	
	
	button8 = gtk_button_new_with_label("Search");
    gtk_box_pack_start(GTK_BOX(box3), button8, TRUE, TRUE, 0);
	
	button9 = gtk_button_new_with_label("Autocomplete");
    gtk_box_pack_start(GTK_BOX(box3), button9, TRUE, TRUE, 0);
    
    button10 = gtk_button_new_with_label("Substitutes");
    gtk_box_pack_start(GTK_BOX(box3), button10, TRUE, TRUE, 0);
    
    g_signal_connect(button8, "clicked", G_CALLBACK(on_button_clicked_triple_I), NULL);
    g_signal_connect(button8, "clicked", G_CALLBACK(open_window4), (gpointer)concatenated);
    g_signal_connect(button9, "clicked", G_CALLBACK(on_button_clicked_triple_I),NULL);
    g_signal_connect(button9, "clicked", G_CALLBACK(open_window6), (gpointer)concatenated);
    g_signal_connect(button10, "clicked", G_CALLBACK(on_button_clicked_triple_I),NULL);
    g_signal_connect(button10, "clicked", G_CALLBACK(open_window8), (gpointer)concatenated);
    
    gtk_widget_show_all(window3);
    
}


void open_window2(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox2;
    GtkWidget *box2;
    GtkWidget  *button5, *button6, *button7;
    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window2), "Recipes");
    gtk_window_set_default_size(GTK_WINDOW(window2), 400, 400);
    g_signal_connect(window2, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window2), box2);
    
    
    const gchar *chaine = (const gchar *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "recipes/", NULL);
    
    g_print("%s\n", concatenated);
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window2), vbox2);
	
	
	button5 = gtk_button_new_with_label("ComplexSearch");
    gtk_box_pack_start(GTK_BOX(box2), button5, TRUE, TRUE, 0);

    button6 = gtk_button_new_with_label("FindByNutrients");
    gtk_box_pack_start(GTK_BOX(box2), button6, TRUE, TRUE, 0);
    
    button7 = gtk_button_new_with_label("FindByIngredients");
    gtk_box_pack_start(GTK_BOX(box2), button7, TRUE, TRUE, 0);
    
    g_signal_connect(button5, "clicked", G_CALLBACK(on_button_clicked_triple_R), NULL);
    g_signal_connect(button5, "clicked", G_CALLBACK(open_window5), (gpointer)concatenated);
    g_signal_connect(button6, "clicked", G_CALLBACK(on_button_clicked_triple_R),NULL);
    g_signal_connect(button6, "clicked", G_CALLBACK(open_window7), (gpointer)concatenated);
    g_signal_connect(button7, "clicked", G_CALLBACK(on_button_clicked_triple_R),NULL);
    g_signal_connect(button7, "clicked", G_CALLBACK(open_window9), (gpointer)concatenated);
    
    
    gtk_widget_show_all(window2);
    
}


// Fonction de rappel qui se déclenche lorsque le bouton est cliqué
void on_button_clicked_double(GtkButton *button, gpointer user_data) {
    if (g_strcmp0(gtk_button_get_label(button), "Recipes") == 0) {
        // Code à exécuter pour le bouton Recipes
        g_print("Bouton Recipes a été cliqué.\n");
        
      	
      	

        // Ouverture de la fenêtre 2
        
    } else if (g_strcmp0(gtk_button_get_label(button), "Ingredients") == 0) {
        // Code à exécuter pour le bouton Ingredients
        g_print("Bouton Ingredients a été cliqué.\n");
		
       
    }
}

int main(int argc, char *argv[]) {
    GtkWidget *button1, *button2, *button3, *button4;
    GtkWidget *vbox1;
    GtkWidget *box1;
    GtkWidget *entry1, *entry2;

    gtk_init(&argc, &argv);

    // Ouverture du fichier en mode écriture
    data = fopen("data.txt", "w");
    if (data == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return -1;
    }

    window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window1), "Accueil");
    gtk_window_set_default_size(GTK_WINDOW(window1), 400, 400);

    box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window1), box1);

    // Saisie du nom dans la boite "Entrez votre nom"
    entry1 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Entrez votre nom");
    gtk_box_pack_start(GTK_BOX(box1), entry1, TRUE, TRUE, 0);

    // Saisie du nom dans la boite "Entrez votre adresse mail"
    entry2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Entrez votre adresse mail");
    gtk_box_pack_start(GTK_BOX(box1), entry2, TRUE, TRUE, 0);

    vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window1), vbox1);
    
    button4 = gtk_button_new_with_label("Valider");
    gtk_box_pack_start(GTK_BOX(box1), button4, TRUE, TRUE, 0);

    button1 = gtk_button_new_with_label("Recipes");
    gtk_box_pack_start(GTK_BOX(box1), button1, TRUE, TRUE, 0);

    button2 = gtk_button_new_with_label("Ingredients");
    gtk_box_pack_start(GTK_BOX(box1), button2, TRUE, TRUE, 0);

    button3 = gtk_button_new_with_label("Fermer");
    gtk_box_pack_start(GTK_BOX(box1), button3, TRUE, TRUE, 0);
    
    // Affichage du nom dans le Terminal
    g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(on_button_name), entry1);
    g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Affichage du mail dans le Terminal
    g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(on_button_mail), entry2);
    g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	//gchar **concatenated_string_ptr = NULL;
	const gchar *json_text ="https://api.spoonacular.com/";
	
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button_clicked_double), NULL);
    g_signal_connect(button1, "clicked", G_CALLBACK(open_window2), (gpointer)json_text);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked_double), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(open_window3), (gpointer)json_text);
	
    gtk_box_pack_start(GTK_BOX(vbox1), button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox1), button2, TRUE, TRUE, 0);

    
    
    

   
	
	
	g_signal_connect(button3, "clicked", G_CALLBACK(close_window), window1);
	
    gtk_widget_show_all(window1);
    gtk_main();

    // Fermeture du fichier
    fclose(data);

    return 0;
}

