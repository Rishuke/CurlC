#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdarg.h>
#include <curl/curl.h>
#include "cJSON.h"


struct Liste{
    const gchar* data;
    struct Liste* next;
};

struct Liste* List = NULL; // Déclaration de la variable globale


GtkWidget *window1, *window2, *window3, *window4, *window5, *window6, *window7, *window8, *window9, *window10, *window11, *window12, *window13, *window14, *window15, *window16, *window17, *window18, *window19, *window20, *window21;

// Déclaration du pointeur de fichier global
FILE *data;


void addListe(const gchar* newData) {
    struct Liste* newList = malloc(sizeof(struct Liste));
    newList->data = newData;
    newList->next = List;
    List = newList;
}


void freeList() {
    struct Liste* current = List;
    while (current != NULL) {
        struct Liste* next = current->next;
        free(current);
        current = next;
    }
}

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

void on_button_param(const gchar* tab, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    const gchar* param = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("Le nom de parametre est : %s\n", param);
    addListe(param);
    
  
    
}



void open_window21() {
    GtkWidget *window21, *text_view, *scroll_window;
    GtkTextBuffer *buffer;
    gchar *result;
    FILE *file;
    char *file_content;
    long file_size;
    cJSON *json, *results, *recipe, *title;

    // Création de la fenêtre GTK
    gtk_init(NULL, NULL);
    window21 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window21), "API2.3");
    gtk_window_set_default_size(GTK_WINDOW(window21), 400, 400);
    g_signal_connect(window21, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Ouverture et lecture du fichier JSON
    file = fopen("response.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    file_content = (char *)malloc(file_size + 1);
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';
	printf("%s\n",file_content);
	
	
    // Parsing du JSON
    json = cJSON_Parse(file_content);
    if (json == NULL) {
        printf("Erreur de parsing JSON.\n");
        free(file_content);
        fclose(file);
        return;
    }

    // Accès aux résultats des recettes
    results = cJSON_GetObjectItem(json, "results");
    if (results == NULL || !cJSON_IsArray(results)) {
        printf("Erreur lors de l'accès aux résultats des recettes.\n");
        cJSON_Delete(json);
        free(file_content);
        fclose(file);
        return;
    }

    // Concaténation des titres de recettes
    const gchar* str1 = "Titre de recette : ";
    result = g_strdup("");
    cJSON_ArrayForEach(recipe, results) {
        title = cJSON_GetObjectItem(recipe, "title");
        if (title != NULL && cJSON_IsString(title)) {
            result = g_strconcat(result,g_strconcat(str1, title->valuestring, "\n", NULL),NULL);
        }
    }

    // Création du widget GtkTextView pour afficher les titres
    text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, result, -1);

    // Création de la fenêtre de défilement pour le widget GtkTextView
    scroll_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll_window), text_view);

    // Ajout du widget GtkTextView à la fenêtre
    gtk_container_add(GTK_CONTAINER(window21), scroll_window);

    // Affichage de la fenêtre et démarrage de la boucle principale GTK
    gtk_widget_show_all(window21);
    gtk_main();

    // Nettoyage
    g_free(result);
    cJSON_Delete(json);
   free(file_content);
    fclose(file);
}

void open_file1(GtkButton *button,gpointer user_data) {
	
    CURL *curl;
    CURLcode res;
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    
    
    
    
    while (List != NULL) {
        chaine = g_strconcat(chaine, List->data, NULL);
        List = List->next;
    }
    printf("\n");
    
    g_print("%s\n", chaine);
    
    curl = curl_easy_init();
    
	if(curl) {
    	FILE* file = fopen("response.txt", "wb"); // Ouvre le fichier en mode binaire
  		
  		//const gchar *json_text ="https://api.spoonacular.com/recipes/complexSearch?apiKey=759b7e6c793c4ec8bff63b4940a952ed";
  		
  		//gchar *result = g_strdup_printf("%s%s", json_text, param);
  		
  		// Configuration de l'URL de l'API
        curl_easy_setopt(curl, CURLOPT_URL, chaine);
        
        
        //const gchar *response = NULL;
        
        // Configuration de la fonction de rappel pour écrire la réponse dans une chaîne
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback2);
       // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
       // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  	
  		
    //https://api.spoonacular.com/recipes/716429/information?apiKey=759b7e6c793c4ec8bff63b4940a952ed&includeNutrition=true
    //https://www.thecocktaildb.com/api/json/v1/1/search.php?s=margarita
    //"jdbc:mysql://localhost:3306/Meal?user=admin&password=password"
    //https://pokebuildapi.fr/api/v1/pokemon/type/Eau
    //https://api.github.com/users/petrgazarov
    
    
    	
  

	res = curl_easy_perform(curl);
	
    if (res != CURLE_OK) {
            printf("Erreur lors de l'exécution de la requête : %s\n", curl_easy_strerror(res));
        } else {
            // Affichage de la réponse
            printf("Réponse de l'API :\n%s\n", chaine);
           // const gchar *j = g_strdup(response);
            printf("Réponse de l'API a été enregistrée dans le fichier response.txt.\n");
            // Création d'un widget de texte
    
   

    
            /*
            
            // Création d'un widget GtkTextView pour afficher le texte JSON brut
    		GtkWidget *text_view = gtk_text_view_new();
    		
    		GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
   			 //gtk_text_buffer_set_text(buffer, j , -1);
   			 gtk_text_buffer_set_text(buffer, file_content, -1);
   			 
   			 
   			 // Ajout du widget GtkTextView à la fenêtre
   			 GtkWidget *scroll_window = gtk_scrolled_window_new(NULL, NULL);
    		gtk_container_add(GTK_CONTAINER(scroll_window), text_view);
   			 gtk_container_add(GTK_CONTAINER(window21), scroll_window);*/
        }
		
        // Nettoyage
       // free(response);
       fclose(file);
        curl_easy_cleanup(curl);
    } else {
        printf("Erreur lors de l'initialisation de cURL.\n");
    }

    curl_global_cleanup();
    
    
    /*
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window21), vbox);
	
    gtk_widget_show_all(window21);*/
    
    freeList();
    
    open_window21();
    
}

