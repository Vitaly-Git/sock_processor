#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>

class SocketClient{
    private:
        std::string name;
        uint16_t serverPort = 0;
        uint16_t connectionPeriod = 0;
        void connectToServerSendData();
    public:
        SocketClient(std::string clientName, uint16_t srvPort, uint16_t connPeriod):
                    name(clientName), serverPort(srvPort), connectionPeriod(connPeriod){
            ;
        }
        void sendDataToServer();
};