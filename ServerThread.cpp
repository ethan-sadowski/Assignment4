#include <winsock2.h>
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
}

void ServerThread::run() {
    int rval;
    stringstream req, res;
    char *buf = new char[1024];

    if ((rval = read(socket, buf, 1024)) < 0){
        perror("reading socket");
    } else {
        req << buf;
    }
    HttpServletRequest *httpRequest = new HttpServletRequest(req);
    HttpServletResponse *httpResponse = new HttpServletResponse(res);
    httpRequest->serialize();
    httpCall(*httpRequest, *httpResponse);
    cout << sizeof(httpResponse->getResponse()) << endl;
    send(socket, httpResponse->getResponse().str().c_str(), strlen(httpResponse->getResponse().str().c_str()), 0);
    delete (httpRequest);
    delete (httpResponse);
    delete[] (buf);
}

ServerThread::~ServerThread() {
    cout << "Thread " << this->id << " deleted" << endl;
    free(this);
}
