#ifndef ISO8583REQUEST_H
#define ISO8583REQUEST_H
#include <string>


struct ISO8583Request {
    std::string pan;
    std::string cvv2;
    std::string pvv;
    std::string data;
    std::string mac;
    std::string exp;

};



#endif //ISO8583REQUEST_H