void open_window20() {
	GtkWidget *window20, *text_view, *scroll_window;
    GtkTextBuffer *buffer;
    gchar *result;
    FILE *file;
    char *file_content;
    long file_size;
    cJSON *json, *results, *recipe, *title;

    // Création de la fenêtre GTK
    gtk_init(NULL, NULL);
    window20 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window20), "API6.3");
    gtk_window_set_default_size(GTK_WINDOW(window20), 400, 400);
    g_signal_connect(window20, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Ouverture et lecture du fichier JSON
    file = fopen("response.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    file_content = (char *)malloc(file_size + 1);
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';
	printf("%s\n",file_content);
	
	
    // Parsing du JSON
    json = cJSON_Parse(file_content);
    if (json == NULL) {
        printf("Erreur de parsing JSON.\n");
        free(file_content);
        fclose(file);
        return;
    }

    // Accès aux résultats des recettes
    results = cJSON_GetObjectItem(json, "results");
    if (results == NULL || !cJSON_IsArray(results)) {
        printf("Erreur lors de l'accès aux résultats des recettes.\n");
        cJSON_Delete(json);
        free(file_content);
        fclose(file);
        return;
    }

    // Concaténation des titres de recettes
    const gchar* str1 = "Titre de recette : ";
    result = g_strdup("");
    cJSON_ArrayForEach(recipe, results) {
        title = cJSON_GetObjectItem(recipe, "title");
        if (title != NULL && cJSON_IsString(title)) {
            result = g_strconcat(result,g_strconcat(str1, title->valuestring, "\n", NULL),NULL);
        }
    }

    // Création du widget GtkTextView pour afficher les titres
    text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, result, -1);

    // Création de la fenêtre de défilement pour le widget GtkTextView
    scroll_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll_window), text_view);

    // Ajout du widget GtkTextView à la fenêtre
    gtk_container_add(GTK_CONTAINER(window20), scroll_window);

    // Affichage de la fenêtre et démarrage de la boucle principale GTK
    gtk_widget_show_all(window20);
    gtk_main();

    // Nettoyage
    g_free(result);
    cJSON_Delete(json);
   free(file_content);
    fclose(file);
}




void open_file3(GtkButton *button,gpointer user_data) {
	
	CURL *curl;
    CURLcode res;
    
    
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    
    
    
    
    while (List != NULL) {
        chaine = g_strconcat(chaine, List->data, NULL);
        List = List->next;
    }
    printf("\n");
    
    g_print("%s\n", chaine);
    
    curl = curl_easy_init();
    
	if(curl) {
    	FILE* file = fopen("response.txt", "wb"); // Ouvre le fichier en mode binaire
  		
  		//const gchar *json_text ="https://api.spoonacular.com/recipes/complexSearch?apiKey=759b7e6c793c4ec8bff63b4940a952ed";
  		
  		//gchar *result = g_strdup_printf("%s%s", json_text, param);
  		// Configuration de l'URL de l'API
        curl_easy_setopt(curl, CURLOPT_URL, chaine);
        
        
        
        
        // Configuration de la fonction de rappel pour écrire la réponse dans une chaîne
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback2);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  	
  		
    //https://api.spoonacular.com/recipes/716429/information?apiKey=759b7e6c793c4ec8bff63b4940a952ed&includeNutrition=true
    //https://www.thecocktaildb.com/api/json/v1/1/search.php?s=margarita
    //"jdbc:mysql://localhost:3306/Meal?user=admin&password=password"
    //https://pokebuildapi.fr/api/v1/pokemon/type/Eau
    //https://api.github.com/users/petrgazarov
    
    
    	
    
    	
    

	res = curl_easy_perform(curl);
	
    if (res != CURLE_OK) {
            printf("Erreur lors de l'exécution de la requête : %s\n", curl_easy_strerror(res));
        } else {
            // Affichage de la réponse
            printf("Réponse de l'API :\n%s\n", chaine);
            //const gchar *j = g_strdup(response);
            printf("Réponse de l'API a été enregistrée dans le fichier response.txt.\n");
            // Création d'un widget de texte
            
        }

        // Nettoyage
       // free(response);
       fclose(file);
        curl_easy_cleanup(curl);
    } else {
        printf("Erreur lors de l'initialisation de cURL.\n");
    }

    curl_global_cleanup();
    
    
    
	
    
    freeList();
    
    open_window20();
    
}

