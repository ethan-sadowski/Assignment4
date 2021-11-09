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

/* Routes HTTP requests to either the doPost or doGet method of httpServlet */
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

/* Parses HTTP headers from the socket stream */
void parseHttpHeaders(map<string, string>& headers, int socket) {
    char buf[1];
    char skip[1];
    vector<char> image;
    bool run = true;
    string length, method, agent, filename, caption, date, nextString;
    while (run) {
        read(socket, buf, 1);

        /* Adds the Method header */
        if (nextString == "GET") {
            headers.insert(make_pair("Method", nextString));
            nextString = "";
        } else if (nextString == "POST") {
            headers.insert(make_pair("Method", nextString));
            nextString = "";

            /* Adds the content length header */
        } else if (nextString == "Content-Length:") {
            nextString = "";
            read(socket, buf, 1);
            nextString.push_back(buf[0]);
            while (buf[0] != ' ' && buf[0] != '\r' && buf[0] != '\n') {
                read(socket, buf, 1);
                nextString.push_back(buf[0]);
            }
            headers.insert(make_pair("Content-Length", nextString));
            nextString = "";

            /* Adds the User-Agent header */
        } else if (nextString == "User-Agent:") {
            nextString = "";
            read(socket, buf, 1);
            nextString.push_back(buf[0]);
            while (buf[0] != ' ' && buf[0] != '\r' && buf[0] != '\n') {
                read(socket, buf, 1);
                nextString.push_back(buf[0]);
            }
            headers.insert(make_pair("User-Agent", nextString));
            nextString = "";
        } else if (buf[0] == '\n' && nextString[0] != '\r') {
            nextString = "";

        /* Adds the Accept-Language header, this is used to identify the end of the headers */
        } else if (nextString == "Accept-Language:") {
            for (int k = 0; k < 14; k++) {
                read(socket, skip, 1);
            }
            nextString = "";
        } else {
            nextString.push_back(buf[0]);
            if ( nextString == "\r\n\r\n") {
                run = false;
                break;
            }
        }
    }
}

/* A helper function used to match strings and identify where the stream currently is */
void incrementSearchString(string& searchString, char newChar) {
    for (int i = 1; i < searchString.size(); i++) {
        searchString[i - 1] = searchString[i];
    }
    searchString[searchString.size() - 1] = newChar;
}

/* Gets the bytes and form submission data from the file upload */
void getBytes(map<string, string>& headers, vector<char>& image, int socket) {
    int length = atoi(headers.at("Content-Length").c_str());
    string next, boundary, date, caption, filename;
    vector<char> imageData;
    int readBytes;
    char imageBuffer[length];
    int bytes, boundaryRep = 0;

    /* Reads the image bytes for a length equal to the number of bytes represented by the Content-Length header */
    while (bytes < length) {
        readBytes = read(socket, imageBuffer + bytes, length - bytes);
        bytes += readBytes;
    }
    for(char byte : imageBuffer) {
        imageData.push_back(byte);
    }

    /* Parses the filename, caption and date from the image Content-Disposition fields */
    string buf = "ZZZZZZZZZZ";
    bool getFileName = false;
    for (char & i : imageData) {
        incrementSearchString(buf, i);
        if (getFileName) {
            if (i != '"') {
                filename += i;
            } else {
                headers.insert(make_pair("Filename", filename));
                buf = "ZZZZ";
                getFileName = false;
            }
        } else if (boundaryRep == 0) {
            if (buf == "filename=\"") {
                getFileName = true;
            }
            if (buf == "\r\n\r\n") {
                boundaryRep++;
            }
        } else if (boundaryRep == 1) {
            if (buf == "\r\n\r\n") {
                boundaryRep++;
                image.pop_back();
                image.pop_back();
                image.pop_back();
            } else {
                image.push_back(i);
            }
        } else if (boundaryRep == 2) {
            if (i != '\r' && i != '\n') {
                caption += i;
            } else {
                headers.insert(make_pair("Caption", caption));
                boundaryRep++;
            }
        } else if (boundaryRep == 3) {
            if (buf == "\r\n\r\n") {
                boundaryRep++;
            }
        } else if (boundaryRep == 4) {
            if (date.size() < 10) {
                date += i;
            } else {
                headers.insert(make_pair("Date", date));
                break;
            }
        }
    }
}

/* Runs the thread */
void ServerThread::run() {
    stringstream res;
    map<string, string> headers;
    vector<char> image;

    /* Get all the headers from the incoming request */
    cout << "Parsing Headers" << endl;
    parseHttpHeaders(headers, socket);
    if (headers.at("Method") == "POST") {
        getBytes(headers, image, socket);
    }

    /* Create a servlet request and response */
    HttpServletRequest *httpRequest = new HttpServletRequest(headers, image);
    HttpServletResponse *httpResponse = new HttpServletResponse(res);
//    httpRequest->serialize();

    /* Call either the doPost or doGet method based on the incoming request */
    cout << "Performing doGet/doPost" << endl;
    httpCall(*httpRequest, *httpResponse);

    cout << "Writing Response to Client" << endl;
    write(socket, httpResponse->getResponse().str().c_str(), strlen(httpResponse->getResponse().str().c_str()));
    delete (httpRequest);
    delete (httpResponse);
}

void ServerThread::closeThread() {
    close(socket);
    delete(this);
}

ServerThread::~ServerThread() {
    cout << "Thread " << this->id << " deleted" << endl;
    close(socket);
}
