#ifndef ISO8583MESSAGE_H
#define ISO8583MESSAGE_H
#include <map>
#include <string>


class ISO8583Message {

public:
    // setters
    void setMTI(const std::string& mti);
    void setField(int fieldNumber, const std::string& value);
    // getters
    std::string getMTI();
    std::string getField(int fieldNumber);
    // pack: fields map -> string
    std::string pack();
    // unpack string -> fields map
    std::map<int, std::string> unpack(const std::string& message);

private:
    // MTI and fields
    std::string mti;
    std::map<int, std::string> fields;
    // helper methods
    std::string encodeField(int filedNumber, const std::string& value);
    std::string decodeField(int fieldNumber, const std::string& value);
    std::string extractValue(int fieldNumber, const std::string& msg, size_t& offset);
};



#endif //ISO8583MESSAGE_H
