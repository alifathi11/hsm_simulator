#ifndef HSMSERVER_H
#define HSMSERVER_H



class HSMServer {
public:
    explicit HSMServer(int port);
    void start();
private:
    int serverSocket;
    int port;

    void setupSocket();
};



#endif //HSMSERVER_H
