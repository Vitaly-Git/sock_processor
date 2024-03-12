#include <iostream>

class SocketClient{
    private:
        std::string name;
        uint16_t serverPort = 0;
        uint16_t connectionPeriod = 0;
    public:
        SocketClient(std::string clientName, uint16_t srvPort, uint16_t connPeriod):
                    name(clientName), serverPort(srvPort), connectionPeriod(connPeriod){
            ;
        }
        void connectToServer();
};