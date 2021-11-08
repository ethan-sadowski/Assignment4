#include <cstring>
#include <sys/socket.h>
#include <mutex>
#include "ServerThread.h"
#include "HttpServletRequest.h"
#include "HttpServletResponse.h"
#include "HttpServlet.h"
#include "UploadServlet.h"

using namespace std;

ServerThread::ServerThread(int socket, int id):Thread(this) {
    this->socket = socket;
    this->id = id;
    cout << "Thread " << this->id << " opened" << endl;
}

void httpCall(HttpServletRequest& req, HttpServletResponse& res) {
    HttpServlet *httpServlet = new UploadServlet();
    if (req.getHeader("Method") == "GET") {
        httpServlet->doGet(req, res);
    }

    if (req.getHeader("Method") == "POST") {
        httpServlet->doPost(req, res);
    }
    delete(httpServlet);
}

void parseHttpHeaders(map<string, string>& headers, int socket) {
    char nextChar;
    char buf[40000];
    char *nextElement = buf;
    size_t bReceived = recv(socket, buf, 40000, 0);
    string length, method, agent, filename;
    while(*nextElement != ' ' && nextElement != NULL) {
        nextChar = *nextElement;
        method.push_back(nextChar);
        nextElement++;
    }
    headers.insert(make_pair("Method", method));

    nextElement = strstr(buf, "User-Agent");
    nextElement = nextElement + 12;
    while(*nextElement != '\n' && *nextElement != '\r') {
        nextChar = *nextElement;
        agent.push_back(nextChar);
        nextElement++;
    }
    headers.insert(make_pair("User-Agent", agent));


    if (method == "POST") {
        nextElement = strstr(buf, "Content-Length");
        nextElement = nextElement + 16;
        while(*nextElement != '\n' && *nextElement != '\r') {
            nextChar = *nextElement;
            length.push_back(nextChar);
            nextElement++;
        }
        headers.insert(make_pair("Content-Length", length));
    }

    //Content disposition can be grabbed here

    nextElement = strstr(buf, "\r\n\r\n");
    nextElement = nextElement + 4;
    if (headers.at("Method") == "POST") {
        int imgSize = atoi(length.c_str());
        if (bReceived > atoi(length.c_str())) {
            nextElement = strstr(buf, "filename");
            nextElement = nextElement + 10;
            while(*nextElement != 34) {
                nextChar = *nextElement;
                filename.push_back(nextChar);
                nextElement++;
            }
            nextElement = strstr(buf, "g\r\n\r\n");
            nextElement = nextElement + 5;
            int imageSize = atoi(length.c_str());
//            int imageSize = 5406;
            char image[imageSize];
            int count = 0;
            string file = "../Images/test.jpg";
//            string savedFile = file.append(filename);
            std::ofstream out;
            out.open(file, std::ofstream::binary | std::ofstream::trunc | std::ofstream::out);
            while (imageSize > 0) {
                out.write(nextElement, sizeof(nextElement));
                nextElement++;
                imageSize -=1;
                count++;
            }

            out.write(image, sizeof(imageSize));
            out.close();
        }
    }
}

void ServerThread::run() {
    mutex mtx;
    int rval;
    vector<char*> imageData;
    stringstream req, res;
    string next;
    map<string, string> headers;
    mtx.lock();
    parseHttpHeaders(headers, socket);


    HttpServletRequest *httpRequest = new HttpServletRequest(headers, imageData);
    HttpServletResponse *httpResponse = new HttpServletResponse(res);
//    httpRequest->serialize();
    httpCall(*httpRequest, *httpResponse);
    write(socket, httpResponse->getResponse().str().c_str(), strlen(httpResponse->getResponse().str().c_str()));
    mtx.unlock();
    close(socket);
    delete (httpRequest);
    delete (httpResponse);
    delete(this);
}

ServerThread::~ServerThread() {
    cout << "Thread " << this->id << " deleted" << endl;
}