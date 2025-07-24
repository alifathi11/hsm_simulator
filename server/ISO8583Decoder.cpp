#include "ISO8583Decoder.h"

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <stdexcept>


std::bitset<128> ISO8583Decoder::parseBitmap(const std::string& rawBitmap) {
    if (rawBitmap.size() != 8 && rawBitmap.size() != 16) {
        throw std::invalid_argument("Bitmap must be 8 or 16 bytes");
    }

    std::bitset<128> bitmap;
    size_t bitCount = rawBitmap.size() * 8;
    for (size_t i = 0; i < rawBitmap.size(); ++i) {
        unsigned char byte = static_cast<unsigned char>(rawBitmap[i]);
        for (int bit = 0; bit < 8; ++bit) {
            bitmap[(i * 8) + (7 - bit)] = (byte >> bit) & 0x01;
        }
    }

    return bitmap;
}

std::string ISO8583Decoder::decodeLLVAR(const std::string& data) {
    if (data.size() < 2) {
        throw std::invalid_argument("LLVAR data too short for length prefix");
    }

    std::string lengthStr = data.substr(0, 2);
    if (!std::all_of(lengthStr.begin(), lengthStr.end(), ::isdigit)) {
        throw std::invalid_argument("LLVAR length prefix must be numeric");
    }

    int length = std::stoi(lengthStr);
    if (data.size() < 2 + length) {
        throw std::invalid_argument("LLVAR data shorter than specified length");
    }

    return data.substr(2, length);
}


std::string ISO8583Decoder::decodeLLLVAR(const std::string& data) {
    if (data.size() < 3) {
        throw std::invalid_argument("LLLVAR data too short for length prefix");
    }

    std::string lengthStr = data.substr(0, 3);
    if (!std::all_of(lengthStr.begin(), lengthStr.end(), ::isdigit)) {
        throw std::invalid_argument("LLLVAR length prefix must be numeric");
    }

    int length = std::stoi(lengthStr);
    if (data.size() < 3 + length) {
        throw std::invalid_argument("LLLVAR data shorter than specified length");
    }

    return data.substr(3, length);
}

std::string ISO8583Decoder::decodeFixed(const std::string &data, size_t length) {
    if (data.size() != length) {
        throw std::invalid_argument("Fixed field length mismatch");
    }

    if (std::all_of(data.begin(), data.end(), ::isdigit)) {
        size_t firstNonZero = data.find_first_not_of('0');
        return (firstNonZero == std::string::npos) ? "0" : data.substr(firstNonZero);
    }

    return data.substr(0, data.find_last_not_of(' ') + 1);
}


std::string ISO8583Decoder::decodeBCD(const std::string& bcd) {
    std::string digits;
    for (unsigned char byte : bcd) {
        uint8_t high = (byte >> 4) & 0x0F;
        uint8_t low = byte & 0x0F;
        digits += std::to_string(high);
        digits += std::to_string(low);
    }

    if (digits.size() > 1 && digits[0] == '0') {
        digits = digits.substr(1);
    }

    return digits;
}

std::string ISO8583Decoder::decodeMTI(const std::string& data) {
    std::string mti = decodeBCD(data);
    if (mti.size() != 4) {
        // throw std::invalid_argument("Decoded MTI must be 4 digits");
    }
    return mti;
}

std::string ISO8583Decoder::decodePAN(const std::string& data) {
    std::string pan = decodeLLVAR(data);
    if (pan.size() < 13 || pan.size() > 19 || !all_of(pan.begin(), pan.end(), ::isdigit)) {
        throw std::invalid_argument("PAN must be between 13 and 19 digits");
    }
    return pan;
}

std::string ISO8583Decoder::decodeProcessingCode(const std::string& data) {
    std::string code = decodeFixed(data, 6);
    if (!std::all_of(code.begin(), code.end(), ::isdigit)) {
        throw std::invalid_argument("Decoded processing code must be numeric");
    }
    return code;
}

std::string ISO8583Decoder::decodeSTAN(const std::string& data) {
    std::string stan = decodeFixed(data, 6);
    if (!std::all_of(stan.begin(), stan.end(), ::isdigit)) {
        throw std::invalid_argument("Decoded STAN must be numeric");
    }
    return stan;
}

