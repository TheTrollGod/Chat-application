#include "server.h"



int main() {
    Server server("127.0.0.1", 54000);
    server.start();
    return 0;
}