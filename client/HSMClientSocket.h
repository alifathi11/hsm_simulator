#ifndef HSMCLIENTSOCKET_H
#define HSMCLIENTSOCKET_H
#include <string>

#include "SSLContext.h"


class HSMClientSocket {

public:
    HSMClientSocket();
    ~HSMClientSocket();
    bool connectToServer();
    bool sendMessage(const std::string& message);
    std::string receiveMessage();
    void closeConnection();
    bool isConnected();
    // setters
    void setServerIP(const std::string& ip);
    void setPort(int port);
    void setSSLCTX(SSLContext& sllContext);

private:
    SSLContext sslContext;
    std::string serverIP = "127.0.0.1";
    SSL* ssl = nullptr;
    int port = 12345;
    int sockfd = -1;
};



#endif //HSMCLIENTSOCKET_H
