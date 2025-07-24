#ifndef SSLCONTEXT_H
#define SSLCONTEXT_H
#include <string>
#include <openssl/ssl.h>

enum class TLSMode {
    CERT, // Certificate-based TLS
    PSK,  // Pre-Shared Key TLS
};



class SSLContext {

public:
    SSLContext(TLSMode mode, const std::string& certFile, const std::string& keyFile);
    ~SSLContext();

    SSL_CTX* getContext();

private:
    TLSMode mode;
    std::string certFile, keyFile;
    SSL_CTX* ctx;

    void init();
    void configureCert();
    void configurePSK();
};



#endif //SSLCONTEXT_H
