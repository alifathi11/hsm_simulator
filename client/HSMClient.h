#ifndef HSMCLIENT_H
#define HSMCLIENT_H
#include "HSMClientSocket.h"
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

    std::string serverIP = "127.0.0.1";
    int port = 12345;
    HSMClientSocket socket = HSMClientSocket(serverIP, port);
};



#endif //HSMCLIENT_H
