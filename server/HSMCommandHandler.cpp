#include "HSMCommandHandler.h"

#include "FieldMapper.h"
#include "ISO8583Message.h"
#include "SecurityService.h"


std::string HSMCommandHandler::handleVerifyCVV2(ISO8583Message iso8583Message) {
    // extract data
    std::string pan = iso8583Message.getField(FieldMapper::getFieldNumber("pan"));
    std::string cvv2 = iso8583Message.getField(FieldMapper::getFieldNumber("cvv2"));
    std::string exp = iso8583Message.getField(FieldMapper::getFieldNumber("exp"));

    // return result
    std::string result = SecurityService::verifyCVV2(pan, cvv2, exp);
    return result;
}


std::string HSMCommandHandler::handleVerifyPVV(ISO8583Message iso8583Message) {
    // extract data
    std::string pan = iso8583Message.getField(FieldMapper::getFieldNumber("pan"));
    std::string pvv = iso8583Message.getField(FieldMapper::getFieldNumber("pvv"));

    // return result
    std::string result = SecurityService::verifyPVV(pan, pvv);
    return result;
}

std::string HSMCommandHandler::handleEncryptData(ISO8583Message iso8583Message) {
    // extract data
    std::string data = iso8583Message.getField(FieldMapper::getFieldNumber("data"));

    // return result
    std::string result = SecurityService::encryptData(data);
    return result;
}

std::string HSMCommandHandler::handleGenerateMAC(ISO8583Message iso8583Message) {
    // extract data
    std::string data = iso8583Message.getField(FieldMapper::getFieldNumber("data"));

    // return result
    std::string result = SecurityService::generateMAC(data);
    return result;
}

std::string HSMCommandHandler::handleVerifyMAC(ISO8583Message iso8583Message) {
    // extract data
    std::string data = iso8583Message.getField(FieldMapper::getFieldNumber("data"));
    std::string mac = iso8583Message.getField(FieldMapper::getFieldNumber("mac"));

    // return result
    std::string result = SecurityService::verifyMAC(data, mac);
    return result;
}


