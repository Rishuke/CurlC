#include <stdio.h>
#include <curl/curl.h>

int main(void)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://jsonplaceholder.typicode.com/posts/1"); // Remplacez l'URL par l'URL de votre base de données
    
    //"jdbc:mysql://localhost:3306/Meal?user=admin&password=password"
    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
      fprintf(stderr, "Erreur lors de la requête : %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl);
  }
  
  return 0;
}
