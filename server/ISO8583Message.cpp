#include "ISO8583Message.h"

#include <bitset>
#include <iostream>
#include <map>

#include "ISO8583Encoder.h"

#include <string>

#include "ISO8583Decoder.h"
#include "Utils.h"

void ISO8583Message::setMTI(const std::string& mti) {
    this->mti = mti;
}

void ISO8583Message::setField(int fieldNumber, const std::string& value) {
    this->fields[fieldNumber] = value;
}

std::string ISO8583Message::getField(int fieldNumber) {
    return this->fields.at(fieldNumber);
}

std::string ISO8583Message::getMTI() {
    return this->mti;
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


std::map<int, std::string> ISO8583Message::unpack(const std::string& rawMessage) {

    std::map<int, std::string> fields;
    size_t offset = 0;

    // extract MTI
    std::string encodedMTI = rawMessage.substr(offset, 4);
    offset += 4;

    // decode MTI
    mti = ISO8583Decoder::decodeMTI(encodedMTI);

    // extract 8 bytes of raw bitmap
    std::string rawBitmap = rawMessage.substr(offset, 8);
    offset += 8;

    // extract bitmap
    std::bitset<128> bitmap = ISO8583Decoder::parseBitmap(rawBitmap);

    // If bit 1 is set, it's a 128-bit bitmap, so read 8 more bytes
    if (bitmap[0]) {
        std::string secondaryBitmap = rawMessage.substr(offset, 8);
        offset += 8;
        rawBitmap += secondaryBitmap;
        bitmap = ISO8583Decoder::parseBitmap(rawBitmap);
    }

    // extract and decode fields
    for (int fieldNumber = 2; fieldNumber <= bitmap.size(); fieldNumber++) {
        if (bitmap.test(fieldNumber - 1)) {
            std::string rawValue = extractValue(fieldNumber, rawMessage, offset);
            std::string decodedValue = decodeField(fieldNumber, rawValue);
            fields[fieldNumber] = decodedValue;
        }
    }

    this->fields = fields;
    return fields;
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
            Utils::showError("invalid field number in encodeField: " + fieldNumber);
            exit(1);
    }
}

std::string ISO8583Message::decodeField(int fieldNumber, const std::string& value) {
    switch (fieldNumber) {
        case 2:  return ISO8583Decoder::decodePAN(value);
        case 3:  return ISO8583Decoder::decodeProcessingCode(value);
        case 7:  return ISO8583Decoder::decodeTransmissionDateTime(value);
        case 11: return ISO8583Decoder::decodeSTAN(value);
        case 12: return ISO8583Decoder::decodeTimeLocal(value);
        case 13: return ISO8583Decoder::decodeDateLocal(value);
        case 14: return ISO8583Decoder::decodeExpirationDate(value);
        case 22: return ISO8583Decoder::decodePOSConditionCode(value);
        case 24: return ISO8583Decoder::decodeFunctionCode(value);
        case 25: return ISO8583Decoder::decodePOSConditionCode(value);
        case 35: return ISO8583Decoder::decodeTrack2Data(value);
        case 41: return ISO8583Decoder::decodeTerminalID(value);
        case 42: return ISO8583Decoder::decodeCAIDC(value);
        case 48: return ISO8583Decoder::decodeAdditionalDataPrivate(value);
        case 49: return ISO8583Decoder::decodeCurrencyCode(value);
        case 52: return ISO8583Decoder::decodePINBlock(value);
        case 53: return ISO8583Decoder::decodeSecurityControlInfo(value);
        case 64: return ISO8583Decoder::decodeMAC(value);
        default:
            Utils::showError("invalid field number in decodeField: " + fieldNumber);
            exit(1);
    }
}

std::string ISO8583Message::extractValue(int fieldNumber, const std::string& msg, size_t& offset) {
    auto safe_substr = [&](size_t start, size_t len) -> std::string {
        if (start + len > msg.size()) {
            std::cerr << "Message too short when extracting field " << fieldNumber << std::endl;
            exit(1);
        }
        return msg.substr(start, len);
    };

    switch (fieldNumber) {
        // Field 2 - PAN - LLVAR (2-digit length prefix)
        case 2: {
            int len = std::stoi(safe_substr(offset, 2));
            offset += 2;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 3 - Processing Code - Fixed 6 bytes
        case 3: {
            int len = 6;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 7 - Transmission Date & Time - Fixed 10 bytes (MMDDhhmmss)
        case 7: {
            int len = 10;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 11 - STAN - Fixed 6 bytes
        case 11: {
            int len = 6;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 12 - Local Time - Fixed 6 bytes (hhmmss)
        case 12: {
            int len = 6;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 13 - Local Date - Fixed 4 bytes (MMDD)
        case 13: {
            int len = 4;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 14 - Expiration Date - Fixed 4 bytes (YYMM)
        case 14: {
            int len = 4;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 22 - POS Entry Mode - Fixed 3 bytes
        case 22: {
            int len = 3;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 24 - Function Code - Fixed 3 bytes
        case 24: {
            int len = 3;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 25 - POS Condition Code - Fixed 2 bytes
        case 25: {
            int len = 2;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 35 - Track 2 Data - LLVAR (2-digit length prefix)
        case 35: {
            int len = std::stoi(safe_substr(offset, 2));
            offset += 2;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 41 - Terminal ID - Fixed 8 bytes
        case 41: {
            int len = 8;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 42 - Merchant ID (CAIDC) - Fixed 15 bytes
        case 42: {
            int len = 15;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 48 - Additional Data (Private) - LLLVAR (3-digit length prefix)
        case 48: {
            int len = std::stoi(safe_substr(offset, 3));
            offset += 3;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 49 - Currency Code - Fixed 3 bytes
        case 49: {
            int len = 3;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 52 - PIN Block - Fixed 16 hex characters (8 bytes)
        case 52: {
            int len = 16; // hex string length
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 53 - Security Control Information - Fixed 16 hex chars
        case 53: {
            int len = 16;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        // Field 64 - Message Authentication Code (MAC) - Fixed 16 hex chars (8 bytes)
        case 64: {
            int len = 16;
            std::string data = safe_substr(offset, len);
            offset += len;
            return data;
        }
        default:
            Utils::showError("invalid field number in extractValue: " + fieldNumber);
            exit(1);
    }
}

