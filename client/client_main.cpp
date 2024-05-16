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
    Client client("127.0.0.1", 54000);
    client.connectToServer();

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