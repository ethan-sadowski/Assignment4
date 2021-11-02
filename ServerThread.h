#pragma once
#include "Thread.h"
#include <cstdio>
#include <cstdlib>
#include <pthread.h>

class ServerThread : public Thread {
public:
    explicit ServerThread(int socket, int id);
    char* run() ;
    void closeThread();
    ~ServerThread();
private:
    int socket;
    int id;
};
