#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdarg.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>

// Définition de la structure Liste
struct Liste{
    const gchar* data;   // Champ de données de type gchar* (chaîne de caractères)
    struct Liste* next;  // Pointeur vers la prochaine structure Liste
};


struct Liste* List = NULL; // Déclaration de la variable globale


GtkWidget *window1 = NULL; // Déclaration de la fenetre window1


// Déclaration du pointeur de fichier global data
FILE *data;




// Fonction pour ajouter un nouvel élément à une liste
void addListe(const gchar* newData) {
    // Allouer de la mémoire pour une nouvelle structure Liste
    struct Liste* newList = malloc(sizeof(struct Liste));
    
    // Affecter la valeur du nouveau data
    newList->data = newData;
    
    // Définir le prochain pointeur de la nouvelle liste pour qu'il pointe vers l'ancienne liste
    newList->next = List;
    
    // Mettre à jour le pointeur de la liste pour qu'il pointe vers la nouvelle liste
    List = newList;
}


void freeList() {
    // Déclaration d'un pointeur vers une structure Liste nommé "current" et initialisation avec la valeur du pointeur List
    struct Liste* current = List;

    // Boucle tant que le pointeur "current" n'est pas NULL
    while (current != NULL) {
        // Déclaration d'un pointeur vers une structure Liste nommé "next" et initialisation avec la valeur du pointeur next de la structure courante
        struct Liste* next = current->next;

        // Libération de la mémoire occupée par la structure courante
        free(current);

        // Mise à jour du pointeur "current" avec la valeur du pointeur "next" pour passer à la structure suivante
        current = next;
    }
}

// Fonction de rappel pour écrire les données de réponse dans une chaîne
size_t write_callback(void* contents, size_t size, size_t nmemb, char** response) {
    // Calcul de la taille réelle des données reçues
    size_t realsize = size * nmemb;

    // Réallocation de la mémoire pour la réponse
    *response = realloc(*response, realsize + 1);

    // Vérification de l'allocation de mémoire
    if (*response == NULL) {
        printf("Erreur de mémoire lors de l'allocation du tampon de réponse.\n");
        return 0;
    }

    // Copie des données reçues dans le tampon de réponse
    memcpy(*response, contents, realsize);

    // Ajout du caractère de fin de chaîne
    (*response)[realsize] = '\0';

    // Retourne la taille réelle des données reçues
    return realsize;
}



// Fonction de rappel pour écrire les données de réponse dans un fichier
size_t write_callback2(void* contents, size_t size, size_t nmemb, FILE* file) {
	// Le type size_t est un type de données entier non signé qui est défini dans le langage C.
	
    return fwrite(contents, size, nmemb, file);
}



char* read_file(const char* filename) {
    // Ouvrir le fichier en mode lecture
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return NULL;
    }

    // Déterminer la taille du fichier en déplaçant la position du curseur à la fin du fichier
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);  // Réinitialiser la position du curseur au début du fichier

    // Allouer un tampon pour contenir le contenu du fichier, plus un caractère supplémentaire pour le terminateur de chaîne
    char* buffer = (char*)malloc((file_size + 1) * sizeof(char));
    if (buffer == NULL) {
        fclose(file);
        printf("Erreur de mémoire lors de l'allocation du tampon.\n");
        return NULL;
    }

    // Lire le contenu du fichier dans le tampon
    size_t read_size = fread(buffer, sizeof(char), file_size, file);
     if (read_size != (size_t)file_size) {
        printf("Erreur de lecture du fichier.\n");
        free(buffer);
        fclose(file);
        
    }
    
    buffer[file_size] = '\0';  // Ajouter un terminateur de chaîne à la fin du tampon

    fclose(file);

    return buffer;  // Retourner le tampon contenant le contenu du fichier
}




// Fonction qui permet de fermer une fenetre gtk
void close_window(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(data);
   
    
}

