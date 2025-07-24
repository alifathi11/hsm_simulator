#ifndef ISO8583INPUTMANAGER_H
#define ISO8583INPUTMANAGER_H

#include "ISO8583Request.h"


class ISO8583InputManager {

public:
    static ISO8583Request getVerifyCVV2Input();
    static ISO8583Request getVerifyPVVInput();
    static ISO8583Request getEncryptDataInput();
    static ISO8583Request getGenerateMACInput();
    static ISO8583Request getVerifyMACInput();
};



#endif //ISO8583INPUTMANAGER_H
