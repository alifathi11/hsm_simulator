#ifndef HSMSERVER_H
#define HSMSERVER_H
#include <atomic>

#include "SSLContext.h"


class HSMServer {
public:
    explicit HSMServer(int port, SSLContext& sslContext);
    void start();
    void stop();

private:
    int serverSocket;
    int port;
    SSLContext& sslContext;
    std::atomic<bool> isRunning;

    void setupSocket();
};



#endif //HSMSERVER_H
