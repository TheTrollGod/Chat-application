#ifndef SERVER_H
#define SERVER_H


#include <string>

class Server {
    public:
    //Initializeses the server with an IP address and a port
        Server(const std::string& ip, int port);
        //starts the server
        void start();
        //stops the server
        void stop();

    private:
        //ip address the server listens on
        std::string ip;
        //port the server is listening on
        int port;
        //file descriptor for server socket
        int serverSocket;
        //bool for y/n running
        bool running;
        //hanndels communication with client
        void handleClient(int clientSocket);
};
#endif