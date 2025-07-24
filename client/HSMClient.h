#ifndef HSMCLIENT_H
#define HSMCLIENT_H
#include "HSMClientSocket.h"
#include "HSMResponse.h"
#include "ISO8583Builder.h"
#include "ISO8583InputManager.h"


class HSMClient {

public:
    void verifyCVV2();
    void verifyPVV();
    void encryptData();
    void generateMAC();
    void verifyMAC();

    void setSocket(HSMClientSocket* socket);

private:
    HSMClientSocket* socket = nullptr;
};



#endif //HSMCLIENT_H
