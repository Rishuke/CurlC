#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

int main(int argc, char *argv[])
{
  CURL *curl;
  CURLcode res;
  char chaine1[100] = "https://pokebuildapi.fr/api/v1/pokemon";
  char chaine2[100] = "";
  
  strcat(chaine1,chaine2);
  curl = curl_easy_init();
  if(curl) {
  	
  	for (int i = 1; i < argc; i++) {
        strcat(chaine2,argv[i]);
        
    }
    curl_easy_setopt(curl, CURLOPT_URL, strcat(chaine1,chaine2)); // Remplacez l'URL par l'URL de votre base de données
    //https://www.thecocktaildb.com/api/json/v1/1/search.php?s=margarita
    //"jdbc:mysql://localhost:3306/Meal?user=admin&password=password"
    //https://pokebuildapi.fr/api/v1/pokemon
    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
      fprintf(stderr, "Erreur lors de la requête : %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl);
  }
  
  return 0;
}
