#ifndef HSMCLIENT_H
#define HSMCLIENT_H
#include "ISO8583Builder.h"
#include "ISO8583InputManager.h"


class HSMClient {

public:
    void verifyCVV2();
    void verifyPVV();
    void encryptData();
    void generateMAC();
    void verifyMAC();

private:
    ISO8583InputManager inputManager;
    ISO8583Builder builder;
    // TODO: send to HSM server
};



#endif //HSMCLIENT_H
