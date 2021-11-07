#include "Socket.h"
#include "ServerSocket.h"
#include <cstddef>

int main() {
    ServerSocket *ss = new ServerSocket(9100);
    perror("started");
    ss->init();
    delete(ss);
}
