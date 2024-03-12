#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include "utils.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

class SocketServer{
    private:
        int64_t port = -1;
    public:
        SocketServer(int64_t serverPort):port(serverPort){};
        void gotoListenMode();
};