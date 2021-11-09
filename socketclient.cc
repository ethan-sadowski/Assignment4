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
#include <string>
#include <cassert>
#include <limits>
#include <stdexcept>
#include <cctype>

using namespace std;

const int BLOCK_SIZE = 16 * 1024;
const string CRLF = "\r\n";


vector<unsigned char> getByteArray(const string& filename) {
    ifstream file(filename, ios::binary);

    istream_iterator<unsigned char> begin(file), end;

    vector<unsigned char> buffer(begin, end);

    return buffer;
}



int main() {
    //	Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("opening stream socket");
    }

    // Create a hint structure for the server were connecting with
    int port = 9999;
    // this could be IP address for TOMCAT?
    string ipAddress ="127.0.0.1";
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    // connect to the server on the socket
//    int connectRes = connect(sock,(sockaddr*)&hint, sizeof(hint));
//    if (connectRes == -1) {
//        perror("Cannot connect to the server");
//    }


    char buf[BLOCK_SIZE];
    string userInput;


    vector<unsigned char> fileByteArray;
    fileByteArray = getByteArray("../dog.jpg");
    int imageSize = fileByteArray.size();
    stringstream ss;
    ss << imageSize;
    string sizeString = ss.str();


    string httpString = "POST /photogallery/upload HTTP/1.1" + CRLF +
                        "Host: localhost:8081" + CRLF +
                        "Connection: keep-alive" + CRLF +
                        "Content-Length: " + sizeString + CRLF +
                        "Cache-Control: max-age=0" + CRLF +
                        R"(sec-ch-ua: "Google Chrome";v="93", " Not;A Brand";v="99", "Chromium";v="93")" + CRLF +
                        "sec-ch-ua-mobile: ?0" + CRLF +
                        "sec-ch-ua-platform: \"Windows\"" + CRLF +
                        "Upgrade-Insecure-Requests: 1" + CRLF +
                        "Origin: http://localhost:8081" + CRLF +
                        "Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryQJZ1hukB5Ezq5RXh" + CRLF +
                        "User-Agent: Client" + CRLF +
                        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,/;q=0.8,application/signed-exchange;v=b3;q=0.9" + CRLF +
                        "Sec-Fetch-Site: same-origin" + CRLF +
                        "Sec-Fetch-Mode: navigate" + CRLF +
                        "Sec-Fetch-User: ?1" + CRLF +
                        "Sec-Fetch-Dest: document" + CRLF +
                        "Referer: http://localhost:8081/photogallery/upload?" + CRLF +
                        "Accept-Encoding: gzip, deflate, br" + CRLF +
                        "Accept-Language: en-US,en;q=0.9" + CRLF + CRLF +
                        "------WebKitFormBoundaryQJZ1hukB5Ezq5RXh" + CRLF +
                        "Content-Disposition: form-data; name=\"fileName\"; filename=\"Android.png\"" + CRLF +
                        "Content-Type: image/png" + CRLF + CRLF;

    string httpStringLast = "------WebKitFormBoundaryQJZ1hukB5Ezq5RXh" + CRLF +
                            "Content-Disposition: form-data; name=\"caption\"" + CRLF + CRLF +
                            "test" + CRLF +
                            "------WebKitFormBoundaryQJZ1hukB5Ezq5RXh" + CRLF +
                            "Content-Disposition: form-data; name=\"date\"" + CRLF + CRLF +
                            "2021-11-11" + CRLF +
                            "------WebKitFormBoundaryQJZ1hukB5Ezq5RXh--" +CRLF;


    do {

        // append the byte array image sample to the http string
        vector<unsigned char> fileAppendToHttpString(httpString.size());
        copy(httpString.begin(), httpString.end()-1, fileAppendToHttpString.begin());
        fileAppendToHttpString.insert(fileAppendToHttpString.end(), fileByteArray.begin(), fileByteArray.end());
        fileAppendToHttpString.insert(fileAppendToHttpString.end(), httpStringLast.begin(), httpStringLast.end());

        // appending the caption and dates to the http string

        // send to server
//        int sendRes = send(sock,result.data(), sizeof(result[0])*result.size(), 0);
//        //TODO: check if that failed!
//        if (sendRes == -1) {
//            cout << "Could not send to server! Whoops!\r\n";
//            continue;
//        }


        // wait for response
        memset(buf, 0, 4096);
        int byteReceived = recv(sock, buf, 4096, 0);
        if (byteReceived == -1) {
            cout << "There was an error getting response from server\r\n";
        }
        // Display response
        cout << "SERVER> " << string(buf,byteReceived) << "\r\n";
        // close the socket
    } while(true);

    close(sock);
    return 0;
}
