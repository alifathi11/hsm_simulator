#ifndef ISO8583PROCESSOR_H
#define ISO8583PROCESSOR_H
#include <string>

#include "ISO8583Message.h"


class ISO8583Processor {

public:
    explicit ISO8583Processor(const std::string& messageStr);
    std::string process();

private:
    std::string rawMessage;

    ISO8583Message buildISO8583Message();
    std::string handleISO8583Message(ISO8583Message iso8583Message);
};



#endif //ISO8583PROCESSOR_H
