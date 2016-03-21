#ifndef __LIBCURL_WRAPPER_H__
#define __LIBCURL_WRAPPER_H__

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <map>

using namespace std;

class Libcurl_Wrapper
{
public:
    CURL* curl;
    CURLcode res;
    Libcurl_Wrapper();
    ~Libcurl_Wrapper();
    
    string get(string &url);
    string get(string &url, map<string, string> &params);
    string get(string &url, map<string, int> &params);
    string get(string &url, map<int, string> &params);
    string get(string &url, map<int, int> &params);
    string post(string &url, string &data);
    string post(string &url, map<string, string> &params);
    string post(string &url, map<string, string> &params, map<string, string> &headers_map);

    inline unsigned int  HttpStatus() const { 
        return http_status; 
    }

    struct postData
    {
        const char *readptr;
        long sizeleft;
    };

private:
    unsigned int http_status;
};

#endif