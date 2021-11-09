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


int sendData(int sckt, const void *data, int datalen)
{
    const char *ptr = static_cast<const char*>(data);
    while (datalen > 0) {
        int bytes = send(sckt, ptr, datalen, 0);
        if (bytes <=0) return -1;
        ptr += bytes;
        datalen -= bytes;
    }
    return 0;
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

//     connect to the server on the socket
    int connectRes = connect(sock,(sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1) {
        perror("Cannot connect to the server");
    }


    char buf[BLOCK_SIZE];

    string file, caption, date;
    cout << "Enter an image file name (with the tyoe extension), caption and date (YYYY-MM-DD) to upload" << endl;
    cout << "The image you wish to upload must be in the same directory as this executable" << endl;
    cin >> file >> caption >> date;
    cout << "Executing file upload" << endl;
    std::ifstream fin(file, std::ios::in | std::ios::binary);
    std::ostringstream oss;
    oss << fin.rdbuf();
    std::string data(oss.str());

    string firstWebKit = "------WebKitFormBoundaryQJZ1hukB5Ezq5RXh" + CRLF +
                         "Content-Disposition: form-data; name=\"fileName\"; filename=\"" + file + "\"" + CRLF +
                         "Content-Type: image/png" + CRLF + CRLF;

    string httpStringLast = "------WebKitFormBoundaryQJZ1hukB5Ezq5RXh" + CRLF +
                            "Content-Disposition: form-data; name=\"caption\"" + CRLF + CRLF +
                            caption + CRLF +
                            "------WebKitFormBoundaryQJZ1hukB5Ezq5RXh" + CRLF +
                            "Content-Disposition: form-data; name=\"date\"" + CRLF + CRLF +
                            date + CRLF +
                            "------WebKitFormBoundaryQJZ1hukB5Ezq5RXh--" + CRLF;

    int imageSize = data.size() + httpStringLast.size() + firstWebKit.size();
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
                        "Accept-Language: en-US,en;q=0.9" + CRLF + CRLF;

    httpString.append(firstWebKit);

    int totalSize = httpString.size() + data.size() + httpStringLast.size();
    string output = httpString + data + httpStringLast;

    sendData(sock, output.c_str(), totalSize);
    // wait for response
    memset(buf, 0, 4096);
    int byteReceived = recv(sock, buf, 4096, 0);
    if (byteReceived == -1) {
        cout << "There was an error getting response from server\r\n";
    }
    // Display response
    cout << '\n' << string(buf,byteReceived) << "\r\n";
    // close the socket

    close(sock);
    return 0;
}