void open_window19() {
	GtkWidget *window19, *text_view, *scroll_window;
    GtkTextBuffer *buffer;
    gchar *result;
    FILE *file;
    char *file_content;
    long file_size;
    cJSON *json, *results, *recipe, *title;

    // Création de la fenêtre GTK
    gtk_init(NULL, NULL);
    window19 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window19), "API5.3");
    gtk_window_set_default_size(GTK_WINDOW(window19), 400, 400);
    g_signal_connect(window19, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Ouverture et lecture du fichier JSON
    file = fopen("response.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    file_content = (char *)malloc(file_size + 1);
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';
	printf("%s\n",file_content);
	
	
    // Parsing du JSON
    json = cJSON_Parse(file_content);
    if (json == NULL) {
        printf("Erreur de parsing JSON.\n");
        free(file_content);
        fclose(file);
        return;
    }

    // Accès aux résultats des recettes
    results = cJSON_GetObjectItem(json, "results");
    if (results == NULL || !cJSON_IsArray(results)) {
        printf("Erreur lors de l'accès aux résultats des recettes.\n");
        cJSON_Delete(json);
        free(file_content);
        fclose(file);
        return;
    }

    // Concaténation des titres de recettes
    const gchar* str1 = "Titre de recette : ";
    result = g_strdup("");
    cJSON_ArrayForEach(recipe, results) {
        title = cJSON_GetObjectItem(recipe, "ingredient");
        if (title != NULL && cJSON_IsString(title)) {
            result = g_strconcat(result,g_strconcat(str1, title->valuestring, "\n", NULL),NULL);
        }
    }

    // Création du widget GtkTextView pour afficher les titres
    text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, result, -1);

    // Création de la fenêtre de défilement pour le widget GtkTextView
    scroll_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll_window), text_view);

    // Ajout du widget GtkTextView à la fenêtre
    gtk_container_add(GTK_CONTAINER(window19), scroll_window);

    // Affichage de la fenêtre et démarrage de la boucle principale GTK
    gtk_widget_show_all(window19);
    gtk_main();

    // Nettoyage
    g_free(result);
    cJSON_Delete(json);
   free(file_content);
    fclose(file);
}


void open_file6(GtkButton *button,gpointer user_data) {
	
	CURL *curl;
    CURLcode res;
    
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    
    
    
    
    while (List != NULL) {
        chaine = g_strconcat(chaine, List->data, NULL);
        List = List->next;
    }
    printf("\n");
    
    g_print("%s\n", chaine);
    
    curl = curl_easy_init();
    
	if(curl) {
    	FILE* file = fopen("response.txt", "wb"); // Ouvre le fichier en mode binaire
  		
  		//const gchar *json_text ="https://api.spoonacular.com/recipes/complexSearch?apiKey=759b7e6c793c4ec8bff63b4940a952ed";
  		
  		//gchar *result = g_strdup_printf("%s%s", json_text, param);
  		// Configuration de l'URL de l'API
        curl_easy_setopt(curl, CURLOPT_URL, chaine);
        
        
        
        
        // Configuration de la fonction de rappel pour écrire la réponse dans une chaîne
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback2);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  	
  		
    //https://api.spoonacular.com/recipes/716429/information?apiKey=759b7e6c793c4ec8bff63b4940a952ed&includeNutrition=true
    //https://www.thecocktaildb.com/api/json/v1/1/search.php?s=margarita
    //"jdbc:mysql://localhost:3306/Meal?user=admin&password=password"
    //https://pokebuildapi.fr/api/v1/pokemon/type/Eau
    //https://api.github.com/users/petrgazarov
    
    
    	
    
    

	res = curl_easy_perform(curl);
	
    if (res != CURLE_OK) {
            printf("Erreur lors de l'exécution de la requête : %s\n", curl_easy_strerror(res));
        } else {
            // Affichage de la réponse
            printf("Réponse de l'API :\n%s\n", chaine);
            //const gchar *j = g_strdup(response);
            printf("Réponse de l'API a été enregistrée dans le fichier response.txt.\n");
            // Création d'un widget de texte
    
   

    
            
         
        }

        // Nettoyage
       // free(response);
       fclose(file);
        curl_easy_cleanup(curl);
    } else {
        printf("Erreur lors de l'initialisation de cURL.\n");
    }

    curl_global_cleanup();
    
    
    
    
    freeList();
    
    open_window19();
}

void open_window18() {
	GtkWidget *window18, *text_view, *scroll_window;
    GtkTextBuffer *buffer;
    gchar *result;
    FILE *file;
    char *file_content;
    long file_size;
    cJSON *json, *results, *recipe, *title;

    // Création de la fenêtre GTK
    gtk_init(NULL, NULL);
    window18 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window18), "API3.3");
    gtk_window_set_default_size(GTK_WINDOW(window18), 400, 400);
    g_signal_connect(window18, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Ouverture et lecture du fichier JSON
    file = fopen("response.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    file_content = (char *)malloc(file_size + 1);
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';
	printf("%s\n",file_content);
	
	
    // Parsing du JSON
    json = cJSON_Parse(file_content);
    if (json == NULL) {
        printf("Erreur de parsing JSON.\n");
        free(file_content);
        fclose(file);
        return;
    }

    // Accès aux résultats des recettes
    results = cJSON_GetObjectItem(json, "results");
    if (results == NULL || !cJSON_IsArray(results)) {
        printf("Erreur lors de l'accès aux résultats des recettes.\n");
        cJSON_Delete(json);
        free(file_content);
        fclose(file);
        return;
    }

    // Concaténation des titres de recettes
    const gchar* str1 = "nom de recette : ";
    result = g_strdup("");
    cJSON_ArrayForEach(recipe, results) {
        title = cJSON_GetObjectItem(recipe, "name");
        if (title != NULL && cJSON_IsString(title)) {
            result = g_strconcat(result,g_strconcat(str1, title->valuestring, "\n", NULL),NULL);
        }
    }

    // Création du widget GtkTextView pour afficher les titres
    text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, result, -1);

    // Création de la fenêtre de défilement pour le widget GtkTextView
    scroll_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll_window), text_view);

    // Ajout du widget GtkTextView à la fenêtre
    gtk_container_add(GTK_CONTAINER(window18), scroll_window);

    // Affichage de la fenêtre et démarrage de la boucle principale GTK
    gtk_widget_show_all(window18);
    gtk_main();

    // Nettoyage
    g_free(result);
    cJSON_Delete(json);
   free(file_content);
    fclose(file);
    
}


