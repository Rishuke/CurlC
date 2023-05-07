#include <gtk/gtk.h>

// Fonction de rappel pour le clic sur le bouton
/*static void on_button_clicked(GtkWidget *button, gpointer user_data) {
    g_print("Bouton cliqué\n");
}*/



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

void on_button_nbparam(GtkButton *button, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    const gchar *nbparam = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Le mail saisi est : %s\n", nbparam);
   
}

void on_button_clicked(GtkButton *button, gpointer data)
{
    GtkWidget *window2;
    
    // Création de la deuxième fenêtre
    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window2), "Renseignement des paramètres");
    gtk_window_set_default_size(GTK_WINDOW(window2), 400, 300);
    

    GtkWidget *button2;
    GtkWidget *vbox;
    GtkWidget *box;
    
	
	
    
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window2), box);
    
    
    
    for(int i = 1; i<= 3;i++){
    	GtkWidget *entry = gtk_entry_new();
    	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez votre parametre ");
    	gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);
    	
   }
    
   
    // Création d'une boîte verticale pour contenir le bouton
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window2), vbox);
    
    // Création du bouton
    button2 = gtk_button_new_with_label("Envoyer");
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);
    
    
    
    //g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_container_add(GTK_CONTAINER(vbox), button2);
    
    gtk_container_add(GTK_CONTAINER(window2), button2);
    
    // Affichage de la deuxième fenêtre
    gtk_widget_show_all(window2);
}


int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;
	GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *vbox;
    GtkWidget *box;
    gtk_init(&argc, &argv);
	
	// Création de la fenêtre
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Ma fenêtre");
     gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    
    gtk_window_set_title(GTK_WINDOW(window), "Wicookin");
    
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);
    
    entry1 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Entrez votre nom");
    gtk_box_pack_start(GTK_BOX(box), entry1, TRUE, TRUE, 0);
    
    
   


    
    entry2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Entrez votre adresse email");
    gtk_box_pack_start(GTK_BOX(box), entry2, TRUE, TRUE, 0);
    
    entry3 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry3), "Entrez le nombres de paramètres que vous voulez renseigner pour votre recherche dans l'API");
    gtk_box_pack_start(GTK_BOX(box), entry3, TRUE, TRUE, 0);
    
   
    // Création d'une boîte verticale pour contenir le bouton
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    // Création du bouton
    button = gtk_button_new_with_label("Envoyer");
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);
    
    //Affichage du nom dans le Terminal
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_name), entry1);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    //Affichage du mail dans le Terminal
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_mail), entry2);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    
    //Affichage du number_paramater dans le Terminal
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_nbparam), entry3);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_container_add(GTK_CONTAINER(vbox), button);
    
    gtk_container_add(GTK_CONTAINER(window), button);
    
   

    
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
