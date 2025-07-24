#ifndef ISO8583DECODER_H
#define ISO8583DECODER_H
#include <bitset>
#include <string>

class ISO8583Decoder {
public:

    static std::string decodeMTI(const std::string& encodedMTI);
    static std::bitset<128> parseBitmap(const std::string& rawBitmap);
    static std::string decodeFixed(const std::string& data, size_t length);
    static std::string decodeLLVAR(const std::string& value);
    static std::string decodeLLLVAR(const std::string& value);
    static std::string decodeBCD(const std::string& value);

    static std::string decodePAN(const std::string& value);
    static std::string decodeProcessingCode(const std::string& value);
    static std::string decodeTransmissionDateTime(const std::string& value);
    static std::string decodeSTAN(const std::string& value);
    static std::string decodeTimeLocal(const std::string& value);
    static std::string decodeDateLocal(const std::string& value);
    static std::string decodeNII(const std::string &data);
    static std::string decodePOSentryMode(const std::string &data);
    static std::string decodeExpirationDate(const std::string& value);
    static std::string decodePOSConditionCode(const std::string& value);
    static std::string decodeFunctionCode(const std::string& value);
    static std::string decodeTrack2Data(const std::string& value);
    static std::string decodeTerminalID(const std::string& value);
    static std::string decodeCAIDC(const std::string& value);
    static std::string decodeAdditionalDataPrivate(const std::string& value);
    static std::string decodeCurrencyCode(const std::string& value);
    static std::string decodePINBlock(const std::string& value);
    static std::string decodeAmount(const std::string &data);
    static std::string decodeMerchantID(const std::string& data);
    static std::string decodeSecurityControlInfo(const std::string& value);
    static std::string decodeMAC(const std::string& value);
};



#endif //ISO8583DECODER_H
