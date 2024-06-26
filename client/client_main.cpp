#include "client.h"
#include <iostream>
#include <thread>

/*
    TODO
    Make a section to input custom server
    Make a config save for the user
    Allow user to use save to connect to server
*/

void receiveMessages(Client& client) {
    client.receiveMessages();
}

int main() {
    std::string remote_server; 
    std::cout << "What is the address of the chat server?" << std::endl;
    std::getline(std::cin, remote_server);
    Client client(remote_server, 54000);
    int thrown_error = 0;
    client.connectToServer(thrown_error);
    if (thrown_error != 0) {
        return 1;
    }
    std::thread receiveThread(receiveMessages, std::ref(client));

    //setup username
    std::string sender;
    std::cout << "Enter your name: ";
    std::getline(std::cin, sender);

    std::string content;
    while (true) {
        std::getline(std::cin, content);
        if (content == "/quit") {
            break;
        }
        client.sendMessage(sender, content);
    }

    client.sendMessage(sender, "has left the chat.");
    receiveThread.join();

    return 0;
}