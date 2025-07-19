#ifndef ISO8583MESSAGE_H
#define ISO8583MESSAGE_H
#include <map>
#include <string>


class ISO8583Message {

public:
    void setMTI(const std::string&);
    void setField(int, const std::string&);
    std::string getField(int);
    std::string pack();
    std::map<int, std::string> unpack(const std::string unpack&);

private:
    std::string mti;
    std::map<int, std::string> fields;
    std::string encodeField(int, const std::string&);
};



#endif //ISO8583MESSAGE_H