void open_file5(GtkButton *button,gpointer user_data) {
	
	CURL *curl;
    CURLcode res;
   
    
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    
    
    
    
    while (List != NULL) {
        chaine = g_strconcat(chaine, List->data, NULL);
        List = List->next;
    }
    printf("\n");
    
    g_print("%s\n", chaine);
    
    curl = curl_easy_init();
    
	if(curl) {
    	FILE* file = fopen("response.txt", "wb"); // Ouvre le fichier en mode binaire
  		
  		//const gchar *json_text ="https://api.spoonacular.com/recipes/complexSearch?apiKey=759b7e6c793c4ec8bff63b4940a952ed";
  		
  		//gchar *result = g_strdup_printf("%s%s", json_text, param);
  		// Configuration de l'URL de l'API
        curl_easy_setopt(curl, CURLOPT_URL, chaine);
        
        
        
        
        // Configuration de la fonction de rappel pour écrire la réponse dans une chaîne
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback2);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  	
  		
    //https://api.spoonacular.com/recipes/716429/information?apiKey=759b7e6c793c4ec8bff63b4940a952ed&includeNutrition=true
    //https://www.thecocktaildb.com/api/json/v1/1/search.php?s=margarita
    //"jdbc:mysql://localhost:3306/Meal?user=admin&password=password"
    //https://pokebuildapi.fr/api/v1/pokemon/type/Eau
    //https://api.github.com/users/petrgazarov
    
    
    	
    
    	
    
    

	res = curl_easy_perform(curl);
	
    if (res != CURLE_OK) {
            printf("Erreur lors de l'exécution de la requête : %s\n", curl_easy_strerror(res));
        } else {
            // Affichage de la réponse
            printf("Réponse de l'API :\n%s\n", chaine);
            //const gchar *j = g_strdup(response);
            printf("Réponse de l'API a été enregistrée dans le fichier response.txt.\n");
            // Création d'un widget de texte
    
   

    
            
            
         
        }

        // Nettoyage
       // free(response);
       fclose(file);
        curl_easy_cleanup(curl);
    } else {
        printf("Erreur lors de l'initialisation de cURL.\n");
    }

    curl_global_cleanup();
    
    
   
    
    freeList();
    open_window18();
}

void open_window17() {
	GtkWidget *window17, *text_view, *scroll_window;
    GtkTextBuffer *buffer;
    gchar *result;
    FILE *file;
    char *file_content;
    long file_size;
    cJSON *json, *results, *recipe, *title;
    
    // Création de la fenêtre GTK
    gtk_init(NULL, NULL);
    window17 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window17), "API4.3");
    gtk_window_set_default_size(GTK_WINDOW(window17), 400, 400);
     g_signal_connect(window17, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Ouverture et lecture du fichier JSON
    file = fopen("response.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    file_content = (char *)malloc(file_size + 1);
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';
	printf("%s\n",file_content);
	
	
    // Parsing du JSON
    json = cJSON_Parse(file_content);
    if (json == NULL) {
        printf("Erreur de parsing JSON.\n");
        free(file_content);
        fclose(file);
        return;
    }

    // Accès aux résultats des recettes
    results = cJSON_GetObjectItem(json, "results");
   if (results == NULL || !cJSON_IsArray(results)) {
        printf("Erreur lors de l'accès aux résultats des recettes.\n");
        cJSON_Delete(json);
        free(file_content);
        fclose(file);
        return;
    }

    // Concaténation des titres de recettes
    const gchar* str1 = "Titre de recette : ";
    result = g_strdup("");
    cJSON_ArrayForEach(recipe, results) {
        title = cJSON_GetObjectItem(recipe, "title");
        if (title != NULL && cJSON_IsString(title)) {
            result = g_strconcat(result,g_strconcat(str1, title->valuestring, "\n", NULL),NULL);
        }
    }

    // Création du widget GtkTextView pour afficher les titres
    text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, result, -1);

    // Création de la fenêtre de défilement pour le widget GtkTextView
    scroll_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll_window), text_view);

    // Ajout du widget GtkTextView à la fenêtre
    gtk_container_add(GTK_CONTAINER(window17), scroll_window);

    // Affichage de la fenêtre et démarrage de la boucle principale GTK
    gtk_widget_show_all(window17);
    gtk_main();

    // Nettoyage
    g_free(result);
    cJSON_Delete(json);
   free(file_content);
    fclose(file);

    
}

