#ifndef ISO8583DECODER_H
#define ISO8583DECODER_H
#include <bitset>
#include <string>

class ISO8583Decoder {
public:

    static std::string decodeMTI(const std::string& encodedMTI);
    static std::bitset<64> parseBitmap(const std::string& bitmapHEX);
    static std::string decodeFixed(const std::string& value, size_t length);
    static std::string decodeLLVAR(const std::string& value);
    static std::string decodeLLLVAR(const std::string& value);
    static std::string decodeBCD(const std::string& value);

    static std::string decodePAN(const std::string& value);                    // Field 2
    static std::string decodeProcessingCode(const std::string& value);         // Field 3
    static std::string decodeTransmissionDateTime(const std::string& value);   // Field 7
    static std::string decodeSTAN(const std::string& value);                   // Field 11
    static std::string decodeTimeLocal(const std::string& value);              // Field 12
    static std::string decodeDateLocal(const std::string& value);              // Field 13
    static std::string decodeExpirationDate(const std::string& value);         // Field 14
    static std::string decodePOSConditionCode(const std::string& value);       // Fields 22 and 25
    static std::string decodeFunctionCode(const std::string& value);           // Field 24
    static std::string decodeTrack2Data(const std::string& value);             // Field 35
    static std::string decodeTerminalID(const std::string& value);             // Field 41
    static std::string decodeCAIDC(const std::string& value);                  // Field 42
    static std::string decodeAdditionalDataPrivate(const std::string& value);  // Field 48
    static std::string decodeCurrencyCode(const std::string& value);           // Field 49
    static std::string decodePINBlock(const std::string& value);               // Field 52
    static std::string decodeSecurityControlInfo(const std::string& value);    // Field 53
    static std::string decodeMAC(const std::string& value);                    // Field 64
};



#endif //ISO8583DECODER_H
