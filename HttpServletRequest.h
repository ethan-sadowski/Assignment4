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

class HttpServletRequest {
private:
    stringstream& inputStream;
    map<string, string> headers;
public:
    explicit HttpServletRequest(stringstream& ss) : inputStream(ss){};
    HttpServletRequest(HttpServletRequest& c) : inputStream(c.inputStream), headers(c.headers){};
    void serialize();
    string getHeader(const string& key) {return this->headers.at(key);}
    ~HttpServletRequest()= default;
};


#endif //MULTITHREADEDSERVER_C_HTTPSERVLETREQUEST_H
