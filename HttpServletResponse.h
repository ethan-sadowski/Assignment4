//
// Created by Ethan on 2021-11-05.
//

#ifndef MULTITHREADEDSERVER_C_HTTPSERVLETRESPONSE_H
#define MULTITHREADEDSERVER_C_HTTPSERVLETRESPONSE_H

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

class HttpServletResponse {
private:
    stringstream& outputStream;
    map<string, string> headers;
public:
    explicit HttpServletResponse(stringstream& ss) : outputStream(ss){};
    HttpServletResponse(HttpServletResponse& c) : outputStream(c.outputStream), headers(c.headers){};
    string getHeader(const string& key) {return this->headers.at(key);}
    void print(const string& output){outputStream << output;}
    stringstream& getResponse(){return this->outputStream;}
    ~HttpServletResponse()= default;
};


#endif //MULTITHREADEDSERVER_C_HTTPSERVLETRESPONSE_H
