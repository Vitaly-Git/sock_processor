#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <thread>
#include "Utils.hpp"

class SocketServer{
    private:
        uint16_t port = -1;
        static void proccessIncomeConnection(int incomeSocket, bool disconectAfteRcvData);
    public:
        SocketServer(uint16_t serverPort):port(serverPort){};
        void gotoListenMode();
};