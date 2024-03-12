#include <iostream>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <fstream>
#include <mutex>
#include <sys/time.h>

enum class AppErrors{
    CreateListeningSocketError = 1,
    BindListeningSocketError = 2,
    TurnOnListeningSocketMode = 3,
    ListeningSocketBroken = 4,
    AcceptSocketError = 5,
    ClientDisconnected = 6,
    CreateLocalSocketError = 7,
    ServerConnetionError = 8
};

class Utils{
    public:
        static void msgCoutEndl(std::string msg);
        static void helpStringOut();
        static void errorProcess(std::string errorText, bool isCritial, AppErrors appErr);
        static void fillLocalAddr(sockaddr_in& localAddr);
        static void writeMsgToLog(std::string msgToLog);
        static void getCurrentTimeFormatted(char * outTimeBuff);
};