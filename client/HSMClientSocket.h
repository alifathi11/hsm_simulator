#ifndef HSMCLIENTSOCKET_H
#define HSMCLIENTSOCKET_H
#include <string>


class HSMClientSocket {

public:
    HSMClientSocket(const std::string& serverIP, int port);
    ~HSMClientSocket();
    bool connectToServer();
    bool sendMessage(const std::string& message);
    std::string receiveMessage();
    bool closeConnection();
    bool isConnected();

private:
    std::string serverIP;
    int port;
    int sockfd;
};



#endif //HSMCLIENTSOCKET_H
