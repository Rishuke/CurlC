#include <stdio.h>
#include <curl/curl.h>

int main(void)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.thecocktaildb.com/api/json/v1/1/search.php?s=margarita"); // Remplacez l'URL par l'URL de votre base de données
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
