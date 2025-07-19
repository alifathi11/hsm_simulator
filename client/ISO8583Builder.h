#ifndef ISO8583BUILDER_H
#define ISO8583BUILDER_H
#include <string>


class ISO8583Builder {

public:
    std::string buildVerifyCVV2(const std::string& pan, const std::string& cvv2, const std::string& exp);
    std::string buildVerifyPVV(const std::string& pan, const std::string& pvv);
    std::string buildEncryptُData(const std::string& data);
    std::string buildGenerateMAC(const std::string& data);
    std::string buildVerifyMAC(const std::string& data, const std::string& mac);
};



#endif //ISO8583BUILDER_H
