#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
    public:
        Client(const std::string& ip, int port);
        void connectToServer(int& thrown_error);
        void sendMessage(const std::string& sender, const std::string& content);
        void receiveMessages();

    private:
        std::string ip;
        int port;
        int clientSocket;
};

#endif