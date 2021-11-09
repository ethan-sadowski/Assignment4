#pragma once
#include "Thread.h"
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <sstream>
#include <string>
#include <iostream>

/* Represents a ServerThread subclass of Thread */
class ServerThread : public Thread {
public:
    explicit ServerThread(int socket, int id);
    void run() ;
    void closeThread();
    ~ServerThread();
private:
    int socket;
    int id;
};
