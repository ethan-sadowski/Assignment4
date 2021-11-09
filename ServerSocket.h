#pragma once

#include "ServerThread.h"

/* Represents a ServerSocket */
class ServerSocket
{
public:
    ServerSocket(int port);
    ServerThread* Accept();
    ~ServerSocket();
    void init();
private:
    int sock;
};

