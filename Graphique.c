#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdarg.h>
#include <curl/curl.h>

GtkWidget *window1, *window2, *window3;
//char *chaine;
gchar *chaine;
FILE *data; // Déclaration du pointeur de fichier global

// Fonction de rappel pour écrire les données de réponse dans une chaîne
size_t write_callback(void* contents, size_t size, size_t nmemb, char** response) {
	size_t realsize = size * nmemb;
    *response = realloc(*response, realsize + 1);
    
    if (*response == NULL) {
        printf("Erreur de mémoire lors de l'allocation du tampon de réponse.\n");
        return 0;
    }
    memcpy(*response, contents, realsize);
    (*response)[realsize] = '\0';
    return realsize;
}

// Fonction de rappel pour écrire les données de réponse dans un fichier
size_t write_callback2(void* contents, size_t size, size_t nmemb, FILE* file) {
    return fwrite(contents, size, nmemb, file);
}

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
    fprintf(data, "%s\n",name);
}

// Fonction de rappel qui se declenche lorsque le bouton est cliqué et affichage d'un print dans le Terminal
void on_button_mail(GtkButton *button, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    const gchar *mail = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Le mail saisi est : %s\n", mail);
    if (data == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        
    }
    fprintf(data, "%s\n",mail);
}

int global_result; // Variable globale pour stocker le résultat



void on_button_nbparam(GtkButton *button ,gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    const gchar *nbparam = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Le nombre de parametre est de : %s\n", nbparam);
    //char tab[100] = nbpamarm;
    global_result = atoi(nbparam);
    printf("Le résultat est : %d\n", global_result);
    if (data == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        
    }
    fprintf(data, "%s\n",nbparam);
}

const gchar *param;

void on_button_param(const gchar* tab, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    param = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Le nom de parametre est : %s\n", param);
    printf("%d\n", global_result);
    //int a = 0;
    
    /*if(a < global_result){
    	//chaine = strcpy(chaine,(char*)param);
    	g_stpcpy(chaine, param);
    	a++;
    	g_print("Le nom de parametre chaine est : %s\n", chaine);
    }*/
  
    
}

// Fonction pour lire le contenu d'un fichier et le stocker dans une chaîne de caractères
char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return NULL;
    }

    // Déterminer la taille du fichier
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allouer un tampon pour le contenu du fichier
    char* buffer = (char*)malloc((file_size + 1) * sizeof(char));
    if (buffer == NULL) {
        fclose(file);
        printf("Erreur de mémoire lors de l'allocation du tampon.\n");
        return NULL;
    }

    // Lire le contenu du fichier dans le tampon
    fread(buffer, sizeof(char), file_size, file);
    buffer[file_size] = '\0';

    fclose(file);

    return buffer;
}



