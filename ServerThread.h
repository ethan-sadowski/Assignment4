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


class ServerThread : public Thread {
public:
    explicit ServerThread(int socket, int id);
    void run() ;
    ~ServerThread();
private:
    int socket;
    int id;
};
