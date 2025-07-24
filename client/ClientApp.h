#ifndef CLIENTAPP_H
#define CLIENTAPP_H
#include <memory>
#include <string>
#include <openssl/x509.h>

#include "HSMClient.h"
#include "HSMClientSocket.h"


class ClientApp {

public:
    void run();

private:

    std::string serverIP = "127.0.0.1";
    int port = 12345;
    SSLContext sslContext;

    static std::shared_ptr<HSMClientSocket> socket;
    static std::shared_ptr<HSMClient> hsmClient;


    void init();
    void showMenu();
    void handleOption(const std::string& option);
    void endProgram();
};


#endif //CLIENTAPP_H
