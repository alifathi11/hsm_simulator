#include "ISO8583InputManager.h"
#include "ISO8583Request.h"
#include "Utils.h"

ISO8583Request ISO8583InputManager::getVerifyCVV2Input() {

    // get inputs
    std::string pan = Utils::prompt("Enter your Primary Account Number:");
    std::string cvv2 = Utils::prompt("Enter your CVV2:");
    std::string exp = Utils::prompt("Enter your Expiration date (YYMM):");

    // build request
    ISO8583Request request;
    request.pan = pan;
    request.cvv2 = cvv2;
    request.exp = exp;

    return request;
}

ISO8583Request ISO8583InputManager::getVerifyPVVInput() {

    // get inputs
    std::string pan = Utils::prompt("Enter your Primary Account Number:");
    std::string pvv = Utils::prompt("Enter your PVV:");

    // build request
    ISO8583Request request;
    request.pan = pan;
    request.pvv = pvv;

    return request;
}

ISO8583Request ISO8583InputManager::getEncryptDataInput() {

    // get inputs
    std::string data = Utils::prompt("Enter your data:");

    // build request
    ISO8583Request request;
    request.data = data;

    return request;
}


ISO8583Request ISO8583InputManager::getGenerateMACInput() {

    // get inputs
    std::string data = Utils::prompt("Enter your data:");

    // build request
    ISO8583Request request;
    request.data = data;

    return request;
}

ISO8583Request ISO8583InputManager::getVerifyMACInput() {

    // get inputs
    std::string data = Utils::prompt("Enter your data:");
    std::string mac = Utils::prompt("Enter your MAC:");

    // build request
    ISO8583Request request;
    request.data = data;
    request.mac = mac;

    return request;
}

