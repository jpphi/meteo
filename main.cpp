#include <iostream>
#include <curl/curl.h>

// api.openweathermap.org/data/2.5/weather?lat=43.5283&lon=5.44973&appid=fb7ea3ac85bb67a9bdb0b4b9a51f1c72&units=metric

/*
/home/jpphi/Downloads/buildroot-2023.08/output/build/libcurl-8.2.1/include/curl/curl.h
/home/jpphi/Downloads/buildroot-2023.08/output/host/aarch64-buildroot-linux-gnu/sysroot/usr/include/curl/curl.h
*/

using namespace std;

int main()
{
    CURL *curl= curl_easy_init();
    CURLcode ccode;
    //struct curl_slist Header= NULL;

    if(curl)
    {
        cout << "curl !NULL" << endl;
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL,
            "api.openweathermap.org/data/2.5/weather?lat=43.5283&lon=5.44973&appid=fb7ea3ac85bb67a9bdb0b4b9a51f1c72&units=metric");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        //Header= curl_slist_append()

        ccode= curl_easy_perform(curl);



    }

    curl_easy_cleanup(curl);
    return 0;

}
