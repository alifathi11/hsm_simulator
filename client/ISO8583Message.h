#ifndef ISO8583MESSAGE_H
#define ISO8583MESSAGE_H
#include <map>
#include <string>


class ISO8583Message {

public:
    void setMTI(const std::string& mti);
    void setField(int fieldNumber, const std::string& value);
    std::string getField(int fieldNumber);
    std::string pack();
    std::map<int, std::string> unpack(const std::string& message);

private:
    std::string mti;
    std::map<int, std::string> fields;
    std::string encodeField(int filedNumber, const std::string& value);
};



#endif //ISO8583MESSAGE_H
