#ifndef SECURITYSERVICE_H
#define SECURITYSERVICE_H
#include <string>


class SecurityService {
public:
    static std::string verifyCVV2(const std::string& pan, const std::string& cvv2, const std::string& exp);
    static std::string verifyPVV(const std::string& pan, const std::string& pvv);
    static std::string encryptData(const std::string& data);
    static std::string generateMAC(const std::string& data);
    static std::string verifyMAC(const std::string& data, const std::string& mac);
};



#endif //SECURITYSERVICE_H
