#ifndef ISO8583BUILDER_H
#define ISO8583BUILDER_H
#include <string>

#include "ISO8583Message.h"
#include "ISO8583Request.h"


class ISO8583Builder {

public:
    static ISO8583Message buildVerifyCVV2(const ISO8583Request &request);
    static ISO8583Message buildVerifyPVV(const ISO8583Request &request);
    static ISO8583Message buildEncryptُData(const ISO8583Request &request);
    static ISO8583Message buildGenerateMAC(const ISO8583Request &request);
    static ISO8583Message buildVerifyMAC(const ISO8583Request &request);
};



#endif //ISO8583BUILDER_H
