#ifndef SERVER_H
#define SERVER_H

#include "RequestManager.h"

#include <iostream>
#include <cstring>      
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <unistd.h>
#include <spdlog/spdlog.h>

class Server {
public:
    Server(int);

    void Start();

private:
    int m_Port;
    int m_ServerFd;
    int m_EpollFd;
    sockaddr_in m_ServerAddress;
    RequestManager m_RequestManager;
       
    bool CreateSocket();

    bool BindSocket();

    bool Listen();

    bool CreateAndRegisterEpoll();

    std::string HandleClientRequest(int);

    void HandleClientConnection(int);

    void SendResponse(int client_fd, std::string);
};

#endif
