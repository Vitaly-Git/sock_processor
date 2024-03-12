#include "utils.hpp"

void Utils::msgCoutEndl(std::string msg){
    std::cout<<msg<<std::endl;
}

void Utils::helpStringOut(){
    Utils::msgCoutEndl("s_p [-s ServerPort]/[-c ClientName ServerPort ConnectionPeriod]");
    Utils::msgCoutEndl("[-s ServerPort] - start socket server on port");
    Utils::msgCoutEndl("[-c ClientName ServerPort ConnectionPeriod] - start client to connection on server port");
}

void Utils::errorProcess(std::string errorText, bool isCritial, AppErrors appErr){
    Utils::msgCoutEndl(errorText + "Error code: " + std::to_string((int)appErr));
    if (isCritial)
        exit((int)appErr);
}