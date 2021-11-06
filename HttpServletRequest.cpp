//
// Created by Ethan on 2021-11-05.
//

#include <cstring>
#include "HttpServletRequest.h"

void removeEndCharacters(string& inputString) {
    if (inputString[inputString.size() - 1] == '\n' || inputString[inputString.size() - 1] == '\r')  {
        inputString = inputString.substr(0, inputString.size() - 1);
        removeEndCharacters(inputString);
    }
}

void HttpServletRequest::serialize() {
    string method, address, protocol, nextHeader, nextValue;
    getline(this->inputStream, method, ' ');
    getline(this->inputStream, address, ' ');
    getline(this->inputStream, protocol, '\n');
    removeEndCharacters(method);
    removeEndCharacters(address);
    removeEndCharacters(protocol);
    this->headers.insert(make_pair("Method", method));
    this->headers.insert(make_pair("Address", address));
    this->headers.insert(make_pair("Protocol", protocol));
    string boundary, buf;
    bool webKitFound = false;
    while(getline(this->inputStream, nextHeader, ':')) {
        removeEndCharacters(nextHeader);
            if (nextHeader == "Content-Type" && !webKitFound) {
                getline(this->inputStream, nextValue, ';');
                nextValue.erase(0, 1);
                removeEndCharacters(nextValue);
                this->addHeader(nextHeader, nextValue);
                getline(this->inputStream, boundary);
                boundary.erase(0, 10);
                removeEndCharacters(boundary);
                webKitFound = true;
            } else if (strstr(nextHeader.c_str(), boundary.c_str()) && webKitFound) {
                nextHeader.erase(0, 44);
                getline(this->inputStream, nextValue);
                nextValue.erase(0, 1);
                removeEndCharacters(nextValue);
                this->addHeader(nextHeader, nextValue);
                getline(this->inputStream, nextHeader, ':');
                removeEndCharacters(nextHeader);
                getline(this->inputStream, nextValue, '\n');
                removeEndCharacters(nextValue);
                nextValue.erase(0, 1);
                this->addHeader("Content", nextValue);
                cout << this->getHeader("Content-Disposition") << endl;
                break;
            } else {
                getline(this->inputStream, nextValue, '\n');
                nextValue.erase(0, 1);
                removeEndCharacters(nextValue);
                this->addHeader(nextHeader, nextValue);
            }
    }

    if (this->getHeader("Method") == "POST") {
        //Parse post data
    }
}



