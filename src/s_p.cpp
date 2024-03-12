#include "s_p.hpp"

int main(int argc, char* argv[]){

    if(argc<3){
        Utils::helpStringOut();
        return 1;
    }

    std::string appMode(argv[1]);
    uint16_t serverPort;
    std::string clientName;
    uint16_t connectionPeriod;

    if(appMode == "-s" && argc == 3){
        
        serverPort = std::stoi(argv[2]);
        
        SocketServer sockServer(serverPort);
        sockServer.gotoListenMode();

    }else if(appMode == "-c" && argc == 5){
        
        clientName = argv[2];
        serverPort = std::stoi(argv[3]);
        connectionPeriod = std::stoi(argv[4]);
        
        SocketClient sockClient(clientName, serverPort, connectionPeriod);
        sockClient.sendDataToServer();

    }else{
        Utils::helpStringOut();
    } 

    return 0;
}

