#ifndef SSLCONTEXT_H
#define SSLCONTEXT_H
#include <openssl/types.h>


enum class TLSMode {
    CERT,
    PSK,
};


class SSLContext {
public:
    SSLContext();
    ~SSLContext();

    SSL_CTX* getCTX();

private:
    SSL_CTX *ctx;

    void init();
};



#endif //SSLCONTEXT_H