void open_file2(GtkButton *button,gpointer user_data) {
	
	CURL *curl;
    CURLcode res;
    
   
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    
    
    
    
    while (List != NULL) {
        chaine = g_strconcat(chaine, List->data, NULL);
        List = List->next;
    }
    printf("\n");
    
    g_print("%s\n", chaine);
    
    curl = curl_easy_init();
    
	if(curl) {
    	FILE* file = fopen("response.txt", "wb"); // Ouvre le fichier en mode binaire
  		
  		//const gchar *json_text ="https://api.spoonacular.com/recipes/complexSearch?apiKey=759b7e6c793c4ec8bff63b4940a952ed";
  		
  		//gchar *result = g_strdup_printf("%s%s", json_text, param);
  		// Configuration de l'URL de l'API
        curl_easy_setopt(curl, CURLOPT_URL, chaine);
        
        
        
        
        // Configuration de la fonction de rappel pour écrire la réponse dans une chaîne
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback2);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  	
  		
    //https://api.spoonacular.com/recipes/716429/information?apiKey=759b7e6c793c4ec8bff63b4940a952ed&includeNutrition=true
    //https://www.thecocktaildb.com/api/json/v1/1/search.php?s=margarita
    //"jdbc:mysql://localhost:3306/Meal?user=admin&password=password"
    //https://pokebuildapi.fr/api/v1/pokemon/type/Eau
    //https://api.github.com/users/petrgazarov
    
    
    	
    
 
    
    

	res = curl_easy_perform(curl);
	
    if (res != CURLE_OK) {
            printf("Erreur lors de l'exécution de la requête : %s\n", curl_easy_strerror(res));
        } else {
            // Affichage de la réponse
            printf("Réponse de l'API :\n%s\n", chaine);
            //const gchar *j = g_strdup(response);
            printf("Réponse de l'API a été enregistrée dans le fichier response.txt.\n");
            // Création d'un widget de texte
    
   

    
            
            
        }

        // Nettoyage
       // free(response);
       fclose(file);
        curl_easy_cleanup(curl);
    } else {
        printf("Erreur lors de l'initialisation de cURL.\n");
    }

    curl_global_cleanup();
    
    
    
	
    
    freeList();
    open_window17();
}

void open_window16() {
	GtkWidget *window16, *text_view, *scroll_window;
    GtkTextBuffer *buffer;
    gchar *result;
    FILE *file;
    char *file_content;
    long file_size;
    cJSON *json, *results, *recipe, *title;

    // Création de la fenêtre GTK
    gtk_init(NULL, NULL);
    window16 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window16), "API1.3");
    gtk_window_set_default_size(GTK_WINDOW(window16), 400, 400);
    g_signal_connect(window16, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Ouverture et lecture du fichier JSON
    file = fopen("response.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    file_content = (char *)malloc(file_size + 1);
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';
	printf("%s\n",file_content);
	
	
    // Parsing du JSON
    json = cJSON_Parse(file_content);
    if (json == NULL) {
        printf("Erreur de parsing JSON.\n");
        free(file_content);
        fclose(file);
        return;
    }

    // Accès aux résultats des recettes
    results = cJSON_GetObjectItem(json, "results");
    if (results == NULL || !cJSON_IsArray(results)) {
        printf("Erreur lors de l'accès aux résultats des recettes.\n");
        cJSON_Delete(json);
        free(file_content);
        fclose(file);
        return;
    }

    // Concaténation des titres de recettes
    const gchar* str1 = "Nom de recette : ";
    result = g_strdup("");
    cJSON_ArrayForEach(recipe, results) {
        title = cJSON_GetObjectItem(recipe, "name");
        if (title != NULL && cJSON_IsString(title)) {
            result = g_strconcat(result,g_strconcat(str1, title->valuestring, "\n", NULL),NULL);
        }
    }

    // Création du widget GtkTextView pour afficher les titres
    text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, result, -1);

    // Création de la fenêtre de défilement pour le widget GtkTextView
    scroll_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll_window), text_view);

    // Ajout du widget GtkTextView à la fenêtre
    gtk_container_add(GTK_CONTAINER(window16), scroll_window);

    // Affichage de la fenêtre et démarrage de la boucle principale GTK
    gtk_widget_show_all(window16);
    gtk_main();

    // Nettoyage
    g_free(result);
    cJSON_Delete(json);
   free(file_content);
    fclose(file);
}

void open_file4(GtkButton *button,gpointer user_data) {
	
	CURL *curl;
    CURLcode res;
    
   
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    
    
    
    
    while (List != NULL) {
        chaine = g_strconcat(chaine, List->data, NULL);
        List = List->next;
    }
    printf("\n");
    
    g_print("%s\n", chaine);
    
    curl = curl_easy_init();
    
	if(curl) {
    	FILE* file = fopen("response.txt", "wb"); // Ouvre le fichier en mode binaire
  		
  		//const gchar *json_text ="https://api.spoonacular.com/recipes/complexSearch?apiKey=759b7e6c793c4ec8bff63b4940a952ed";
  		
  		//gchar *result = g_strdup_printf("%s%s", json_text, param);
  		// Configuration de l'URL de l'API
        curl_easy_setopt(curl, CURLOPT_URL, chaine);
        
        
        
        
        // Configuration de la fonction de rappel pour écrire la réponse dans une chaîne
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback2);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  	
  		
    //https://api.spoonacular.com/recipes/716429/information?apiKey=759b7e6c793c4ec8bff63b4940a952ed&includeNutrition=true
    //https://www.thecocktaildb.com/api/json/v1/1/search.php?s=margarita
    //"jdbc:mysql://localhost:3306/Meal?user=admin&password=password"
    //https://pokebuildapi.fr/api/v1/pokemon/type/Eau
    //https://api.github.com/users/petrgazarov
    
    
    	
 
    

	res = curl_easy_perform(curl);
	
    if (res != CURLE_OK) {
            printf("Erreur lors de l'exécution de la requête : %s\n", curl_easy_strerror(res));
        } else {
            // Affichage de la réponse
            printf("Réponse de l'API :\n%s\n", chaine);
            //const gchar *j = g_strdup(response);
            printf("Réponse de l'API a été enregistrée dans le fichier response.txt.\n");
            // Création d'un widget de texte
    
   

    
            
            
            
        }

        // Nettoyage
       // free(response);
       fclose(file);
        curl_easy_cleanup(curl);
    } else {
        printf("Erreur lors de l'initialisation de cURL.\n");
    }

    curl_global_cleanup();
    
    
  
    
    freeList();
    
    open_window16();
}

