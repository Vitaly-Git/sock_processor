#include <iostream>

class SocketClient{
    private:
        std::string name;
        int64_t serverPort = -1;
        int64_t connectionPeriod = 0;
    public:
        SocketClient(std::string clientName, int64_t srvPort, int64_t connPeriod):
                    name(clientName), serverPort(srvPort), connectionPeriod(connPeriod){
            ;
        }
        void connectToServer();
};