
#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

int main() {
    FILE* file = fopen("response.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return 1;
    }

    // Obtention de la taille du fichier
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocation d'un tampon pour stocker les données du fichier
    char* buffer = (char*)malloc((file_size + 1) * sizeof(char));
    if (buffer == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
        fclose(file);
        return 1;
    }

    // Lecture des données du fichier dans le tampon
    size_t read_size = fread(buffer, sizeof(char), file_size, file);
    if (read_size != (size_t)file_size) {
        printf("Erreur de lecture du fichier.\n");
        free(buffer);
        fclose(file);
        return 1;
    }
    buffer[file_size] = '\0'; // Ajout du caractère de fin de chaîne

    // Fermeture du fichier
    fclose(file);

    // Analyse du JSON à partir du tampon
    cJSON* root = cJSON_Parse(buffer);
    if (root) {
        cJSON* results = cJSON_GetObjectItem(root, "results");
        int results_count = cJSON_GetArraySize(results);

        for (int i = 0; i < results_count; ++i) {
            cJSON* result = cJSON_GetArrayItem(results, i);
            cJSON* title = cJSON_GetObjectItem(result, "title");
            cJSON* name = cJSON_GetObjectItem(result, "name");
            cJSON* nutrients = cJSON_GetObjectItem(cJSON_GetObjectItem(result, "nutrition"), "nutrients");
            int nutrients_count = cJSON_GetArraySize(nutrients);
			 printf("Title: %s\n", name->valuestring);
            printf("Title: %s\n", title->valuestring);
           
            for (int j = 0; j < nutrients_count; ++j) {
                cJSON* nutrient = cJSON_GetArrayItem(nutrients, j);
                cJSON* name = cJSON_GetObjectItem(nutrient, "name");
                cJSON* amount = cJSON_GetObjectItem(nutrient, "amount");
                cJSON* unit = cJSON_GetObjectItem(nutrient, "unit");

                printf("Nutrient: %s, Amount: %.4f %s\n", name->valuestring, amount->valuedouble, unit->valuestring);
            }
        }

        cJSON_Delete(root);
    } else {
        printf("Erreur d'analyse du JSON.\n");
    }

    // Libération de la mémoire allouée pour le tampon
    free(buffer);

    return 0;
}
