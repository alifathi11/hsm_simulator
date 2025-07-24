#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <optional>
#include <string>

#include "ISO8583Processor.h"
#include "SSLContext.h"


class ClientHandler {
public:
    explicit ClientHandler(SSL* ssl);
    ~ClientHandler();
    void operator()();

private:
    SSL* ssl;
    int clientSocket;

    std::optional<std::string> receiveMessage();
    std::string handleMessage(const std::string& message);
    bool sendResponse(const std::string& response);
    void closeClientSocket();
};



#endif //CLIENTHANDLER_H
