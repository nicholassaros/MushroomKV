#include "SessionManager.h"
#include "Server.h"

#include <iostream>
#include <spdlog/spdlog.h>
#include <iostream>
#include <map>
#include <vector>
#include <cstring>      
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>  
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10

int main(){
    spdlog::info("Welcome to spdlog!");
    spdlog::warn("This is a warning!");
    spdlog::error("This is an error with a number: {}", 42);

    SessionManager sessionManager;

    sessionManager.removeSession(111);

    return 1;
}

Server::Server(int port)
    : m_Port(port), m_ServerFd(-1) {

};


void Server::Start() {
    m_ServerAddress.sin_family = AF_INET;           // IPv4
    m_ServerAddress.sin_addr.s_addr = INADDR_ANY;   // Listen on all interfaces
    m_ServerAddress.sin_port = htons(m_Port); 

    SocketCreate();

    SocketBind();

    SocketListen();
    
    CreateRegisterEpoll();

    epoll_event events[MAX_EVENTS];

    while(true) {

        int ready_fds = epoll_wait(m_EpollFd, events, MAX_EVENTS, -1);
        if (ready_fds == -1) {
            perror("epoll_wait");
            continue;
        }

        for (int i = 0; i < ready_fds; ++i) {
            if (events[i].data.fd == m_ServerFd) {
                
                while (true) {
                    sockaddr_in client_addr{};
                    socklen_t client_len = sizeof(client_addr);

                    // Accept connection (non-blocking)
                    int client_fd = accept(m_ServerFd, (sockaddr*)&client_addr, &client_len);
                    if (client_fd == -1) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) { // break when no more connections
                            break;
                        } else {
                            perror("accept");
                            break;
                        }
                    }

                    // Set the new client socket to non-blocking
                    //make_socket_non_blocking(client_fd);

                    // Register client socket with epoll to monitor for reading
                    epoll_event client_event{};
                    client_event.data.fd = client_fd;
                    client_event.events = EPOLLIN | EPOLLET; // Edge-triggered mode

                    if (epoll_ctl(m_EpollFd, EPOLL_CTL_ADD, client_fd, &client_event) == -1) {
                        perror("epoll_ctl: client_fd");
                        close(client_fd);
                    } else {
                        std::cout << "New connection: FD " << client_fd << "\n";
                    }
                }

            } else {
                // Client requesting 

            }
        }
    }

}



void Server::SocketCreate() {
    m_ServerFd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_ServerFd == 0) {
       exit(EXIT_FAILURE);
    }
}

void Server::SocketBind() {
    if (bind(m_ServerFd, (sockaddr*)&m_ServerAddress, sizeof(m_ServerAddress)) < 0) {
        close(m_ServerFd);
        exit(EXIT_FAILURE);
    }
}

void Server::SocketListen() {
    if (listen(m_ServerFd, 100) < 0) {
        close(m_ServerFd);
        exit(EXIT_FAILURE);
    }
}

void Server::CreateRegisterEpoll() {
   m_EpollFd = epoll_create1(0);

    if (m_EpollFd == -1) {
        spdlog::error("Error creating epoll instance");
        exit(EXIT_FAILURE);
    }

    epoll_event event{};
    event.data.fd = m_ServerFd;
    event.events = EPOLLIN;

    // register server socket with epoll isntance
    if (epoll_ctl(m_EpollFd, EPOLL_CTL_ADD, m_ServerFd, &event) == -1) {
        spdlog::error("Error registering server socket with epoll instance");
        exit(EXIT_FAILURE);
    }

    epoll_event events[MAX_EVENTS];
    spdlog::info("Successfully created and registered Epoll");
}
