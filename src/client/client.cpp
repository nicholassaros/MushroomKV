#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    const char* server_ip = "127.0.0.1"; // change to your server IP if needed
    const int server_port = 8080;

    std::cout << "Client Starting\n";

    // 1. Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Error creating socket\n";
        return 1;
    }

    // 2. Set up server address
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    // 3. Connect to server
    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Connection failed\n";
        close(sock);
        return 1;
    }

    std::cout << "Connected to server\n";

    // 4. Send request
    const char* request = "Hello from client";
    send(sock, request, strlen(request), 0);

    // 5. Receive response
    char buffer[1024] = {0};
    ssize_t bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        std::cout << "Server response: " << buffer << "\n";
    } else {
        std::cerr << "No response from server\n";
    }

    // 6. Close connection
    close(sock);

    return 0;
}