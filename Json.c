#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

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

int main() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl) {
        char* response = NULL;

        // Configuration de l'URL de l'API
        curl_easy_setopt(curl, CURLOPT_URL, "https://pokebuildapi.fr/api/v1/pokemon/type");

        // Configuration de la fonction de rappel pour écrire la réponse dans une chaîne
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Exécution de la requête
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            printf("Erreur lors de l'exécution de la requête : %s\n", curl_easy_strerror(res));
        } else {
            // Affichage de la réponse
            printf("Réponse de l'API :\n%s\n", response);
        }

        // Nettoyage
        free(response);
        curl_easy_cleanup(curl);
    } else {
        printf("Erreur lors de l'initialisation de cURL.\n");
    }

    curl_global_cleanup();

    return 0;
}
