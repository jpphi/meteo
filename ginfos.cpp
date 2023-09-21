/// \brief Projet AJC - Linux embarqué
/// \author Jean-Pierre Maffre
/// \date 20 Septembre 2023
/// \bug Ne se compile pas sur QT creator (problème d'intégration de la librairie gd)

#include <iostream>
# include <fstream>

#include <vector>
#include <string>
#include<numeric>

#include <curl/curl.h>

#include <nlohmann/json.hpp>

#include <gd.h>
#include <gdfontmb.h>


using namespace std;
using json= nlohmann::json_abi_v3_11_2::json;

double maxTab(vector<double>);

double minTab(vector<double>);

//unsigned char * int_unsigned_char(int);

int main()
{
    /// \brief url de l'api
    char url[]= "api.open-meteo.com/v1/forecast?latitude=43.5283&longitude=5.4497&hourly=temperature_2m,windspeed_10m,winddirection_10m";

    /// \brief Paramètre de l'image (hauteur, largeur et couleur de fond
    const unsigned int hauteur= 800, largeur= 800;
    const long unsigned int couleur_fond= 0x00D0EAFF;
    const long unsigned int couleur_trace= 0x000000FF;
    const long unsigned int couleur_echelle= 0x00808080;

    gdImagePtr im;

    /// Fichier json qui sera généré
    char njson[]= "rmeteo.json";

    FILE *desc;

    desc= fopen(njson,"w"); // On écrase à chaque fois le précédent relevé

    /// \brief Récupération des données
    CURL *curl= curl_easy_init();
    CURLcode ccode;

    if(curl)
    {
        cout << "curl !NULL" << endl;
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL,url);
        //curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, desc);

        ccode= curl_easy_perform(curl);

        if(ccode== CURLE_OK)
        {
            cout << "CURL OK";
        }

    }

    fclose(desc);

    curl_easy_cleanup(curl);

    /// \brief Ouverture du fichier json (utilisation de ifstream plutôt que fopen)
    ifstream flux(njson);

    json j;
    flux >>j;

    cout << j["hourly"]["temperature_2m"] << endl;

    vector<double> temperature2m(j["hourly"]["temperature_2m"]);

    cout << "Taille: " << temperature2m.size() << endl;

    double tempmax= maxTab(temperature2m);
    double tempmin= minTab(temperature2m);

    cout << "T° max: " << tempmax << "T° min: " << tempmin << endl;

    flux.close();

    /// \brief Création d'un fichier png
    im = gdImageCreateTrueColor(largeur, hauteur);

    gdImageFilledRectangle(im, 0, 0, largeur-1, hauteur-1, couleur_fond);


    double margel= (double)largeur / 20, margeh= (double)hauteur/20;
    unsigned int taille= temperature2m.size();
    double pasl= (largeur- 2 * margel)/taille;
    double a= (2*margeh - hauteur)/(tempmax-tempmin);
    double b= margeh - a * tempmax;

    for(int i=0; i<taille-1; i++)
    {
        double x0= margel+i*pasl, x1= margel + (i+1) * pasl;
        double y0= a * temperature2m[i] + b;
        double y1= a * temperature2m[i+1] + b;

        //gdImageSetPixel(im,i,hauteur- temperature2m[i],0);
        gdImageLine(im,x0, y0,x1, y1, couleur_trace);
        //gdImageFilledRectangle(im, x0, y0, x1, y0 - pourcentage[i], COULEURS[i]);

        //printf("\nx0, y0= %d, %d - x1, y1 %d,%d - pourcentage[%d]= %d larg_h= %d espace== %d\n", x0,y0,x1,y0 - pourcentage[i],i, pourcentage[i], larg_h, espace);

        //x0= x0 + larg_h + espace;
        //x1= x1 + larg_h + espace;
    }

    /// \brief dessiner une échelle et la graduer
    int bas= (int)tempmin, ht= (int)(tempmax+1);
    //int ecart= ( (ht-bas)%2==0 )
    for(int t= bas; t< ht; t++)
    {
        double li= a * t + b;
        gdImageLine(im, margel, li, largeur - margel, li, couleur_echelle);

        string st= to_string(t);
        char ch[st.size()+1];
        unsigned char uch[st.size()+1];
        int i;
        for(i= 0; i < st.size(); i++)ch[i]= (char)(st[i]);
        ch[i]= 0;
        for(int i= 0; i < st.size(); i++)uch[i]= (unsigned char)(st[i]);
        uch[i]= 0;

        gdImageString(im, gdFontMediumBold, gdFontMediumBold->w , li - gdFontMediumBold->h/2 ,
                      uch, 0x00000000);
    }



    // Sauvegarde du fichier
    desc= fopen("temperatures.png","w"); // On écrase à chaque fois le précédent relevé

    gdImagePng(im, desc);
    fclose(desc);

    gdImageDestroy(im);

    return 0;

}


/// \brief Retourne le maximum d'un tableau vector
/// \param vt Tableau (vector) de double
/// \return Le maximum du tableau
double maxTab(vector<double> vt)
{
    double max= -numeric_limits<double>::max();

    for(double v: vt)
    {
        if(v > max)max= v;
    }
    return max;
}

/// \brief Retourne le minimum d'un tableau vector
/// \param vt Tableau (vector) de double
/// \return Le minimum du tableau
double minTab(vector<double> vt)
{
    double m= numeric_limits<double>::max();

    for(double v: vt)
    {
        if(v < m)m= v;
    }
    return m;
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
