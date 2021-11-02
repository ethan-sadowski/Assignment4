#pragma once

#include "ServerThread.h"

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

