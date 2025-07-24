#include "SSLContext.h"

#include <stdexcept>
#include <openssl/ssl.h>
#include <openssl/err.h>

SSLContext::SSLContext(TLSMode mode, const std::string &certFile, const std::string &keyFile)
    : ctx(nullptr), mode(mode), certFile(certFile), keyFile(keyFile) {

    init();

    if (mode == TLSMode::CERT) {
        configureCert();
    } else if (mode == TLSMode::PSK) {
        configurePSK();
    }
}

SSLContext::~SSLContext() {
    if (ctx != nullptr) {
        SSL_CTX_free(ctx);
    }
}

SSL_CTX* SSLContext::getContext() {
    return ctx;
}

void SSLContext::init() {
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    const SSL_METHOD* method = TLS_server_method();
    ctx = SSL_CTX_new(method);

    if (!ctx) {
        throw std::runtime_error("Failed to create SSL context");
    }

    SSL_CTX_set_min_proto_version(ctx, TLS1_2_VERSION);
    SSL_CTX_set_cipher_list(ctx, "HIGH:!aNULL:!MD5");
}


void SSLContext::configureCert() {

    if (SSL_CTX_use_certificate_file(ctx, certFile.c_str(), SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        throw std::runtime_error("Failed to load certificate from file: " + certFile);
    }

    if (SSL_CTX_use_PrivateKey_file(ctx, keyFile.c_str(), SSL_FILETYPE_PEM ) <= 0) {
        ERR_print_errors_fp(stderr);
        throw std::runtime_error("Failed to load private key from file: " + keyFile);
    }

    if (!SSL_CTX_check_private_key(ctx)) {
        ERR_print_errors_fp(stderr);
        throw std::runtime_error("Private key does not match certificate.");
    }
}


void SSLContext::configurePSK() {
    // TODO: implement Pre-Shared Key TLS
}