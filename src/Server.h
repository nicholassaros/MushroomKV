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
    sockaddr_in m_ServerAddress;
       
    void SocketCreate();

    void SocketBind();

    void SocketListen();
};

#endif
