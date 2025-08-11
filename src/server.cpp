#include <spdlog/spdlog.h>
#include <iostream>

#include "SessionManager.h"
#include "Server.h"

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

}

void Server::SocketCreate() {
    m_ServerFd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_ServerFd == 0) {
       exit(1);
    }
}

void Server::SocketBind() {

}

void Server::SocketListen() {

}
