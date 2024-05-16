#include "client.h"
#include "../common/message.h"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>


//initilizes the client
Client::Client(const std::string& ip, int port) : ip(ip), port(port), clientSocket(-1) {}


void Client::connectToServer(int& thrown_error) {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        thrown_error = 1;
        return;
    }

   sockaddr_in serverAddr;
   std::memset(&serverAddr, 0, sizeof(serverAddr));
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
   serverAddr.sin_port = htons(port);


   if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
    std::cerr << "Error connecting to server" << std::endl;
    thrown_error = 2;
    return;
   }
    
    thrown_error = 0;
   std::cout << "Connected to remote server\n" << ip << ":" << port << std::endl;
   
}



void Client::sendMessage(const std::string& sender, const std::string& content) {
    Message msg;
    msg.sender = sender;
    msg.content = content;
    std::string msgStr = msg.toString();
    //actually sends the message through the socket
    send(clientSocket, msgStr.c_str(), msgStr.size(), 0);
}



void Client::receiveMessages(){
    char buffer[1024];
    while(true) {
        ssize_t bytesRecived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRecived <= 0) {
            close(clientSocket);
            return;
        }
        buffer[bytesRecived] = '\0';
        Message msg = Message::fromString(buffer);
        std::cout << "Received message from " << msg.sender << ": " << msg.content << std::endl;
    }
}