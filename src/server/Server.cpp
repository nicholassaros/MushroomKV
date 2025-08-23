#include "Server.h"

Server::Server(int port)
    :   m_Port(port), 
        m_ServerFd(-1), 
        m_RequestManager(RequestManager()),
        m_TaskQueue(TaskQueue()) {
};

void Server::Start() { 

    if (!CreateSocket() || !BindSocket() || !Listen() || !CreateAndRegisterEpoll()){
        exit(EXIT_FAILURE);
    }

    
    while(true) {
        int ready_fds = GetReadyFileDescriptors();
        if (ready_fds == -1) {
            spdlog::error("Error getting list of list of fd's with ready status.");
            continue;
        }

        for (int i = 0; i < ready_fds; ++i) {
            int current_fd = m_EventsList[i].data.fd 

            if (current_fd == m_ServerFd) {
                spdlog::info("Detected new client connection. Adding request to processing queue"); 
                HandleClientConnection();

            } else {
                spdlog::info("Detected new message from client socket {}. Adding request to processing queue", current_fd);
                m_TaskQueue.push({TaskType::HANDLE_CLIENT_REQUEST, client_fd});
            }
        }
    }

}

bool Server::CreateSocket() {
    m_ServerFd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_ServerFd == 0) {
       return false;
    }
    spdlog::info("Successfully created server socket");
    return true;
}

bool Server::BindSocket() {
    m_ServerAddress.sin_family = AF_INET;           // IPv4
    m_ServerAddress.sin_addr.s_addr = INADDR_ANY;   // Listen on all interfaces
    m_ServerAddress.sin_port = htons(m_Port); 

    if (bind(m_ServerFd, (sockaddr*)&m_ServerAddress, sizeof(m_ServerAddress)) < 0) {
        close(m_ServerFd);
        return false;
    }
    spdlog::info("Bound to socket, {}", m_ServerFd);
    return true;
}

bool Server::Listen() {
    if (listen(m_ServerFd, 100) < 0) {
        close(m_ServerFd);
        return false;
    }
    spdlog::info("Listening over socket, {}", m_ServerFd);
    return true;
}

bool Server::CreateAndRegisterEpoll() {
    m_EpollFd = epoll_create1(0);

    if (m_EpollFd == -1) {
        spdlog::error("Error creating epoll instance");
        return false;
    }

    epoll_event event{};
    event.data.fd = m_ServerFd;
    event.events = EPOLLIN;

    // register server socket with epoll isntance
    if (epoll_ctl(m_EpollFd, EPOLL_CTL_ADD, m_ServerFd, &event) == -1) {
        spdlog::error("Error registering server socket with epoll instance");
        return false;
    }

    spdlog::info("Successfully created and registered Epoll");
    return true;
}

int Server::GetReadyFileDescriptors() {
    spdlog::error("Getting list of FD's ready for processing");
    int ready_fds = epoll_wait(m_EpollFd, m_EventsList, MAX_EVENTS, -1);
    return ready_fdsl
}

std::string Server::HandleClientRequest(int client_fd) {
    char buffer[BUFFER_SIZE];
    std::string data;

    while (true) {
        int bytes_read = read(client_fd, buffer, sizeof(buffer));
        if (bytes_read > 0) {

            data.append(buffer, bytes_read);

        } else if (bytes_read == 0) {
            // Client disconnected
            spdlog::info("Client disconnected"); 
            close(client_fd);
            break;
        } else {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // No more data available to read (expected with EPOLLET)
                break;
            } else {
                // Read error
                spdlog::error("Error reading from client socket"); 
                close(client_fd);
                break;
            }
        }
    }
    return data;
}

void Server::HandleClientConnection() {
   while (true) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);

        int client_fd = accept(m_ServerFd, (sockaddr*)&client_addr, &client_len);
        if (client_fd == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) { // break when no more connections
                break;
            } else {
                spdlog::error("Error when accepting new client");
                break;
            }
        }

        // MAKE NEW CLIENT SOCKET NOT BLOCKING
        //make_socket_non_blocking(client_fd);

        // Register client socket with epoll to monitor for reading
        epoll_event client_event{};
        client_event.data.fd = client_fd;
        client_event.events = EPOLLIN | EPOLLET; // Edge-triggered mode

        if (epoll_ctl(m_EpollFd, EPOLL_CTL_ADD, client_fd, &client_event) == -1) {
            spdlog::error("Error registering client with epoll");
            close(client_fd);
        } else {
            // REGISTER WITH SESSION MANAGER
            spdlog::info("Successfully registered new client session");
        }
    } 
}


void Server::SendResponse(int client_fd, std::string response) {
    if (send(client_fd, response.c_str(), response.size(), 0) < 0) {
        spdlog::error("Error sending response to client");
    }
    spdlog::error("Successfully send response to client"); 
}


