#include <iostream>
#include <curl/curl.h>

using namespace std;

int main()
{
    CURL *curl= curl_easy_init();
    CURLcode ccode;

    if(curl)
    {
        cout << "Hello World!" << endl;
    }
    return 0;
}
