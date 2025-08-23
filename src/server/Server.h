#ifndef SERVER_H
#define SERVER_H

#include "RequestManager.h"
#include "RequestParser.h"
#include "SessionManager.h"
#include "TaskQueue.h"

#include <iostream>
#include <cstring>      
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <unistd.h>
#include <iostream>
#include <map>
#include <vector>
#include <optional>      
#include <fcntl.h>
#include <sys/epoll.h>
#include <spdlog/spdlog.h>

#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

class Server {
public:
    Server(int);

    void Start();

private:
    int             m_Port;
    int             m_ServerFd;
    int             m_EpollFd;
    sockaddr_in     m_ServerAddress;
    RequestManager  m_RequestManager;
    TaskQueue       m_TaskQueue;
    epoll_event     m_EventsList[MAX_EVENTS];
       
    bool CreateSocket();

    bool BindSocket();

    bool Listen();

    bool CreateAndRegisterEpoll();

    int GetReadyFileDescriptors();

    std::string HandleClientRequest(int);

    void HandleClientConnection();

    void SendResponse(int client_fd, std::string);
};

#endif
