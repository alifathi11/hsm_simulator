#include "SSLContext.h"

#include <stdexcept>
#include <openssl/ssl.h>

SSLContext::SSLContext() {
    init();
}

SSLContext::~SSLContext() {
    if (ctx != nullptr) {
        SSL_CTX_free(ctx);
    }
}

SSL_CTX *SSLContext::getCTX() {
    return ctx;
}


void SSLContext::init() {
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    const SSL_METHOD *method = TLS_client_method();
    ctx = SSL_CTX_new(method);

    if (!ctx) {
        throw std::runtime_error("Failed to create SSL context");
    }

    SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION);
    SSL_CTX_set_cipher_list(ctx, "HIGH:!aNULL:!MD5");
}
