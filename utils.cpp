#include "utils.hpp"

void Utils::msgCoutEndl(std::string msg){
    std::cout<<msg<<std::endl;
}

void Utils::helpStringOut(){
    Utils::msgCoutEndl("s_p [-s ServerPort]/[-c ClientName ServerPort ConnectionPeriod]");
    Utils::msgCoutEndl("-s ServerPort - start socket server on port");
    Utils::msgCoutEndl("-c ClientName ServerPort ConnectionPeriod - start client to connection on server port");
}

void Utils::errorProcess(std::string errorText, bool isCritial, AppErrors appErr){
    Utils::msgCoutEndl(errorText + "Error code: " + std::to_string((int)appErr));
    if (isCritial)
        exit((int)appErr);
}

void Utils::fillLocalAddr(sockaddr_in& localAddr){

    // localAddr.sin_addr.s_addr = INADDR_ANY;
    char hostName[1024] = {};
    hostent *hostInfo;
    gethostname(hostName, sizeof(hostName));
    hostInfo = gethostbyname(hostName);
    std::memcpy(&localAddr.sin_addr, hostInfo->h_addr, hostInfo->h_length);
}