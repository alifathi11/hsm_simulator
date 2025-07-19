#ifndef ISO8583INPUTMANAGER_H
#define ISO8583INPUTMANAGER_H

#include "ISO8583Request.h"


class ISO8583InputManager {

public:
    ISO8583Request getVerifyCVV2Input();
    ISO8583Request getVerifyPVVInput();
    ISO8583Request getEncryptDataInput();
    ISO8583Request getGenerateMACInput();
    ISO8583Request getVerifyMACInput();
};



#endif //ISO8583INPUTMANAGER_H
