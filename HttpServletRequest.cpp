//
// Created by Ethan on 2021-11-05.
//

#include "HttpServletRequest.h"

void HttpServletRequest::serialize() {
    string method, address, protocol, nextHeader, nextValue;
    getline(this->inputStream, method, ' ');
    getline(this->inputStream, address, ' ');
    getline(this->inputStream, protocol, '\n');
    this->headers.insert(make_pair("Method", method));
    this->headers.insert(make_pair("Address", address));
    this->headers.insert(make_pair("Protocol", protocol));

    while(getline(this->inputStream, nextHeader)) {
        getline(this->inputStream,nextValue, '\n');
        nextValue.erase(0, 1);
        if (nextHeader.find("\r\n\r\n") || nextValue.find("\r\n\r\n")) {
            break;
        }
        this->headers.insert(make_pair(nextHeader, nextValue));
    }
// Use to test what headers have been added
//    for (map<string, string>::iterator it = this->headers.begin(); it != this->headers.end(); ++it) {
//        cout << it->first << it->second << endl;
//    }

    if (this->headers.at("Method") == "POST") {
        //Parse post data
    }
}


