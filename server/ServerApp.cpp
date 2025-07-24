#include "ServerApp.h"

#include <iostream>

#include "ConfigLoader.h"
#include "HSMServer.h"
#include "ServerConfig.h"


void ServerApp::run() {

    // server config file path
    std::string configFilePath = "../server.conf";

    // load config
    ServerConfig config = ConfigLoader::load(configFilePath);

    // start server
    try {
        SSLContext sslContext(config.tlsMode, config.certFile, config.keyFile);
        HSMServer server(config.port, sslContext);
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "[FATAL] " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }


}
