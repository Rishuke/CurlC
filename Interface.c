#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdarg.h>
#include <curl/curl.h>

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
    const gchar *param= gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Le nom de parametre est : %s\n", param);
    
    
}

void on_button_clicked2(GtkButton *button, gpointer data)
{
	GtkWidget *window3;
   	GtkWidget *label;
    GtkWidget *vbox3;

    

    window3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window3, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    vbox3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window3), vbox3);
    
   	label = gtk_label_new("Hello, world!");
    gtk_box_pack_start(GTK_BOX(vbox3), label, TRUE, TRUE, 0);
	
    
    
    gtk_widget_show_all(window3);
    

    gtk_main();
}

	
void on_button_clicked(GtkButton *button, gpointer data)
{
    GtkWidget *window2;
    
    // Création de la deuxième fenêtre
    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window2), "Renseignement des paramètres");
    gtk_window_set_default_size(GTK_WINDOW(window2), 400, 300);
    

    GtkWidget *button2;
    GtkWidget *vbox2;
    GtkWidget *box2;
     
	
	
    
    
    box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window2), box2);
    
    
   
    
   
    // Création d'une boîte verticale pour contenir le bouton
    vbox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window2), vbox2);
    
    // Création du bouton
    button2 = gtk_button_new_with_label("Envoyer");
    
    
   

    
    for(int i = 1; i<= global_result;i++){
    	GtkWidget *entry = gtk_entry_new();
    	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez votre parametre ");
    	gtk_box_pack_start(GTK_BOX(box2), entry, TRUE, TRUE, 0);
    	g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(on_button_param), entry);
    	g_signal_connect(G_OBJECT(window2), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    	
    	
   	}
   	
   	
   	gtk_box_pack_start(GTK_BOX(box2), button2, TRUE, TRUE, 0);
    //g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_container_add(GTK_CONTAINER(vbox2), button2);
    
    gtk_container_add(GTK_CONTAINER(window2), button2);
    
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked2), NULL);
    gtk_container_add(GTK_CONTAINER(vbox2), button2);
    
    
    // Affichage de la deuxième fenêtre
    gtk_widget_show_all(window2);
}


/*void requete(int count, ...){
	CURL *curl;
  	CURLcode res;
  	char chaine1[100] = "https://pokebuildapi.fr/api/v1";
  	char chaine2[100] = "";
	
	strcat(chaine1,chaine2);
  	curl = curl_easy_init();
  	va_list ap;
  	va_start(ap,count);
	if(curl) {
  		
	  	for (int k = 0; k < count; k++) {
	  		
	  		char *str = va_arg(ap,char*);
	  		
		    strcat(chaine2,str);
		    
		    
		}
		va_end(ap);
		printf("%s\n",strcat(chaine1,chaine2));
		curl_easy_setopt(curl, CURLOPT_URL, strcat(chaine1,chaine2)); // Remplacez l'URL par l'URL de votre base de données
		//https://www.thecocktaildb.com/api/json/v1/1/search.php?s=margarita
		//"jdbc:mysql://localhost:3306/Meal?user=admin&password=password"
		//https://pokebuildapi.fr/api/v1/pokemon
		res = curl_easy_perform(curl);

		if(res != CURLE_OK)
		  fprintf(stderr, "Erreur lors de la requête : %s\n", curl_easy_strerror(res));

		curl_easy_cleanup(curl);
	  }
}*/


void requete(GtkWidget *label, int count, ...) {
	
	
    CURL *curl;
    CURLcode res;
    char chaine1[100] = "https://pokebuildapi.fr/api/v1";
    char chaine2[100] = "";

    strcat(chaine1, chaine2);
    curl = curl_easy_init();
    va_list ap;
    va_start(ap, count);
    if(curl) {
        for (int k = 0; k < count; k++) {
            char *str = va_arg(ap,char*);
            strcat(chaine2, str);
        }
        va_end(ap);

        char url[200];
        strcpy(url, strcat(chaine1, chaine2));
        curl_easy_setopt(curl, CURLOPT_URL, url); // Remplacez l'URL par l'URL de votre base de données
        //https://www.thecocktaildb.com/api/json/v1/1/search.php?s=margarita
        //"jdbc:mysql://localhost:3306/Meal?user=admin&password=password"
        //https://pokebuildapi.fr/api/v1/pokemon
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "Erreur lors de la requête : %s\n", curl_easy_strerror(res));

        gchar *response = g_strdup(curl_easy_escape(curl, url, 0));
        gtk_label_set_text(GTK_LABEL(label), response);
        g_free(response);

        curl_easy_cleanup(curl);
        
    }
}
	
	
	
	
int main(int argc, char *argv[]) {
	
    GtkWidget *window;
    GtkWidget *button;
	GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *entry3;
    GtkWidget *vbox;
    GtkWidget *box;
    GtkWidget *label;
   
    
  	
    
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
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry3), "Entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API");
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
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_button_nbparam),entry3);
    //GINT_TO_POINTER(count
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_container_add(GTK_CONTAINER(vbox), button);
    
    gtk_container_add(GTK_CONTAINER(window), button);
    
   
    gtk_widget_show_all(window);
    

    gtk_main();
	
	/*system("gcc -Wall -o Wicookin Wicookin.c -lcurl");
	
	int result = system("./Wicookin /pokemon"); // exécute le programme "mon_programme"
	
    if (result != 0) {
        printf("Erreur lors de l'exécution de mon_programme !\n");
    }*/
    
    
    
	
	//requete(global_result,"/pokemon","850");
	//requete(label, global_result,"/pokemon","850");
	label = gtk_label_new("Hello, world!");
	requete(label, global_result , "/pokemon", "/pikachu");
	
    return 0;
}
