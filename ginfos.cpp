#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <gd.h>
#include <vector>
//#include <string.h>
# include <fstream>
#include<numeric>

/*
/home/jpphi/Downloads/buildroot-2023.08/output/build/libcurl-8.2.1/include/curl/curl.h
/home/jpphi/Downloads/buildroot-2023.08/output/host/aarch64-buildroot-linux-gnu/sysroot/usr/include/curl/curl.h
*/

using namespace std;
using json= nlohmann::json_abi_v3_11_2::json;

double maxTab(vector<double>);

int main()
{
    // curl
    //char url[]= "api.openweathermap.org/data/2.5/weather?lat=43.5283&lon=5.44973&appid=fb7ea3ac85bb67a9bdb0b4b9a51f1c72&units=metric";
    char url[]= "api.open-meteo.com/v1/forecast?latitude=43.5283&longitude=5.4497&hourly=temperature_2m,windspeed_10m,winddirection_10m";

    // json
    char nfichier[]= "rmeteo.json";
    FILE *desc;

    // gd
    long unsigned int COULEUR_FOND= 0x00FFFFFF;
    gdImagePtr im;


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

    fclose(desc);

    curl_easy_cleanup(curl);

    // Ouverture du fichier json
    ifstream flux(nfichier);

    json j;
    flux >>j;

    cout << j["hourly"]["temperature_2m"] ;
    //j.value("hourly","temperature_2m");

    vector<double> temperature2m(j["hourly"]["temperature_2m"]);

    cout << "Taille: " << temperature2m.size();

    double tempmax= maxTab(temperature2m);

    cout << tempmax;


    flux.close();

    //cout << valeur["latitude"];
    int largeur= 800, hauteur= 800;
    im = gdImageCreateTrueColor(largeur, hauteur);
        gdImageFilledRectangle(im, 0, 0, largeur-1, hauteur-1, COULEUR_FOND);




    for(int i=0; i<temperature2m.size()-1; i++)
    {
        double x0=i,y0= temperature2m[i],x1=i+1,y1= temperature2m[i+1];

        //gdImageSetPixel(im,i,hauteur- temperature2m[i],0);
        gdImageLine(im,x0,hauteur - y0,x1,hauteur - y1,0);
        //gdImageFilledRectangle(im, x0, y0, x1, y0 - pourcentage[i], COULEURS[i]);

        //printf("\nx0, y0= %d, %d - x1, y1 %d,%d - pourcentage[%d]= %d larg_h= %d espace== %d\n", x0,y0,x1,y0 - pourcentage[i],i, pourcentage[i], larg_h, espace);

        //x0= x0 + larg_h + espace;
        //x1= x1 + larg_h + espace;
    }




    // Sauvegarde du fichier
    desc= fopen("temperatures.png","w"); // On écrase à chaque fois le précédent relevé

    gdImagePng(im, desc);
    fclose(desc);

    gdImageDestroy(im);

    return 0;

}



double maxTab(vector<double> vt)
{
    double max= - numeric_limits<double>::max();

    for(double v: vt)
    {
        if(v > max)max= v;
    }
    return max;
}


/*
{
"temperature_2m":[]
"time":[]
"winddirection_10m":[]
"windspeed_10m":[]
}
*/

/*

find_package(jsoncpp REQUIRED)

if (jsoncpp_FOUND)
    include_directories(${jsoncpp_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${jsoncpp_LIBRARIES})
endif()



find_package(JSON REQUIRED)

if (JSON_FOUND)
    include_directories(${QJSON_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${QJSON_LIBRARIES})
endif()



find_package(gd)

if (gd_FOUND)
    include_directories(${gd_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${gd_LIBRARIES})
endif()


*/

// INCLUDE
/*
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gd.h>
#include <gdfontl.h>
#include <gdfontt.h>
#include <gdfonts.h>
#include <gdfontmb.h>
#include <gdfontg.h>
#include <math.h>

#define NBPOLICE 5
*/

//void afficheAide(void);
