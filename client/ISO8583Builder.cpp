#include "ISO8583Builder.h"

#include "FieldMapper.h"


ISO8583Message ISO8583Builder::buildVerifyCVV2(const ISO8583Request &request) {

    // extract fields needed
    std::string pan = request.pan;
    std::string cvv2 = request.cvv2;
    std::string exp = request.exp;

    // build ISO8583 message
    ISO8583Message message;
    message.setMTI("0100");

    message.setField(FieldMapper::getFieldNumber("pan"), pan);
    message.setField(FieldMapper::getFieldNumber("cvv2"), cvv2);
    message.setField(FieldMapper::getFieldNumber("exp"), exp);

    return message;
}

ISO8583Message ISO8583Builder::buildVerifyPVV(const ISO8583Request &request) {

    // extract fields needed
    std::string pan = request.pan;
    std::string pvv = request.pvv;

    // build ISO8583 message
    ISO8583Message message;
    message.setMTI("0100");

    message.setField(FieldMapper::getFieldNumber("pan"), pan);
    message.setField(FieldMapper::getFieldNumber("pvv"), pvv);

    return message;
}

ISO8583Message ISO8583Builder::buildEncryptُData(const ISO8583Request &request) {

    // extract fields needed
    std::string data = request.data;

    // build ISO8583 message
    ISO8583Message message;
    message.setMTI("0800");

    message.setField(FieldMapper::getFieldNumber("data"), data);

    return message;
}

ISO8583Message ISO8583Builder::buildGenerateMAC(const ISO8583Request &request) {

    // extract fields needed
    std::string data = request.data;

    // build ISO8583 message
    ISO8583Message message;
    message.setMTI("0800");

    message.setField(FieldMapper::getFieldNumber("data"), data);

    return message;
}

ISO8583Message ISO8583Builder::buildVerifyMAC(const ISO8583Request &request) {

    // extract fields needed
    std::string data = request.data;
    std::string mac = request.mac;

    // build ISO8583 message
    ISO8583Message message;
    message.setMTI("0800");

    message.setField(FieldMapper::getFieldNumber("data"), data);
    message.setField(FieldMapper::getFieldNumber("mac"), mac);

    return message;
}



