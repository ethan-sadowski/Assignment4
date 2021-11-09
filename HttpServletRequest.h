//
// Created by Ethan on 2021-11-05.
//

#ifndef MULTITHREADEDSERVER_C_HTTPSERVLETREQUEST_H
#define MULTITHREADEDSERVER_C_HTTPSERVLETREQUEST_H

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

/* Represents an HttpServletRequest */
class HttpServletRequest {
private:
    map<string, string> headers;
    vector<char> imageData;
public:
    HttpServletRequest(map<string, string>& headerMap, vector<char>& imageData) : imageData(imageData), headers(headerMap){};
    HttpServletRequest(HttpServletRequest& c) : headers(c.headers), imageData(c.imageData){};
    string getHeader(const string& key) {return this->headers.at(key);}
    void addHeader(const string& key, string& value) {this->headers.insert(make_pair(key, value));}
    vector<char> getImageData() {return this->imageData;}
    ~HttpServletRequest()= default;
};


#endif //MULTITHREADEDSERVER_C_HTTPSERVLETREQUEST_H
