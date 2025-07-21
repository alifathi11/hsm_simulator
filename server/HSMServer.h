#ifndef HSMSERVER_H
#define HSMSERVER_H
#include <atomic>


class HSMServer {
public:
    explicit HSMServer(int port);
    void start();
    void stop();

private:
    int serverSocket;
    int port;
    std::atomic<bool> isRunning;

    void setupSocket();
};



#endif //HSMSERVER_H
