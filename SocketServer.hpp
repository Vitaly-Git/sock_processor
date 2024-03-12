#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include "utils.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
class SocketServer{
    private:
        uint16_t port = -1;
    public:
        SocketServer(uint16_t serverPort):port(serverPort){};
        void gotoListenMode();
};