void open_window15(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox;
    GtkWidget *box;
    GtkWidget *button1, *button2;
    window15 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window15), "API6.2");
    gtk_window_set_default_size(GTK_WINDOW(window15), 400, 400);
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window15), box);
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window15), vbox);
	
    
    // Création du bouton
    button1 = gtk_button_new_with_label("Envoyer");
   	
   	const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
	
    
    for(int i = 1; i<= global_result;i++){
    	GtkWidget *entry = gtk_entry_new();
    	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez votre parametre ");
    	gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);
    	//Pour entrer le nom des parametre 
    	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_param), entry);
    	g_signal_connect(G_OBJECT(window15), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    	
    	
   	}
   	
   	gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 0);
	g_signal_connect(button1, "clicked", G_CALLBACK(open_file3), (gpointer)chaine);
	
	// Création du bouton
	button2 =  gtk_button_new_with_label("Fermer");
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);
    g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window15);
    g_signal_connect(G_OBJECT(window15), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Ajout de la boîte verticale à la deuxième fenêtre
	gtk_container_add(GTK_CONTAINER(window15), vbox);	
    
    gtk_widget_show_all(window15);
    
}

void open_window14(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox;
    GtkWidget *box;
    GtkWidget *button1, *button2;
    window14 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window14), "API5.2");
    gtk_window_set_default_size(GTK_WINDOW(window14), 400, 400);
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window14), box);
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window14), vbox);
	
    
    // Création du bouton
    button1 = gtk_button_new_with_label("Envoyer");
   	
   	const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
	
    
    for(int i = 1; i<= global_result;i++){
    	GtkWidget *entry = gtk_entry_new();
    	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez votre parametre ");
    	gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);
    	//Pour entrer le nom des parametre 
    	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_param), entry);
    	g_signal_connect(G_OBJECT(window14), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    	
    	
   	}
   	
   	gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 0);
	g_signal_connect(button1, "clicked", G_CALLBACK(open_file6), (gpointer)chaine);
	
	// Création du bouton
	button2 =  gtk_button_new_with_label("Fermer");
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);
    g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window14);
    g_signal_connect(G_OBJECT(window14), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Ajout de la boîte verticale à la deuxième fenêtre
	gtk_container_add(GTK_CONTAINER(window14), vbox);	
    
    gtk_widget_show_all(window14);
    
}

void open_window13(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox;
    GtkWidget *box;
    GtkWidget *button1, *button2;
    window13 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window13), "API4.2");
    gtk_window_set_default_size(GTK_WINDOW(window13), 400, 400);
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window13), box);
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window13), vbox);
	
    
    // Création du bouton
    button1 = gtk_button_new_with_label("Envoyer");
   	
   	const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
	
    
    for(int i = 1; i<= global_result;i++){
    	GtkWidget *entry = gtk_entry_new();
    	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez votre parametre ");
    	gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);
    	//Pour entrer le nom des parametre 
    	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_param), entry);
    	g_signal_connect(G_OBJECT(window13), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    	
    	
   	}
   	
   	gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 0);
	g_signal_connect(button1, "clicked", G_CALLBACK(open_file2), (gpointer)chaine);
	
	// Création du bouton
	button2 =  gtk_button_new_with_label("Fermer");
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);
    g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window13);
    g_signal_connect(G_OBJECT(window13), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Ajout de la boîte verticale à la deuxième fenêtre
	gtk_container_add(GTK_CONTAINER(window13), vbox);	
    
    gtk_widget_show_all(window13);
    
}

void open_window12(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox;
    GtkWidget *box;
    GtkWidget *button1, *button2;
    window12 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window12), "API3.2");
    gtk_window_set_default_size(GTK_WINDOW(window12), 400, 400);
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window12), box);
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window12), vbox);
	
    
    // Création du bouton
    button1 = gtk_button_new_with_label("Envoyer");
   	
   
	const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    for(int i = 1; i<= global_result;i++){
    	GtkWidget *entry = gtk_entry_new();
    	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez votre parametre ");
    	gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);
    	//Pour entrer le nom des parametre 
    	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_param), entry);
    	g_signal_connect(G_OBJECT(window12), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    	
    	
   	}
   	
   	gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 0);
	g_signal_connect(button1, "clicked", G_CALLBACK(open_file5), (gpointer)chaine);
	
	// Création du bouton
	button2 =  gtk_button_new_with_label("Fermer");
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);
    g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window12);
    g_signal_connect(G_OBJECT(window12), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Ajout de la boîte verticale à la deuxième fenêtre
	gtk_container_add(GTK_CONTAINER(window12), vbox);	
    
    gtk_widget_show_all(window12);
    
}

