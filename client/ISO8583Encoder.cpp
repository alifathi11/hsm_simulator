#include "ISO8583Encoder.h"

#include <algorithm>
#include <cstdint>
#include <format>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <sstream>

#include "string"


std::string ISO8583Encoder::buildBitmap(const std::map<int, std::string> &fields) {
    int maxFieldNumber = 0;
    for (const auto& [fieldNumber, _] : fields) {
        if (fieldNumber > maxFieldNumber) maxFieldNumber = fieldNumber;
    }

    int bitmapSize = maxFieldNumber > 64 ? 128 : 64;
    std::string bitmap(bitmapSize / 8, '\0');

    if (bitmapSize == 128) {
        bitmap[0] = 0x80;
    }

    for (const auto& [fieldNumber, _] : fields) {
        if (fieldNumber < 1 || fieldNumber > 128) {
            throw std::invalid_argument("Invalid field number");
        }
        int bitIndex = fieldNumber - 1;
        int byteIndex = bitIndex / 8;
        int bitInByte = 7 - (bitIndex % 8);
        bitmap[byteIndex] |= (1 << bitInByte);
    }

    return bitmap;
}

std::string ISO8583Encoder::encodeLLVAR(const std::string& value) {

    // get the size of the value string
    int size = value.size();

    if (size > 99) {
        throw std::invalid_argument("value length is too long for LLVAR");
    }

    // build result string
    std::ostringstream oss;

    oss << std::setw(2) <<  std::setfill('0') << size;
    oss << value;

    return oss.str();

}

std::string ISO8583Encoder::encodeLLLVAR(const std::string& value) {

    // get the size of the value string
    int size = value.size();

    if (size > 999) {
        throw std::invalid_argument("value length is too long for LLLVAR");
    }

    // build result string
    std::ostringstream oss;

    oss << std::setw(3) << std::setfill('0') << size;
    oss << value;

    return oss.str();

}

std::string ISO8583Encoder::encodeFixed(const std::string& value, size_t length) {

    size_t size = value.size();

    if (size > length) {
        throw std::invalid_argument("Value length (" + std::to_string(size) +
                                    ") exceeds fixed length of " + std::to_string(length));
    }

    bool isNumber = all_of(value.begin(), value.end(), ::isdigit);

    std::ostringstream oss;

    if (isNumber) {
        oss << std::setw(length) <<  std::setfill('0') << value;
    } else {
        oss << std::left << std::setw(length) << std::setfill(' ') << value;
    }

    return oss.str();

}

std::string ISO8583Encoder::encodeBCD(const std::string& digits) {

    // leading 0 padding
    std::string padded = digits;
    if (padded.size() % 2 != 0) {
        padded = "0" + padded;
    }

    // build bcd string
    std::string bcd;

    for (int i = 0; i < padded.size(); i += 2) {
        char high = padded[i];
        char low = padded[i + 1];

        if (!isdigit(high) || !isdigit(low)) {
            throw std::invalid_argument("non-digit character in BCD input");
        }

        uint8_t byte = ((high - '0') << 4) | (low - '0');
        bcd += static_cast<char>(byte);
    }

    return bcd;

}

std::string ISO8583Encoder::encodeMTI(const std::string& mti) {

    if (mti.size() != 4 || !all_of(mti.begin(), mti.end(), ::isdigit)) {
        throw std::invalid_argument("MTI must be exactly 4 numeric digits");
    }

    return encodeBCD(mti);
}

std::string ISO8583Encoder::encodePAN(const std::string& pan) {

    if (pan.size() != 16 || !all_of(pan.begin(), pan.end(), ::isdigit)) {
        throw std::invalid_argument("PAN must be exactly 16 numeric digits");
    }

    return encodeLLVAR(pan);
}

std::string ISO8583Encoder::encodeProcessingCode(const std::string& code) {

    if (!all_of(code.begin(), code.end(), ::isdigit)) {
        throw std::invalid_argument("non-digit character in processing code");
    }

    return encodeFixed(code, 6);
}

std::string ISO8583Encoder::encodeSTAN(const std::string& stan) {

    if (!all_of(stan.begin(), stan.end(), ::isdigit)) {
        throw std::invalid_argument("non-digit character in STAN");
    }

    return encodeFixed(stan, 6);

}

std::string ISO8583Encoder::encodePOSentryMode(const std::string& mode) {

    if (!all_of(mode.begin(), mode.end(), ::isdigit)) {
        throw std::invalid_argument("non-digit character in pos entry mode");
    }

    return encodeFixed(mode, 3);

}

