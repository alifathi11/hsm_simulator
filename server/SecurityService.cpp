#include "SecurityService.h"

#include "ISO8583Message.h"


std::string SecurityService::verifyCVV2(const std::string &pan, const std::string &cvv2, const std::string &exp) {
    // TODO: implement verify CVV2
    return "00";
}

std::string SecurityService::verifyPVV(const std::string &pan, const std::string &pvv) {
    // TODO: implement verify PVV
    return "00";
}

std::string SecurityService::encryptData(const std::string& data) {
    // TODO: implement encrypt data
    return "00";
}

std::string SecurityService::generateMAC(const std::string &data) {
    // TODO: implement generate MAC
    return "00";
}

std::string SecurityService::verifyMAC(const std::string &data, const std::string& mac) {
    // TODO: implement verify MAC
    return "00";
}