void open_window3() {
    window3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window3), "Requete de l'API");
    gtk_window_set_default_size(GTK_WINDOW(window3), 400, 400);
    //GtkWidget *label;
    GtkWidget *vbox3;
    GtkWidget *box3;
    GtkWidget *button1;
    CURL *curl;
    CURLcode res;
    
    box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    
    
    vbox3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    
    
   	//label = gtk_label_new("Hello, world!");
   // gtk_box_pack_start(GTK_BOX(vbox3), label, TRUE, TRUE, 0);
    
 
   	curl = curl_easy_init();
    
	if(curl) {
    		FILE* file = fopen("response.txt", "wb"); // Ouvre le fichier en mode binaire
  		char* response = NULL;
  		const gchar *json_text ="https://api.spoonacular.com/recipes/complexSearch?apiKey=759b7e6c793c4ec8bff63b4940a952ed";
  		
  		gchar *result = g_strdup_printf("%s%s", json_text, param);
  		// Configuration de l'URL de l'API
        	curl_easy_setopt(curl, CURLOPT_URL, result);
        
        
        
        
        // Configuration de la fonction de rappel pour écrire la réponse dans une chaîne
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback2);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  	
  		
    //https://api.spoonacular.com/recipes/716429/information?apiKey=759b7e6c793c4ec8bff63b4940a952ed&includeNutrition=true
    //https://www.thecocktaildb.com/api/json/v1/1/search.php?s=margarita
    //"jdbc:mysql://localhost:3306/Meal?user=admin&password=password"
    //https://pokebuildapi.fr/api/v1/pokemon/type/Eau
    //https://api.github.com/users/petrgazarov
    
    
    	
    
    	// Lire le contenu du fichier
   	const char* filename = "reponse.txt";
    	char* file_content = read_file(filename);
    
    

	res = curl_easy_perform(curl);
	
    if (res != CURLE_OK) {
            printf("Erreur lors de l'exécution de la requête : %s\n", curl_easy_strerror(res));
        } else {
            // Affichage de la réponse
            printf("Réponse de l'API :\n%s\n", response);
            //const gchar *j = g_strdup(response);
            printf("Réponse de l'API a été enregistrée dans le fichier response.txt.\n");
            // Création d'un widget de texte
    
   

    
            
            
            // Création d'un widget GtkTextView pour afficher le texte JSON brut
    		GtkWidget *text_view = gtk_text_view_new();
    		
    		GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
   			// gtk_text_buffer_set_text(buffer, j , -1);
   			 gtk_text_buffer_set_text(buffer, file_content, -1);
   			 
   			 
   			 // Ajout du widget GtkTextView à la fenêtre
   			 GtkWidget *scroll_window = gtk_scrolled_window_new(NULL, NULL);
    		gtk_container_add(GTK_CONTAINER(scroll_window), text_view);
   			 gtk_container_add(GTK_CONTAINER(window3), scroll_window);
        }

        // Nettoyage
       // free(response);
       fclose(file);
        curl_easy_cleanup(curl);
    } else {
        printf("Erreur lors de l'initialisation de cURL.\n");
    }

    curl_global_cleanup();
    
    
    
    
    
    
    
    //Création du bouton
	button1 =  gtk_button_new_with_label("Fermer");
    gtk_box_pack_start(GTK_BOX(box3), button1, TRUE, TRUE, 0);
    g_signal_connect(button1, "clicked", G_CALLBACK(close_window), window3);
    gtk_container_add(GTK_CONTAINER(window3), box3);
    
    gtk_container_add(GTK_CONTAINER(window3), vbox3);
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
	button2 =  gtk_button_new_with_label("Fermer");
    gtk_box_pack_start(GTK_BOX(box2), button2, TRUE, TRUE, 0);
    g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window2);
    
    // Ajout de la boîte verticale à la deuxième fenêtre
	gtk_container_add(GTK_CONTAINER(window2), vbox2);	
    
    gtk_widget_show_all(window2);
    
}

/*void requete(GtkWidget *label, int count, ...) {
	
	
    CURL *curl;
    CURLcode res;
    char chaine1[200] = "https://api.spoonacular.com/recipes/716429/information?apiKey=759b7e6c793c4ec8bff63b4940a952ed&includeNutrition=";
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
        //https://api.spoonacular.com/recipes/716429/information?apiKey=759b7e6c793c4ec8bff63b4940a952ed&includeNutrition=true
        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "Erreur lors de la requête : %s\n", curl_easy_strerror(res));

        gchar *response = g_strdup(curl_easy_escape(curl, url, 0));
        gtk_label_set_text(GTK_LABEL(label), response);
        g_free(response);

        curl_easy_cleanup(curl);
        
    }
}*/


int main(int argc, char *argv[]) {
	
    GtkWidget *button1, *button2;
    GtkWidget *vbox1;
    GtkWidget *box1;
    GtkWidget *entry1, *entry2, *entry3;
   // GtkWidget *label;
    
    //Allocation dynamique de la mémoire pour la variable globale
   // chaine = (char*)malloc(100*sizeof(char));
   
	data  = fopen("data.txt", "w"); // Ouverture du fichier en mode écriture
	
    
    gtk_init(&argc, &argv);

    window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window1), "Acceuil");
    gtk_window_set_default_size(GTK_WINDOW(window1), 400, 400);
    
    box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window1), box1);
    
    //Saisi du nom dans la boite entrez votre nom
    entry1 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry1), "Entrez votre nom");
    gtk_box_pack_start(GTK_BOX(box1), entry1, TRUE, TRUE, 0);
    
    //Saisi du nom dans la boite entrez votre adresse mail
    entry2 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry2), "Entrez votre adresse mail");
    gtk_box_pack_start(GTK_BOX(box1), entry2, TRUE, TRUE, 0);
    
    //Saisi du nom dans la boite entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API
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
	
	//label = gtk_label_new("Hello, world!");
	//requete(label, global_result,chaine);
	
	/*int r= 0;
	while(r < 2){
		tab[r] = get_string();
		g_print("Le nom de parametre chaine (main) est : %s\n", tab[r]);
		r++;
	}*/
	
    return 0;
}






































