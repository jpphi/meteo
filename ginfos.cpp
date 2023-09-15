#include <iostream>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

//#include <string.h>
# include <fstream>



// api.openweathermap.org/data/2.5/weather?lat=43.5283&lon=5.44973&appid=fb7ea3ac85bb67a9bdb0b4b9a51f1c72&units=metric

/*
/home/jpphi/Downloads/buildroot-2023.08/output/build/libcurl-8.2.1/include/curl/curl.h
/home/jpphi/Downloads/buildroot-2023.08/output/host/aarch64-buildroot-linux-gnu/sysroot/usr/include/curl/curl.h
*/

using namespace std;

int main()
{
    //char url[]= "api.openweathermap.org/data/2.5/weather?lat=43.5283&lon=5.44973&appid=fb7ea3ac85bb67a9bdb0b4b9a51f1c72&units=metric";
    char url[]= "api.open-meteo.com/v1/forecast?latitude=43.5283&longitude=5.4497&hourly=temperature_2m,windspeed_10m,winddirection_10m";
    char nfichier[]= "rmeteo.json";
    FILE *desc;
    //ofstream fichier(nfichier);

    desc= fopen(nfichier,"w"); // On écrase à chaque fois le précédent relevé

    CURL *curl= curl_easy_init();
    CURLcode ccode;
    //struct curl_slist *header= NULL;

    if(curl)
    {
        //desc=
        cout << "curl !NULL" << endl;
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL,url);
        //curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, desc);
        //header= curl_slist_append(header, "test");
        //cout << header->data;

        ccode= curl_easy_perform(curl);

        if(ccode== CURLE_OK)
        {
            cout << "CURL OK";
        }

    }


    curl_easy_cleanup(curl);

    // Ouverture du fichier json
    ifstream flux(nfichier);

    //Json::Reader lecteur;
    //Json::Value valeur;

    //lecteur.parse(flux,valeur);

    cout << valeur["latitude"];


    return 0;

}

/*

find_package(jsoncpp REQUIRED)

if (jsoncpp_FOUND)
    include_directories(${jsoncpp_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${jsoncpp_LIBRARIES})
endif()


*/
