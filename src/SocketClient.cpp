#include "SocketClient.hpp"
#include "Utils.hpp"

void SocketClient::sendDataToServer(){
   while(true){
        connectToServerSendData();
        sleep(this->connectionPeriod);
    }
};

void SocketClient::connectToServerSendData(){

    int localSocket;
    
    localSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(localSocket < 0)
        Utils::errorProcess("Error. Create local socket.", true, AppErrors::CreateLocalSocketError);

    struct sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(this->serverPort);
    Utils::fillLocalAddr(serverAddr);

    if(connect(localSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
        Utils::errorProcess("Error. Server connetion error.", true, AppErrors::ServerConnetionError);
    else
        Utils::msgCoutEndl("Connection established: " + std::string(inet_ntoa(serverAddr.sin_addr)) + 
        ":" + std::to_string(this->serverPort));   

    char currentTimeBuffer[128] = {};
    Utils::getCurrentTimeFormatted(currentTimeBuffer);

    char msgToSend[1024] = {};
    std::sprintf(msgToSend, "[%s] %s", currentTimeBuffer, this->name.c_str());
    send(localSocket, msgToSend, std::strlen(msgToSend), 0);

    close(localSocket);
}