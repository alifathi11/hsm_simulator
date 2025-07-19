#include "ISO8583Message.h"

#include <iostream>

#include "ISO8583Encoder.h"


void ISO8583Message::setMTI(const std::string& mti) {
    this->mti = mti;
}

void ISO8583Message::setField(int fieldNumber, const std::string& value) {
    this->fields[fieldNumber] = value;
}

std::string ISO8583Message::getField(int fieldNumber) {
    return this->fields.at(fieldNumber);
}

std::string ISO8583Message::pack() {

    std::string packedMessage;

    std::string encodedMTI = ISO8583Encoder::encodeMTI(mti);
    packedMessage += encodedMTI;

    std::string bitmap = ISO8583Encoder::buildBitmap(fields);
    packedMessage += bitmap;

    for (const auto& [fieldNumber, value] : this->fields) {
        if (fieldNumber >= 2) {
            std::string encodedField = encodeField(fieldNumber, value);
            packedMessage += encodedField;
        }
    }

    return packedMessage;
}


std::map<int, std::string> ISO8583Message::unpack(const std::string& ) {

}


std::string ISO8583Message::encodeField(int fieldNumber, const std::string& value) {
    switch (fieldNumber) {
        case 2:  return ISO8583Encoder::encodePAN(value);
        case 3:  return ISO8583Encoder::encodeProcessingCode(value);
        case 7:  return ISO8583Encoder::encodeTransmissionDateTime();
        case 11: return ISO8583Encoder::encodeSTAN(value);
        case 12: return ISO8583Encoder::encodeTimeLocal(value);
        case 13: return ISO8583Encoder::encodeDateLocal(value);
        case 14: return ISO8583Encoder::encodeExpirationDate(value);
        case 22: return ISO8583Encoder::encodePOSConditionCode(value);
        case 24: return ISO8583Encoder::encodeFunctionCode(value);
        case 25: return ISO8583Encoder::encodePOSConditionCode(value);
        case 35: return ISO8583Encoder::encodeTrack2Data(value);
        case 41: return ISO8583Encoder::encodeTerminalID(value);
        case 42: return ISO8583Encoder::encodeCAIDC(value);
        case 48: return ISO8583Encoder::encodeAdditionalDataPrivate(value);
        case 49: return ISO8583Encoder::encodeCurrencyCode(value);
        case 52: return ISO8583Encoder::encodePINBlock(value);
        case 53: return ISO8583Encoder::encodeSecurityControlInfo(value);
        case 64: return ISO8583Encoder::encodeMAC(value);

        default:
            std::cerr << "invalid field number." << std::endl;
            exit(1);
    }
}

