#ifndef ISO8583ENCODER_H
#define ISO8583ENCODER_H
#include <map>
#include <string>

class ISO8583Encoder {

public:

    static std::string encodeMTI(const std::string& mti);
    static std::string buildBitmap(const std::map<int, std::string>& fields);
    static std::string encodeFixed(const std::string& value, size_t length);
    static std::string encodeLLVAR(const std::string& value);
    static std::string encodeLLLVAR(const std::string& value);
    static std::string encodeBCD(const std::string& value);

    static std::string encodePAN(const std::string& pan);
    static std::string encodeProcessingCode(const std::string& code);
    static std::string encodeAmount(const std::string& amount);
    static std::string encodeTransmissionDateTime();
    static std::string encodeSTAN(const std::string& stan);
    static std::string encodeTimeLocal(const std::string& time);
    static std::string encodeDateLocal(const std::string& date);
    static std::string encodeFunctionCode(const std::string& code);
    static std::string encodeTrack2Data(const std::string& data);
    static std::string encodeCAIDC(const std::string& code);
    static std::string encodeExpirationDate(const std::string& exp);
    static std::string encodePOSentryMode(const std::string& mode);
    static std::string encodeNII(const std::string& nii);
    static std::string encodePOSConditionCode(const std::string& code);
    static std::string encodeTerminalID(const std::string& tid);
    static std::string encodeMerchantID(const std::string& mid);
    static std::string encodeAdditionalDataPrivate(const std::string& data);
    static std::string encodeCurrencyCode(const std::string& code);
    static std::string encodePINBlock(const std::string& pinBlock);
    static std::string encodeSecurityControlInfo(const std::string& sci);
    static std::string encodeMAC(const std::string& mac);

};




#endif //ISO8583ENCODER_H