std::string ISO8583Decoder::decodePOSentryMode(const std::string& data) {
    std::string mode = decodeFixed(data, 3);
    if (!std::all_of(mode.begin(), mode.end(), ::isdigit)) {
        throw std::invalid_argument("Decoded POS entry mode must be numeric");
    }
    return mode;
}

std::string ISO8583Decoder::decodePOSConditionCode(const std::string& data) {
    std::string code = decodeFixed(data, 2);
    if (!std::all_of(code.begin(), code.end(), ::isdigit)) {
        throw std::invalid_argument("Decoded POS condition code must be numeric");
    }
    return code;
}

std::string ISO8583Decoder::decodeTrack2Data(const std::string& data) {
    std::string track2 = decodeLLVAR(data);
    if (track2.size() > 35 || !std::all_of(track2.begin(), track2.end(), ::isdigit)) {
        throw std::invalid_argument("Decoded Track2 data must be numeric and <= 35 characters");
    }
    return track2;
}

std::string ISO8583Decoder::decodeTerminalID(const std::string& data) {
    return decodeFixed(data, 8);
}

std::string ISO8583Decoder::decodeCAIDC(const std::string& data) {
    return decodeFixed(data, 15);
}

std::string ISO8583Decoder::decodeAdditionalDataPrivate(const std::string& data) {
    return decodeLLLVAR(data);
}

std::string ISO8583Decoder::decodeCurrencyCode(const std::string& data) {
    return decodeFixed(data, 3);
}

std::string ISO8583Decoder::decodeFunctionCode(const std::string& data) {
    return decodeFixed(data, 3);
}

std::string ISO8583Decoder::decodePINBlock(const std::string& data) {
    if (data.size() != 8) {
        throw std::invalid_argument("PIN block must be 8 bytes");
    }

    std::ostringstream oss;
    for (unsigned char byte : data) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    return oss.str();
}

std::string ISO8583Decoder::decodeAmount(const std::string& data) {
    std::string amount = decodeBCD(data);
    if (amount.size() > 12) {
        throw std::invalid_argument("Decoded amount exceeds 12 digits");
    }
    return std::to_string(std::stoll(amount));
}

std::string ISO8583Decoder::decodeDateLocal(const std::string& data) {
    std::string date = decodeBCD(data);
    if (date.size() != 4) {
        throw std::invalid_argument("Decoded local date must be 4 digits (MMDD)");
    }
    return date;
}

std::string ISO8583Decoder::decodeNII(const std::string& data) {
    std::string nii = decodeBCD(data);
    if (nii.size() != 3) {
        throw std::invalid_argument("Decoded NII must be 3 digits");
    }
    return nii;
}

std::string ISO8583Decoder::decodeExpirationDate(const std::string& data) {
    std::string date = decodeBCD(data);
    if (date.size() != 4) {
        throw std::invalid_argument("Decoded expiration date must be 4 digits (YYMM)");
    }
    return date;
}

std::string ISO8583Decoder::decodeMerchantID(const std::string& data) {
    return decodeFixed(data, 15);
}

std::string ISO8583Decoder::decodeTimeLocal(const std::string& data) {
    std::string time = decodeBCD(data);
    if (time.size() != 6) {
        throw std::invalid_argument("Decoded local time must be 6 digits (hhmmss)");
    }
    return time;
}

std::string ISO8583Decoder::decodeMAC(const std::string& data) {
    if (data.size() != 8) {
        throw std::invalid_argument("MAC must be 8 bytes");
    }

    std::ostringstream oss;
    for (unsigned char byte : data) {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }
    return oss.str();
}

std::string ISO8583Decoder::decodeSecurityControlInfo(const std::string& data) {
    return decodeLLVAR(data);
}

std::string ISO8583Decoder::decodeTransmissionDateTime(const std::string& data) {
    std::string datetime = decodeBCD(data);
    if (datetime.size() != 10) {
        throw std::invalid_argument("Decoded transmission datetime must be 10 digits (MMDDhhmmss)");
    }
    return datetime;
}