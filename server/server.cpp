#include "server.h"
#include "../common/message.h"
#include <iostream>
#include <thread>
#include <vector>
#include <cstring> // Include for memset
#include <string> // Include for std::string

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#endif

// Initializes the server object with a provided IP and port
Server::Server(const std::string& ip, int port) : ip(ip), port(port), serverSocket(-1), running(false) {}

void Server::start() {
#ifdef _WIN32
    // Windows socket initialization
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return;
    }
#endif

    // Creates the socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }

    // Sets up socket addressing
    sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    serverAddr.sin_port = htons(port);

    // Binds the socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return;
    }

    // Listens for connections
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error listening on socket" << std::endl;
        return;
    }

    running = true;
    std::cout << "Server Started on " << ip << ":" << port << std::endl;

    // Accepts connections
    while (running) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }
        std::thread(&Server::handleClient, this, clientSocket).detach();
    }
}

// Stop server
void Server::stop() {
    running = false;
    if (serverSocket >= 0) {
#ifdef _WIN32
        closesocket(serverSocket);
        WSACleanup();
#else
        close(serverSocket);
#endif
    }
}

void Server::handleClient(int clientSocket) {
    char buffer[1024];
    while (true) {
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) {
            close(clientSocket);
            return;
        }
        buffer[bytesReceived] = '\0';
        // Convert received message in buffer into a Message object
        Message msg = Message::fromString(buffer);
        
        // DEBUG!!
        std::cout << "Received message from " << msg.sender << ": " << msg.content << std::endl;
    }
}