// Fonction de rappel qui se declenche lorsque le bouton est cliqué et affichage d'un print dans le Terminal
void on_button_name(GtkButton *button, gpointer user_data) {
    // La fonction de rappel appelée lors du clic sur le bouton.
    // Le paramètre "button" est le bouton qui a été cliqué.
    // Le paramètre "user_data" est un pointeur générique vers des données utilisateur supplémentaires.

    // Cast du pointeur générique "user_data" en un pointeur GtkWidget qui représente un widget d'entrée de texte.
    GtkWidget *entry = GTK_WIDGET(user_data);

    // Récupération du texte saisi dans le widget d'entrée de texte.
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(entry));

    // Affichage du nom saisi.
    g_print("Le nom saisi est : %s\n", name);

    // Vérification si le pointeur "data" est nul.
    if (data == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
    }

    // Écriture du nom dans le fichier pointé par "data".
    fprintf(data, "%s\n", name);
}


// Fonction de rappel qui se declenche lorsque le bouton est cliqué et affichage d'un print dans le Terminal
void on_button_mail(GtkButton *button, gpointer user_data) {
    // Cette fonction est le rappel (callback) pour le clic sur le bouton.

    // Convertit le pointeur générique "user_data" en un pointeur de type GtkWidget
    GtkWidget *entry = GTK_WIDGET(user_data);

    // Récupère le texte saisi dans le widget d'entrée (entry)
    const gchar *mail = gtk_entry_get_text(GTK_ENTRY(entry));

    // Affiche le texte saisi dans la console
    g_print("Le mail saisi est : %s\n", mail);

    // Vérifie si "data" est NULL (non valide)
    if (data == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
    }

    // Écrit le texte saisi dans le fichier "data"
    fprintf(data, "%s\n", mail);
}



int global_result; // Variable globale pour stocker le résultat




void on_button_nbparam(GtkButton *button, gpointer user_data) {
    // Cette fonction est appelée lorsque le bouton est cliqué
    // Elle récupère le widget de l'entrée de texte en tant que gpointer, puis le convertit en GtkWidget
    GtkWidget *entry = GTK_WIDGET(user_data);

    // Récupère le texte de l'entrée de texte en tant que const gchar*
    const gchar *nbparam = gtk_entry_get_text(GTK_ENTRY(entry));

    // Affiche le nombre de paramètres dans la console
    g_print("Le nombre de paramètre est de : %s\n", nbparam);

    // Convertit la chaîne de caractères en entier avec la fonction atoi()
    global_result = atoi(nbparam);

    // Affiche le résultat dans la console
    printf("Le résultat est : %d\n", global_result);

    // Vérifie si "data" est NULL (non initialisé)
    if (data == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
    }

    // Écrit le contenu de "nbparam" dans le fichier pointé par "data"
    fprintf(data, "%s\n", nbparam);
}




void on_button_param(const gchar* tab, gpointer user_data) {
    // Cette fonction est appelée lorsque le bouton est cliqué.
    // La variable "tab" est un paramètre qui peut être passé à cette fonction.
    // La variable "user_data" est un pointeur vers les données utilisateur.
    
    GtkWidget *entry = GTK_WIDGET(user_data);
    // On convertit le pointeur "user_data" en un pointeur de type GtkWidget.
    // Cela nous permet d'accéder à l'objet Entry (zone de saisie) associé.
    
    const gchar* param = gtk_entry_get_text(GTK_ENTRY(entry));
    // On récupère le texte saisi dans la zone de saisie Entry.
    // La fonction gtk_entry_get_text() renvoie une chaîne de caractères de type const gchar*.
    
    g_print("Le nom de parametre est : %s\n", param);
    // On affiche le nom du paramètre à l'aide de la fonction g_print().
    
    addListe(param);
    // On appelle la fonction addListe() en passant le nom du paramètre comme argument.
    // Ici, vous devriez définir cette fonction addListe() pour effectuer l'action souhaitée avec le paramètre.
}


const char *copyurl;