void open_window11(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox;
    GtkWidget *box;
    GtkWidget *button1, *button2;
    window11 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window11), "API1.2");
    gtk_window_set_default_size(GTK_WINDOW(window11), 400, 400);
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window11), box);
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window11), vbox);
	
    
    // Création du bouton
    button1 = gtk_button_new_with_label("Envoyer");
   	
   
	const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    for(int i = 1; i<= global_result;i++){
    	GtkWidget *entry = gtk_entry_new();
    	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez votre parametre ");
    	gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);
    	//Pour entrer le nom des parametre 
    	g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_param), entry);
    	g_signal_connect(G_OBJECT(window11), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    	
    	
   	}
   	
   	gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 0);
	g_signal_connect(button1, "clicked", G_CALLBACK(open_file4), (gpointer)chaine);
	
	// Création du bouton
	button2 =  gtk_button_new_with_label("Fermer");
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);
    g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window11);
    g_signal_connect(G_OBJECT(window11), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Ajout de la boîte verticale à la deuxième fenêtre
	gtk_container_add(GTK_CONTAINER(window11), vbox);	
    
    gtk_widget_show_all(window11);
    
}

void open_window10(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox10;
    GtkWidget *box5;
    GtkWidget *button13, *button14;
    window10 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window10), "API2.2");
    gtk_window_set_default_size(GTK_WINDOW(window10), 400, 400);
    
    box5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window10), box5);
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox10 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window10), vbox10);
	
    
    // Création du bouton
    button13 = gtk_button_new_with_label("Envoyer");
   	
   
	const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    for(int i = 1; i<= global_result;i++){
    	GtkWidget *entry = gtk_entry_new();
    	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez votre parametre ");
    	gtk_box_pack_start(GTK_BOX(box5), entry, TRUE, TRUE, 0);
    	//Pour entrer le nom des parametre 
    	g_signal_connect(G_OBJECT(button13), "clicked", G_CALLBACK(on_button_param), entry);
    	g_signal_connect(G_OBJECT(window10), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    	
    	
   	}
   	
   	gtk_box_pack_start(GTK_BOX(box5), button13, TRUE, TRUE, 0);
	g_signal_connect(button13, "clicked", G_CALLBACK(open_file1), (gpointer)chaine);
	
	
	// Création du bouton
	button14 =  gtk_button_new_with_label("Fermer");
    gtk_box_pack_start(GTK_BOX(box5), button14, TRUE, TRUE, 0);
    g_signal_connect(button14, "clicked", G_CALLBACK(close_window), window10);
    g_signal_connect(G_OBJECT(window10), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Ajout de la boîte verticale à la deuxième fenêtre
	gtk_container_add(GTK_CONTAINER(window10), vbox10);	
    
    gtk_widget_show_all(window10);
    
}

void open_window9(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox;
    window9 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window9), "API6");
    gtk_window_set_default_size(GTK_WINDOW(window9), 400, 400);
    g_signal_connect(window9, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *box;
    GtkWidget *entry;
    GtkWidget  *button1, *button2;
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window9), box);
    
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "findByIngredients?apiKey=759b7e6c793c4ec8bff63b4940a952ed", NULL);
    
    g_print("%s\n", concatenated);
    
    //Saisi du nom dans la boite entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API");
    gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);
    
     // Création des bouton
    button1 = gtk_button_new_with_label("Valider");
    gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 0);
    
    //Affichage du nombre de parametre dans le Terminal
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_nbparam),entry);
    //GINT_TO_POINTER(count
    g_signal_connect(G_OBJECT(window9), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    g_signal_connect(button1, "clicked", G_CALLBACK(open_window15), (gpointer)concatenated);
    
    
    button2 = gtk_button_new_with_label("Fermer ");
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);
    
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window9), vbox);
	
	g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window9);
    
    gtk_widget_show_all(window9);
    
}

void open_window8(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox;
    window8 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window8), "API5");
    gtk_window_set_default_size(GTK_WINDOW(window8), 400, 400);
    g_signal_connect(window8, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *box;
    GtkWidget *entry;
    GtkWidget  *button1, *button2;
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window8), box);
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "substitutes?apiKey=759b7e6c793c4ec8bff63b4940a952ed", NULL);
    
    g_print("%s\n", concatenated);
    
    
     //Saisi du nom dans la boite entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API");
    gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);
    
     // Création des bouton
    button1 = gtk_button_new_with_label("Valider");
    gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 0);
    
    //Affichage du nombre de parametre dans le Terminal
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_nbparam),entry);
    //GINT_TO_POINTER(count
    g_signal_connect(G_OBJECT(window8), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    g_signal_connect(button1, "clicked", G_CALLBACK(open_window14), (gpointer)concatenated);
    
    
    button2 = gtk_button_new_with_label("Fermer ");
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);
    
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window8), vbox);
	
	g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window8);
    
    gtk_widget_show_all(window8);
    
    
}

void open_window7(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox;
    window7 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window7), "API4");
    gtk_window_set_default_size(GTK_WINDOW(window7), 400, 400);
    g_signal_connect(window7, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *box;
    GtkWidget *entry;
    GtkWidget  *button1, *button2;
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window7), box);
    
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "findByNutrients?apiKey=759b7e6c793c4ec8bff63b4940a952ed", NULL);
    
    g_print("%s\n", concatenated);
    
    
    
    //Saisi du nom dans la boite entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API");
    gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);
    
     // Création des bouton
    button1 = gtk_button_new_with_label("Valider");
    gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 0);
    
    //Affichage du nombre de parametre dans le Terminal
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_nbparam),entry);
    //GINT_TO_POINTER(count
    g_signal_connect(G_OBJECT(window7), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    g_signal_connect(button1, "clicked", G_CALLBACK(open_window13), (gpointer)concatenated);
    
    
    button2 = gtk_button_new_with_label("Fermer ");
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);
    
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window7), vbox);
	
	g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window7);
    
    gtk_widget_show_all(window7);
    
}

