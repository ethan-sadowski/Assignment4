#include "ServerSocket.h"
#include "ServerSocket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <stdio.h>

/* Instantiates a ServerSocket */
ServerSocket::ServerSocket(int port)
{
    sock = socket (AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("opening stream socket");
    }
    struct sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind (sock, (struct sockaddr *)&server, sizeof server) < 0) {
        perror ("binding stream socket");
    }
    listen (sock, 5);
}

/* Initializes the server to accept incoming requests */
void ServerSocket::init() {
    socklen_t length = sizeof(sockaddr_in);
    sockaddr_in localAddr, remoteAddr;
    int addrLen = sizeof (remoteAddr);
    int threadCount = 0;
    while(1){
        int cSock = accept(sock, (struct sockaddr *)&remoteAddr, &addrLen);
        threadCount++;
        Thread *thread = new ServerThread(cSock, threadCount);
        thread->start();
    }
}

ServerSocket::~ServerSocket()
{
}