// Fonction de rappel qui se declenche lorsque le bouton est cliqué et affichage d'un print dans le Terminal
void on_button_url(GtkButton *button, gpointer user_data) {
    // Cette fonction est le rappel (callback) pour le clic sur le bouton.

    // Convertit le pointeur générique "user_data" en un pointeur de type GtkWidget
    GtkWidget *entry = GTK_WIDGET(user_data);

    // Récupère le texte saisi dans le widget d'entrée (entry)
    const gchar *url = gtk_entry_get_text(GTK_ENTRY(entry));
	
	
    // Affiche le texte saisi dans la console
    
    g_print("L'url saisi est : %s\n", url);
   

    // Vérifie si "data" est NULL (non valide)
    if (data == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
    }

    // Écrit le texte saisi dans le fichier "data"
    fprintf(data, "%s\n", url);
    
    copyurl = g_strdup(url);
    
   
    
}



void open_window4() {
	
	 if (window1 != NULL) {
        gtk_widget_destroy(window1);
        window1 = NULL;
    }
    
    GtkWidget  *text_view, *scroll_window;
    GtkTextBuffer *buffer;
    gchar *result;
    FILE *file;
    char *file_content;
    long file_size;
    cJSON *json, *results, *recipe, *title,*param ,*calories, *protein, *fat, *carbs;

    // Création de la fenêtre GTK
    gtk_init(NULL, NULL);
    window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window1), "API1.3");
    gtk_window_set_default_size(GTK_WINDOW(window1), 400, 400);
    g_signal_connect(window1, "destroy", G_CALLBACK(gtk_main_quit), NULL);

     // Ouverture et lecture du fichier JSON
    file = fopen("response.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    rewind(file);
    file_content = (char*)malloc((file_size + 1) * sizeof(char));
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
   				
				 // Concaténation des titres de recettes
			const gchar* str1 = "nom de recette : ";
			const gchar* str2 = "Titre de recette : ";
			const gchar* str3 = "calories : ";
			const gchar* str4 = "protein : ";
			const gchar* str5 = "fat: ";
			const gchar* str6 = "carbs : ";
			
			
			result = g_strdup("");
			const gchar* keyName;
			int recipeCount = cJSON_GetArraySize(json);
			
			if (recipeCount > 0) {
				cJSON* lastRecipe = cJSON_GetArrayItem(json, recipeCount - 1);
				cJSON* lastKey = lastRecipe->child;
				while (lastKey != NULL) {
					if (lastKey->type == cJSON_String) {
						keyName = lastKey->string;
						// Traitez ici la clé correspondante
						/*if (g_strcmp0(keyName, str5) == 0) {
						    keyName="\n";
						    break; // Sortir de la boucle si la clé "iron" est trouvée
						}*/
					}
					lastKey = lastKey->next;
				}
			}
			cJSON_ArrayForEach(recipe, json) {
				title = cJSON_GetObjectItem(recipe, "name");
				param = cJSON_GetObjectItem(recipe, keyName);
				
				 if (title != NULL && cJSON_IsString(title)) {
				 	
						if (g_strcmp0(keyName, "image") == 0) {
				
					
						 result = g_strconcat(result,g_strconcat(str1, title->valuestring, "\n", NULL),NULL);
						
						result = g_strconcat(result,"\n", NULL);
			  
			   
					   }else{
								
							result = g_strconcat(result,g_strconcat(str1, title->valuestring, "\n", NULL),NULL);
						   
							gchar* concatenated2 = g_strdup_printf("%s%s", keyName, " : ");
							result = g_strconcat(result,g_strconcat(concatenated2, param->valuestring, "\n", NULL),NULL);
							result = g_strconcat(result,"\n", NULL);
						}
						
					}else{
						
						title = cJSON_GetObjectItem(recipe, "title");
						calories = cJSON_GetObjectItem(recipe, "calories");
						protein = cJSON_GetObjectItem(recipe, "protein");
						fat = cJSON_GetObjectItem(recipe, "fat");
						carbs = cJSON_GetObjectItem(recipe, "carbs");
						param = cJSON_GetObjectItem(recipe, keyName);
						
						if (title != NULL && cJSON_IsString(title)) {
    						if (g_strcmp0(keyName, "carbs") == 0) {
    	
    						
								
								result = g_strconcat(result,g_strconcat(str2, title->valuestring, "\n", NULL),NULL);
								gchar* concatenated = g_strdup_printf("%s%d", "", calories->valueint);
								result = g_strconcat(result,g_strconcat(str3, concatenated, "\n", NULL),NULL);
								result = g_strconcat(result,g_strconcat(str4, protein->valuestring, "\n", NULL),NULL);
								result = g_strconcat(result,g_strconcat(str5, fat->valuestring, "\n", NULL),NULL);
								result = g_strconcat(result,g_strconcat(str6, carbs->valuestring, "\n", NULL),NULL);
								result = g_strconcat(result,"\n", NULL);
							  
							   
						   }else{
									
								result = g_strconcat(result,g_strconcat(str2, title->valuestring, "\n", NULL),NULL);
								gchar* concatenated = g_strdup_printf("%s%d", "", calories->valueint);
								result = g_strconcat(result,g_strconcat(str3, concatenated, "\n", NULL),NULL);
								result = g_strconcat(result,g_strconcat(str4, protein->valuestring, "\n", NULL),NULL);
								result = g_strconcat(result,g_strconcat(str5, fat->valuestring, "\n", NULL),NULL);
								result = g_strconcat(result,g_strconcat(str6, carbs->valuestring, "\n", NULL),NULL);
								gchar* concatenated2 = g_strdup_printf("%s%s", keyName, " : ");
								result = g_strconcat(result,g_strconcat(concatenated2, param->valuestring, "\n", NULL),NULL);
								result = g_strconcat(result,"\n", NULL);
							}
        
    					}
				}}
    }else{
  	

		// Concaténation des titres de recettes
		const gchar* str1 = "Titre de recette : ";
		
		
		result = g_strdup("");
		cJSON_ArrayForEach(recipe, results) {
		    title = cJSON_GetObjectItem(recipe, "title");
		    if (title != NULL && cJSON_IsString(title)) {
		        result = g_strconcat(result,g_strconcat(str1, title->valuestring, "\n", NULL),NULL);
		        result = g_strconcat(result,"\n", NULL);
		    }else{
		    	title = cJSON_GetObjectItem(recipe, "name");
		    	if (title != NULL && cJSON_IsString(title)) {
				    result = g_strconcat(result,g_strconcat(str1, title->valuestring, "\n", NULL),NULL);
				    result = g_strconcat(result,"\n", NULL);
        		}
        			
        			
					
				
        	}
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
    gtk_container_add(GTK_CONTAINER(window1), scroll_window);
    

    // Affichage de la fenêtre et démarrage de la boucle principale GTK
    gtk_widget_show_all(window1);
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
    
    const char *chaine =  strdup(copyurl);
    printf("chaine %s\n", chaine);
    
    
    
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
    
    open_window4();
    
}

void open_window3(GtkButton *button,gpointer user_data){
	if (window1 != NULL) {
        gtk_widget_destroy(window1);
        window1 = NULL;
    }
    
	GtkWidget *vbox10;
    GtkWidget *box5;
    GtkWidget *button13, *button14;
    window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window1), "API1.2");
    gtk_window_set_default_size(GTK_WINDOW(window1), 400, 400);
    g_signal_connect(window1,  "destroy", G_CALLBACK(gtk_main_quit), NULL);
     
    box5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window1), box5);
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox10 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window1), vbox10);
	
    
    // Création du bouton
    button13 = gtk_button_new_with_label("Envoyer");
   	
   
	// Affiche le résultat dans la console
    printf("Le résultat est : %d\n", global_result);
    
    for(int i = 1; i<= global_result;i++){
    	GtkWidget *entry = gtk_entry_new();
    	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Entrez votre parametre ");
    	gtk_box_pack_start(GTK_BOX(box5), entry, TRUE, TRUE, 0);
    	//Pour entrer le nom des parametre 
    	g_signal_connect(G_OBJECT(button13), "clicked", G_CALLBACK(on_button_param), entry);
    	g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    	
    	
   	}
   	
   	
   	gtk_box_pack_start(GTK_BOX(box5), button13, TRUE, TRUE, 0);
	g_signal_connect(button13, "clicked", G_CALLBACK(open_file1), NULL);
	
	
	// Création du bouton
	button14 =  gtk_button_new_with_label("Fermer");
    gtk_box_pack_start(GTK_BOX(box5), button14, TRUE, TRUE, 0);
    g_signal_connect(button14, "clicked", G_CALLBACK(close_window), window1);
    //g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Ajout de la boîte verticale à la deuxième fenêtre
	gtk_container_add(GTK_CONTAINER(window1), vbox10);	
    
    gtk_widget_show_all(window1);
    
}

