//
// Created by steve on 11/8/2021.
//

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <sstream>
#include <iterator>
#include <fstream>
#include <vector>

using namespace std;

const int BLOCK_SIZE = 16 * 1024;


int main() {
    string CRLF = "\r\n";
    //    Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("opening stream socket");
    }

//    ifstream file("../Cat03.jpg", ios::binary);
//    istream_iterator<unsigned char> begin(file), end;
//    vector<unsigned char> buffer(begin, end);

    // Create a hint structure for the server were connecting with
    int port = 8081;
    // this could be IP address for TOMCAT?
    string ipAddress ="127.0.0.1";
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    // connect to the server on the socket
    int connectRes = connect(sock,(sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1) {
        return 1;
    }

    string httpString = "POST /photogallery/upload HTTP/1.1" + CRLF +
                        "Host: localhost:8081" + CRLF +
                        "Connection: keep-alive" + CRLF +
                        "Content-Length: 279989" + CRLF +
                        "Cache-Control: max-age=0" + CRLF +
                        R"(sec-ch-ua: "Google Chrome";v="93", " Not;A Brand";v="99", "Chromium";v="93")" + CRLF +
                        "sec-ch-ua-mobile: ?0" + CRLF +
                        "sec-ch-ua-platform: \"Windows\"" + CRLF +
                        "Upgrade-Insecure-Requests: 1" + CRLF +
                        "Origin: http://localhost:8081" + CRLF +
                        "Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryQJZ1hukB5Ezq5RXh" + CRLF +
                        "User-Agent: Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.54 Mobile Safari/537.36" + CRLF +
                        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,/;q=0.8,application/signed-exchange;v=b3;q=0.9" + CRLF +
                        "Sec-Fetch-Site: same-origin" + CRLF +
                        "Sec-Fetch-Mode: navigate" + CRLF +
                        "Sec-Fetch-User: ?1" + CRLF +
                        "Sec-Fetch-Dest: document" + CRLF +
                        "Referer: http://localhost:8081/photogallery/upload?" + CRLF +
                        "Accept-Encoding: gzip, deflate, br" + CRLF +
                        "Accept-Language: en-US,en;q=0.9" + CRLF + CRLF +
                        "------WebKitFormBoundaryQJZ1hukB5Ezq5RXh" + CRLF +
                        "Content-Disposition: form-data; name=\"fileName\"; filename=\"testing.txt\"" + CRLF +
                        "Content-Type: text/plain" + CRLF + CRLF +
                        "test test test" + CRLF +

                        //    int sendRes = send(sock,httpString.c_str(), httpString.size() + 1, 0);
                        //    FILE *f = fopen("../Cat03.jpg", "r");
                        //    char buffer[2] = "";
                        //    int len;
                        //    while ((len = fread(buffer, sizeof(buffer), 1, f)) > 0) {
                        //        send(sock, buffer, sizeof(buffer), 0);
                        //    }

                        "------WebKitFormBoundaryQJZ1hukB5Ezq5RXh" + CRLF +
                        "Content-Disposition: form-data; name=\"caption\"" + CRLF + CRLF +
                        "test" + CRLF +
                        "------WebKitFormBoundaryQJZ1hukB5Ezq5RXh" + CRLF +
                        "Content-Disposition: form-data; name=\"date\"" + CRLF + CRLF +
                        "2021-11-11" + CRLF +
                        "------WebKitFormBoundaryQJZ1hukB5Ezq5RXh--" +CRLF;
    //int sendRes2 = send(sock,httpString2.c_str(), httpString2.size() + 1, 0);
    int sendRes2 = send(sock,httpString.c_str(), httpString.size() + 1, 0);

    /*
     *  private byte[] formData(String name, String value) {
        String formData = "------WebKitFormBoundaryQJZ1hukB5Ezq5RXh" + CRLF +
                "Content-Disposition: form-data; name=\"" + name + "\"" + CRLF + CRLF +
                value + CRLF;
        return formData.getBytes();
    }
     */

    // send to server


    char buf[BLOCK_SIZE];
    string userInput;


    close(sock);
    return 0;
}
