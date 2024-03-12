#include "SocketServer.hpp"        

void SocketServer::gotoListenMode(){

    int listenerSocket;
    int incomeSocket;
    
    listenerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listenerSocket < 0)
        Utils::errorProcess("Error. Create listening socket.", true, AppErrors::CreateListeningSocketError);

    struct sockaddr_in localAddr = {};
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = htons(this->port);
    Utils::fillLocalAddr(localAddr);

	if (bind(listenerSocket, (struct sockaddr*)&localAddr, sizeof(localAddr)) < 0)
		Utils::errorProcess("Error. Bind listening socket.", true, AppErrors::BindListeningSocketError);

	if (listen(listenerSocket, SOMAXCONN) < 0){
        close(listenerSocket);
        Utils::errorProcess("Error. Turn on listening socket mode.", true, AppErrors::TurnOnListeningSocketMode);
    }
    
    Utils::msgCoutEndl("Waiting for incoming connection on " + std::string(inet_ntoa(localAddr.sin_addr)) + 
        ":" + std::to_string(this->port) + "...");

	fd_set readfds = {};
	timeval timeout = {};
	timeout.tv_sec = 0;
	timeout.tv_usec = 100 * 1000;

    struct sockaddr_in incomeAddr = {};
	socklen_t incomeAddrLen = sizeof(incomeAddr);
    int nfds = 0;

	while (true)
	{
        if(listenerSocket < 0)
            Utils::errorProcess("Error. Listening socket broken.", true, AppErrors::ListeningSocketBroken);

        FD_ZERO(&readfds);
        FD_SET(listenerSocket, &readfds);

        nfds = std::max(nfds, listenerSocket);
        select(nfds+1, &readfds, NULL, NULL, &timeout);
        if (FD_ISSET(listenerSocket, &readfds) != 0){

            // Income connection
            FD_ZERO(&readfds);

            incomeSocket = accept(listenerSocket, (struct sockaddr*)&incomeAddr, &incomeAddrLen);
            if (incomeSocket < 0){
                Utils::errorProcess("Error. Turn on listening socket mode.", false, AppErrors::AcceptSocketError);
            }else{
                Utils::msgCoutEndl("Income connetion " + std::string(inet_ntoa(incomeAddr.sin_addr)) + ":" + std::to_string(incomeAddr.sin_port));
                std::thread threadRecievDataFromSocket(SocketServer::proccessIncomeConnection, incomeSocket);
                threadRecievDataFromSocket.detach();
            }
        }
	}
    close(listenerSocket);
};

void SocketServer::proccessIncomeConnection(int incomeSocket, bool disconectAfteRcvData = true){

    char incomeData[1024] = {};
    int bytesRecvd = 0;

    bytesRecvd = recv(incomeSocket, incomeData, sizeof(incomeData), 0);
    if(bytesRecvd > 0){
        std::string incomeString(incomeData);
        Utils::msgCoutEndl("Recieved data: " + incomeString);
        Utils::writeMsgToLog(incomeString);
        if(disconectAfteRcvData){
            close(incomeSocket);
            Utils::msgCoutEndl("Client disconnected.");
        }
    }else{
        close(incomeSocket);
        Utils::errorProcess("Client disconnected.", false, AppErrors::ClientDisconnected);
    }
}