void open_window2(GtkButton *button,gpointer user_data) {
	 
	 if (window1 != NULL) {
        gtk_widget_destroy(window1);
        window1 = NULL;
    }
    
	GtkWidget *vbox;
    window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window1), "API1");
    gtk_window_set_default_size(GTK_WINDOW(window1), 400, 400);
    //g_signal_connect(window1, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *box;
    GtkWidget *entry;
    GtkWidget  *button1, *button2;
    
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window1), box);
    
    
    
    
   
    
    
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
    //g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
     g_signal_connect(button1, "clicked", G_CALLBACK(open_window3), NULL);
    
    
    button2 = gtk_button_new_with_label("Fermer ");
    gtk_box_pack_start(GTK_BOX(box), button2, TRUE, TRUE, 0);
    
    
    // Création d'une boîte verticale pour contenir le bouton
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window1), vbox);
	
	g_signal_connect(button2, "clicked", G_CALLBACK(close_window), window1);
    
    gtk_widget_show_all(window1);
    
   
    
}

int main(int argc, char *argv[]) {
    GtkWidget *button1,  *button3, *button4;
    GtkWidget *vbox1;
    GtkWidget *box1;
    GtkWidget *entry1, *entry2, *entry3;;
    

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
	//g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	 
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
    
    //Saisi de l'URL
    entry3 = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry3), "Entrez l'URL de l'API");
    gtk_box_pack_start(GTK_BOX(box1), entry3, TRUE, TRUE, 0);
    
    button4 = gtk_button_new_with_label("Valider");
    gtk_box_pack_start(GTK_BOX(box1), button4, TRUE, TRUE, 0);
    
    
    
    // Création des bouton
    button1 = gtk_button_new_with_label("Suivant");
    gtk_box_pack_start(GTK_BOX(box1), button1, TRUE, TRUE, 0);

    

    button3 = gtk_button_new_with_label("Fermer");
    gtk_box_pack_start(GTK_BOX(box1), button3, TRUE, TRUE, 0);
    
    
    // Affichage du nom dans le Terminal
    g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(on_button_name), entry1);
    //g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	
    // Affichage du mail dans le Terminal
    g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(on_button_mail), entry2);
    //g_signal_connect(G_OBJECT(window1), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Affichage de l'url dans le Terminal
    g_signal_connect(G_OBJECT(button4), "clicked", G_CALLBACK(on_button_url), entry3);
    
    
    
    
    g_signal_connect(button1, "clicked", G_CALLBACK(open_window2), NULL);
    
    
    
	
    gtk_box_pack_start(GTK_BOX(vbox1), button1, TRUE, TRUE, 0);
    

    
    
    

   
	
	
	g_signal_connect(button3, "clicked", G_CALLBACK(close_window), window1);
	// g_signal_connect(window1, "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
	
	
	
    gtk_widget_show_all(window1);
    //g_signal_connect(window1,  "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();

    // Fermeture du fichier
    fclose(data);

    return 0;
}



