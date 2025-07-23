#ifndef HSMCOMMANDHANDLER_H
#define HSMCOMMANDHANDLER_H
#include <string>


class ISO8583Message;

class HSMCommandHandler {
public:
    static std::string handleVerifyCVV2(ISO8583Message iso8583Message);
    static std::string handleVerifyPVV(ISO8583Message iso8583Message);
    static std::string handleEncryptData(ISO8583Message iso8583Message);
    static std::string handleGenerateMAC(ISO8583Message iso8583Message);
    static std::string handleVerifyMAC(ISO8583Message iso8583Message);
};



#endif //HSMCOMMANDHANDLER_H