void open_window6(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox;
    window6 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window6), "API3");
    gtk_window_set_default_size(GTK_WINDOW(window6), 400, 400);
    g_signal_connect(window6, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *box;
    GtkWidget *entry;
    GtkWidget  *button1, *button2;
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window6), box);
    
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "autocomplete?apiKey=759b7e6c793c4ec8bff63b4940a952ed", NULL);
    
    g_print("%s\n", concatenated);
    
    
    
    //Saisi du nom dans la boite entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API");
    gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);
    
     // Création des bouton
    button1 = gtk_button_new_with_label("Valider");
    gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 0);
    
    //Affichage du nombre de parametre dans le Terminal
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_nbparam),entry);
    //GINT_TO_POINTER(count
    g_signal_connect(G_OBJECT(window6), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    g_signal_connect(button1, "clicked", G_CALLBACK(open_window12), (gpointer)concatenated);
    
    
    button2 = gtk_button_new_with_label("Fermer ");
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);
    
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window6), vbox);
	
	g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window6);
    
    gtk_widget_show_all(window6);
    
}

void open_window5(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox5;
    window5 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window5), "API2");
    gtk_window_set_default_size(GTK_WINDOW(window5), 400, 400);
    g_signal_connect(window5, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *box4;
    GtkWidget *entry3;
    GtkWidget  *button11, *button12;
    
    box4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window5), box4);
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "complexSearch?apiKey=759b7e6c793c4ec8bff63b4940a952ed", NULL);
    
    g_print("%s\n", concatenated);
    
    //Saisi du nom dans la boite entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API
    entry3 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry3), "Entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API");
    gtk_box_pack_start(GTK_BOX(box4), entry3, TRUE, TRUE, 0);
    
     // Création des bouton
    button11 = gtk_button_new_with_label("Valider");
    gtk_box_pack_start(GTK_BOX(box4), button11, TRUE, TRUE, 0);
    
    //Affichage du nombre de parametre dans le Terminal
    g_signal_connect(G_OBJECT(button11), "clicked", G_CALLBACK(on_button_nbparam),entry3);
    //GINT_TO_POINTER(count
    g_signal_connect(G_OBJECT(window5), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    g_signal_connect(button11, "clicked", G_CALLBACK(open_window10), (gpointer)concatenated);
    
    
    button12 = gtk_button_new_with_label("Fermer ");
    gtk_box_pack_start(GTK_BOX(box4), button12, TRUE, TRUE, 0);
    
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window5), vbox5);
	
	g_signal_connect(button12, "clicked", G_CALLBACK(close_window), window5);
    
    gtk_widget_show_all(window5);
    
}

void open_window4(GtkButton *button,gpointer user_data) {
	GtkWidget *vbox;
    window4 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window4), "API1");
    gtk_window_set_default_size(GTK_WINDOW(window4), 400, 400);
    g_signal_connect(window4, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *box;
    GtkWidget *entry;
    GtkWidget  *button1, *button2;
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window4), box);
    
    
    
    
    const char *chaine = (const char *)user_data;
    g_print("%s\n", chaine);
    
    const gchar *concatenated = g_strconcat(chaine, "search?apiKey=759b7e6c793c4ec8bff63b4940a952ed", NULL);
    
    g_print("%s\n", concatenated);
    
    
    //Saisi du nom dans la boite entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez le nombre de paramètres que vous voulez renseigner pour votre recherche dans l'API");
    gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);
    
     // Création des bouton
    button1 = gtk_button_new_with_label("Valider");
    gtk_box_pack_start(GTK_BOX(box), button1, TRUE, TRUE, 0);
    
    //Affichage du nombre de parametre dans le Terminal
    g_signal_connect(G_OBJECT(button1), "clicked", G_CALLBACK(on_button_nbparam),entry);
    //GINT_TO_POINTER(count
    g_signal_connect(G_OBJECT(window4), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    g_signal_connect(button1, "clicked", G_CALLBACK(open_window11), (gpointer)concatenated);
    
    
    button2 = gtk_button_new_with_label("Fermer ");
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);
    
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window4), vbox);
	
	g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window4);
    
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


/*

curl = curl_easy_init();
    
	if(curl) {
    	FILE* file = fopen("response.txt", "wb"); // Ouvre le fichier en mode binaire
  		
  		//const gchar *json_text ="https://api.spoonacular.com/recipes/complexSearch?apiKey=759b7e6c793c4ec8bff63b4940a952ed";
  		
  		//gchar *result = g_strdup_printf("%s%s", json_text, param);
  		// Configuration de l'URL de l'API
        curl_easy_setopt(curl, CURLOPT_URL, concatenated);
        
        
        
        
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
            printf("Réponse de l'API :\n%s\n", concatenated);
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
   			 gtk_container_add(GTK_CONTAINER(window5), scroll_window);
        }

        // Nettoyage
       // free(response);
       fclose(file);
        curl_easy_cleanup(curl);
    } else {
        printf("Erreur lors de l'initialisation de cURL.\n");
    }

    curl_global_cleanup();
*/

