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
        
        SocketServer ss(serverPort);
        ss.gotoListenMode();

    }else if(appMode == "-c" && argc == 5){
        
        clientName = argv[1];
        serverPort = std::stoi(argv[2]);
        connectionPeriod = std::stoi(argv[3]);
        
        SocketClient sc(clientName, serverPort, connectionPeriod);
        sc.connectToServer();

    }else{
        Utils::helpStringOut();
    } 

    return 0;
}

