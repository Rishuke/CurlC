#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdarg.h>
#include <curl/curl.h>

GtkWidget *window1, *window2, *window3;

void close_window(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(data);
}


void on_button_name(GtkButton *button, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Le nom saisi est : %s\n", name);
}

void on_button_mail(GtkButton *button, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    const gchar *mail = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Le mail saisi est : %s\n", mail);
}

int global_result; // Variable globale pour stocker le résultat



void on_button_nbparam(GtkButton *button ,gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    const gchar *nbparam = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Le nombre de parametre est de : %s\n", nbparam);
    //char tab[100] = nbpamarm;
    global_result = atoi(nbparam);
    printf("Le résultat est : %d\n", global_result);
}

void on_button_param(GtkButton *button, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    const gchar *param = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Le nom de parametre est : %s\n", param);
    
    
}

void open_window3() {
    window3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window3), "Requete de l'API");
    gtk_window_set_default_size(GTK_WINDOW(window3), 400, 400);
    
    
    
    gtk_widget_show_all(window3);
}

void open_window2() {
	GtkWidget *vbox2;
    GtkWidget *box2;
    GtkWidget *button1, *button2;
    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window2), "Renseignement des paramètres");
    gtk_window_set_default_size(GTK_WINDOW(window2), 400, 400);
    
    box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window2), box2);
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window2), vbox2);
	
    
    // Création du bouton
    button1 = gtk_button_new_with_label("Envoyer");
   	
   
	
    
    for(int i = 1; i<= global_result;i++){
    	GtkWidget *entry = gtk_entry_new();
    	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez votre parametre ");
    	gtk_box_pack_start(GTK_BOX(box2), entry, TRUE, TRUE, 0);
    	//Pour entrer le nom des parametre 
    	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_param), entry);
    	g_signal_connect(G_OBJECT(window2), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    	
    	
   	}
   	
   	gtk_box_pack_start(GTK_BOX(box2), button1, TRUE, TRUE, 0);
	g_signal_connect(button1, "clicked", G_CALLBACK(open_window3), window2);
	
	// Création du bouton
	button2 =  gtk_button_new_with_label("Close Window 2");
    gtk_box_pack_start(GTK_BOX(box2), button2, TRUE, TRUE, 0);
    g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window2);
    
    // Ajout de la boîte verticale à la deuxième fenêtre
	gtk_container_add(GTK_CONTAINER(window2), vbox2);	
    
    gtk_widget_show_all(window2);
    
}


int main(int argc, char *argv[]) {
    GtkWidget *button1, *button2;
    GtkWidget *vbox1;
    GtkWidget *box1;
    GtkWidget *entry1, *entry2, *entry3;

    gtk_init(&argc, &argv);

    window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window1), "Acceuil");
    gtk_window_set_default_size(GTK_WINDOW(window1), 400, 400);
    
    box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window1), box1);
    
    entry1 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Entrez votre nom");
    gtk_box_pack_start(GTK_BOX(box1), entry1, TRUE, TRUE, 0);
    
    entry2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Entrez votre adresse email");
    gtk_box_pack_start(GTK_BOX(box1), entry2, TRUE, TRUE, 0);
    
    entry3 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry3), "Entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API");
    gtk_box_pack_start(GTK_BOX(box1), entry3, TRUE, TRUE, 0);
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    
    // Création des bouton
    button1 = gtk_button_new_with_label("Envoyer");
    gtk_box_pack_start(GTK_BOX(box1), button1, TRUE, TRUE, 0);
    
    button2 = gtk_button_new_with_label("Fermer ");
    gtk_box_pack_start(GTK_BOX(box1), button2, TRUE, TRUE, 0);
    //gtk_box_pack_start(GTK_BOX(vbox), button3, TRUE, TRUE, 0);
    
    //Affichage du nom dans le Terminal
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_name), entry1);
    g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //Affichage du mail dans le Terminal
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_mail), entry2);
    g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    
    //Affichage du nombre de parametre dans le Terminal
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_nbparam),entry3);
    //GINT_TO_POINTER(count
    g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    
    g_signal_connect(button1, "clicked", G_CALLBACK(open_window2), NULL);

    
    g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window1);

	
	
	
    
    
    gtk_container_add(GTK_CONTAINER(window1), vbox1);
   
    
    
	gtk_widget_show_all(window1);
	gtk_main();
	
    return 0;
}






































