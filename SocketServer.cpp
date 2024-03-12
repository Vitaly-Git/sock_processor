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
    localAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(listenerSocket, (struct sockaddr*)&localAddr, sizeof(localAddr)) < 0)
		Utils::errorProcess("Error. Bind listening socket.", true, AppErrors::BindListeningSocketError);

	if (listen(listenerSocket, SOMAXCONN) < 0){
        close(listenerSocket);
        Utils::errorProcess("Error. Turn on listening socket mode.", true, AppErrors::TurnOnListeningSocketMode);
    }
    
    Utils::msgCoutEndl("Waiting for incoming connection on " + std::string(inet_ntoa(localAddr.sin_addr)) + ":" + std::to_string(this->port));

	fd_set readfds = {};
	timeval timeout = {};
	timeout.tv_sec = 0;
	timeout.tv_usec = 100 * 1000;

    struct sockaddr_in incomeAddr = {};
	socklen_t incomeAddrLen = sizeof(incomeAddr);

	while (true)
	{
		while (true)
		{
            if(listenerSocket < 0)
                Utils::errorProcess("Error. Listening socket broken.", true, AppErrors::ListeningSocketBroken);

			FD_ZERO(&readfds);
			FD_SET(listenerSocket, &readfds);

            select(NULL, &readfds, NULL, NULL, &timeout);
            if (FD_ISSET(listenerSocket, &readfds) != 0)
            {
                // Income connection
                FD_ZERO(&readfds);
                break;
            }
		}

		incomeSocket = accept(listenerSocket, (struct sockaddr*)&incomeAddr, &incomeAddrLen);
		if (incomeSocket < 0)
		{
            Utils::errorProcess("Error. Turn on listening socket mode.", false, AppErrors::AcceptSocketError);
            continue;
		}else{
            Utils::msgCoutEndl("Income connetion " + std::string(inet_ntoa(incomeAddr.sin_addr)) + ":" + std::to_string(incomeAddr.sin_port));
        }

        char incomeData[1024] = {};
        int bytesRecvd = 0;

        bytesRecvd = recv(incomeSocket, incomeData, sizeof(incomeData), 0);
        if(bytesRecvd > 0)
        {
            Utils::msgCoutEndl("Recieved data: " + std::string(incomeData));
        }else{
            close(incomeSocket);
            Utils::errorProcess("Client disconnected.", false, AppErrors::ClientDisconnected);
        }

                // Отправляем данные обратно клиенту
        //         send(*it, buf, bytes_read, 0); 


		// SOCK_INCOMING_CONNECT sock_incoming_connect = { client_socket, listener_type };
		// _beginthread(&thread_sock_incoming_connect_processing, 0, (void*)&sock_incoming_connect);
	}

    close(listenerSocket);


    // char buf[1024];
    // int bytes_read;

    // listen(listenerSocket, 1);
    
    // while(1)
    // {
    //     sock = accept(listenerSocket, NULL, NULL);
    //     if(sock < 0)
    //     {
    //         perror("accept");
    //         exit(3);
    //     }
        
    //     switch(fork())
    //     {
    //     case -1:
    //         perror("fork");
    //         break;
            
    //     case 0:
    //         close(listenerSocket);
    //         while(1)
    //         {
    //             bytes_read = recv(sock, buf, 1024, 0);
    //             if(bytes_read <= 0) break;
    //             send(sock, buf, bytes_read, 0);
    //         }

    //         close(sock);
    //         _exit(0);
            
    //     default:
    //         close(sock);
    //     }
    // }
    
    // close(listenerSocket);

};

