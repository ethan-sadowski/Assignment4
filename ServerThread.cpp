#include <unistd.h>
#include <stdio.h>
#include "ServerThread.h"
#include <string>

ServerThread::ServerThread(int socket, int id):Thread(this, int id) {
    this->socket = socket;
    this->id = id;
}
char* ServerThread::run() {
    int rval;
    char *buf = new char[1024];

    if ((rval = read(socket, buf, 1024)) < 0){
        perror("reading socket");
    }else  {
        printf("%s\n",buf);
    }
    return buf;
}

void ServerThread::closeThread(){
    close(this->socket);
    perror("Thread closed\n\n");
    delete(this);
}

ServerThread::~ServerThread() {
    perror("Thread deleted!");
}
