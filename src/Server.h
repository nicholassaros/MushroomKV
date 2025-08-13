#ifndef SERVER_H
#define SERVER_H

#include <cstring>      
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <unistd.h>

class Server {
public:
    Server(int);

    void Start();

private:
    int m_Port;
    int m_ServerFd;
    int m_EpollFd;
    sockaddr_in m_ServerAddress;

       
    void SocketCreate();

    void SocketBind();

    void SocketListen();

    void CreateRegisterEpoll();
};

#endif
