//message.h
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message {
    //public scope
    public:
    std::string sender;             //Identifier for the sender

    std::string content;            //Content of the message

    std::string toString() const;   //Converts the message object (class) to a string format for transmission

    //Creates a message object from a string
    static Message fromString(const std::string& str);
};




#endif