#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

int main() {
    const char* json_data = R"(
        {
  "results": [
    {
      "id": 654959,
      "title": "Pasta With Tuna",
      "image": "https://spoonacular.com/recipeImages/654959-312x231.jpg",
      "imageType": "jpg",
      "nutrition": {
        "nutrients": [
          {
            "name": "Fat",
            "amount": 10.3185,
            "unit": "g"
          }
        ]
      }
    },
    {
      "id": 654857,
      "title": "Pasta On The Border",
      "image": "https://spoonacular.com/recipeImages/654857-312x231.jpg",
      "imageType": "jpg",
      "nutrition": {
        "nutrients": [
          {
            "name": "Fat",
            "amount": 19.8995,
            "unit": "g"
          }
        ]
      }
    },
    {
      "id": 654926,
      "title": "Pasta With Gorgonzola Sauce",
      "image": "https://spoonacular.com/recipeImages/654926-312x231.jpg",
      "imageType": "jpg",
      "nutrition": {
        "nutrients": [
          {
            "name": "Fat",
            "amount": 24.5836,
            "unit": "g"
          }
        ]
      }
    },
    {
      "id": 654944,
      "title": "Pasta With Salmon Cream Sauce",
      "image": "https://spoonacular.com/recipeImages/654944-312x231.jpg",
      "imageType": "jpg",
      "nutrition": {
        "nutrients": [
          {
            "name": "Fat",
            "amount": 14.547,
            "unit": "g"
          }
        ]
      }
    },
    {
      "id": 654901,
      "title": "Pasta With Chicken and Broccoli",
      "image": "https://spoonacular.com/recipeImages/654901-312x231.jpg",
      "imageType": "jpg",
      "nutrition": {
        "nutrients": [
          {
            "name": "Fat",
            "amount": 24.1358,
            "unit": "g"
          }
        ]
      }
    },
    {
      "id": 654935,
      "title": "Pasta with Peas and Italian Sausage",
      "image": "https://spoonacular.com/recipeImages/654935-312x231.jpg",
      "imageType": "jpg",
      "nutrition": {
        "nutrients": [
          {
            "name": "Fat",
            "amount": 11.8876,
            "unit": "g"
          }
        ]
      }
    },
    {
      "id": 654897,
      "title": "Pasta With Butternut Parmesan Sauce @ Dw Magazine.Com",
      "image": "https://spoonacular.com/recipeImages/654897-312x231.jpg",
      "imageType": "jpg",
      "nutrition": {
        "nutrients": [
          {
            "name": "Fat",
            "amount": 18.805,
            "unit": "g"
          }
        ]
      }
    }
  ],
  "offset": 0,
  "number": 7,
  "totalResults": 94
}
    )";

    // Parse le JSON
    cJSON* json = cJSON_Parse(json_data);
    if (json == NULL) {
        printf("Erreur de parsing JSON.\n");
        return 1;
    }

    // Accède à l'objet "results" contenant les données des recettes
    cJSON* results = cJSON_GetObjectItem(json, "results");
    if (results == NULL || !cJSON_IsArray(results)) {
        printf("Erreur lors de l'accès aux résultats des recettes.\n");
        cJSON_Delete(json);
        return 1;
    }

    // Parcourt les recettes et extrait les titres
    cJSON* recipe;
    cJSON_ArrayForEach(recipe, results) {
        cJSON* title = cJSON_GetObjectItem(recipe, "title");
        if (title != NULL && cJSON_IsString(title)) {
            printf("Titre de recette : %s\n", title->valuestring);
        }
    }

    // Nettoyage
    cJSON_Delete(json);

    return 0;
}

