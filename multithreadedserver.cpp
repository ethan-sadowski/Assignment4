#include "Socket.h"
#include "ServerSocket.h"
#include <cstddef>

using namespace std;

int main() {
    int port = 9999;
    ServerSocket *ss = new ServerSocket(port);
    cout << "Server started on port " << port << endl;
    ss->init();
    delete(ss);
}
