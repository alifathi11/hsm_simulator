#pragma once
#include "SSLContext.h"


struct ServerConfig {
    int port;
    TLSMode tlsMode;
    std::string certFile;
    std::string keyFile;
};