std::string ISO8583Encoder::encodePOSConditionCode(const std::string& conditionCode) {

    if (!all_of(conditionCode.begin(), conditionCode.end(), ::isdigit)) {
        throw std::invalid_argument("non-digit character in pos condition code");
    }

    return encodeFixed(conditionCode, 2);
}

std::string ISO8583Encoder::encodeTrack2Data(const std::string& data) {

    if (!all_of(data.begin(), data.end(), ::isdigit)) {
        throw std::invalid_argument("non-digit character in track2data");
    }

    if (data.size() > 35) {
        throw std::invalid_argument("track2data must have less than 35 characters");
    }

    return encodeLLVAR(data);

}

std::string ISO8583Encoder::encodeTerminalID(const std::string& tid) {
    return encodeFixed(tid, 8);
}

std::string ISO8583Encoder::encodeCAIDC(const std::string& code) {
    return encodeFixed(code, 15);
}

std::string ISO8583Encoder::encodeAdditionalDataPrivate(const std::string& data) {
    return encodeLLLVAR(data);
}

std::string ISO8583Encoder::encodeCurrencyCode(const std::string& code) {
    return encodeFixed(code, 3);
}

std::string ISO8583Encoder::encodeFunctionCode(const std::string& code) {
    return encodeFixed(code, 3);
}

std::string ISO8583Encoder::encodePINBlock(const std::string& pinBlock) {
    if (pinBlock.size() != 16) {
        throw std::invalid_argument("PIN block must be exactly 16 hex characters (8 bytes)");
    }

    // validate hex content
    if (!all_of(pinBlock.begin(), pinBlock.end(), ::isxdigit)) {
        throw std::invalid_argument("PIN block contains non-hex characters");
    }

    // convert hex string to raw bytes
    std::string result;
    for (int i = 0; i < 16; i += 2) {
        uint8_t byte = (std::stoi(pinBlock.substr(i, 2), nullptr, 16)) & 0xFF;
        result += static_cast<char>(byte);
    }

    return result;
}

std::string ISO8583Encoder::encodeAmount(const std::string& amount) {
    if (!all_of(amount.begin(), amount.end(), ::isdigit)) {
        throw std::invalid_argument("Amount must be numeric");
    }

    std::string padded = std::string(12 - amount.size(), '0') + amount;

    return encodeBCD(padded);
}

std::string ISO8583Encoder::encodeDateLocal(const std::string& date) {
    if (date.size() != 4 || !all_of(date.begin(), date.end(), ::isdigit)) {
        throw std::invalid_argument("Local date must be in MMDD format");
    }

    return encodeBCD(date);
}

std::string ISO8583Encoder::encodeNII(const std::string& nii) {
    if (nii.size() != 3 || !all_of(nii.begin(), nii.end(), ::isdigit)) {
        throw std::invalid_argument("NII must be exactly 3 digits");
    }

    return encodeBCD(nii);
}

std::string ISO8583Encoder::encodeExpirationDate(const std::string& date) {
    if (date.size() != 4 || !all_of(date.begin(), date.end(), ::isdigit)) {
        throw std::invalid_argument("Expiration date must be in YYMM format");
    }

    return encodeBCD(date);
}

std::string ISO8583Encoder::encodeMerchantID(const std::string& mid) {
    return encodeFixed(mid, 15);
}

std::string ISO8583Encoder::encodeTimeLocal(const std::string& time) {
    if (time.size() != 6 || !all_of(time.begin(), time.end(), ::isdigit)) {
        throw std::invalid_argument("Local time must be in hhmmss format");
    }

    return encodeBCD(time);
}

std::string ISO8583Encoder::encodeMAC(const std::string& mac) {
    if (mac.size() != 16 || !all_of(mac.begin(), mac.end(), ::isxdigit)) {
        throw std::invalid_argument("MAC must be 8-byte hex (16 hex chars)");
    }

    std::string result;
    for (int i = 0; i < 16; i += 2) {
        uint8_t byte = std::stoi(mac.substr(i, 2), nullptr, 16);
        result += static_cast<char>(byte);
    }

    return result;
}

std::string ISO8583Encoder::encodeSecurityControlInfo(const std::string& sci) {
    return encodeLLVAR(sci);
}

std::string ISO8583Encoder::encodeTransmissionDateTime() {
    std::time_t t = std::time(nullptr);
    std::tm *now = std::gmtime(&t);

    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%m%d%H%M%S", now);

    return encodeBCD(buffer);
}
