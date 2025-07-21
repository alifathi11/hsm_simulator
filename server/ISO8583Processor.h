#ifndef ISO8583PROCESSOR_H
#define ISO8583PROCESSOR_H
#include <string>

#include "ISO8583Message.h"


class ISO8583Processor {

public:
    explicit ISO8583Processor(const std::string& messageStr);
    std::string process();

private:
    std::string messageStr;
    ISO8583Message iso8583Message;

    // TODO: build ISO8583Message out of the string message
    ISO8583Message buildISO8583Message();
    // TODO: process the ISO8583Message and make the response
    std::string handleISO8583Message();
    // TODO: send back the response to ClientHandler
    void sendResult();
};



#endif //ISO8583PROCESSOR_H
