//Converts strings to and from objects
#include "message.h"
#include <sstream>

//Converts message object to a string format
std::string Message::toString() const{

    //Format: sender: content
    return sender + ": " + content;
}

//Creates a message object from a string
Message Message::fromString(const std::string& str) {
    Message msg;

    size_t pos = str.find(": ");
    if (pos != std::string::npos) {
        msg.sender = str.substr(0, pos);
        msg.content = str.substr(pos + 2);
    }
    return msg;
}