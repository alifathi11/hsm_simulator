#include "HSMServer.h"

#include <cstring>
#include <sys/socket.h>

#include <iostream>
#include <thread>
#include <unistd.h>
#include <cstring>
#include <memory>
#include <netinet/in.h>
#include <openssl/err.h>
#include <sys/socket.h>

#include "ClientHandler.h"
#include "../common/Utils.h"


HSMServer::HSMServer(int port, SSLContext& sslContext) : port(port), sslContext(sslContext) {}


void HSMServer::setupSocket() {

    // create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        Utils::showError("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // set SO_REUSEADDR option
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        Utils::showError("setsokopt failed");
        exit(EXIT_FAILURE);
    }

    // bind to port
    sockaddr_in serverAddress{};
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0) {
        Utils::showError("Failed to bind socket");
        exit(EXIT_FAILURE);
    }

    // start listening on the port
    if (listen(serverSocket, SOMAXCONN) < 0) {
        Utils::showError("Failed to start listening");
        exit(EXIT_FAILURE);
    }


    Utils::showMessage("Server started listening on port " + std::to_string(port));
}

void HSMServer::start() {

    setupSocket();

    isRunning = true;

    while (isRunning) {
        sockaddr_in clientAddress{};
        socklen_t clientAddressLength = sizeof(clientAddress);

        int clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            Utils::showError("Failed to accept connection");
            continue;
        }

        SSL* ssl = SSL_new(sslContext.getContext());
        SSL_set_fd(ssl, clientSocket);

        if (SSL_accept(ssl) <= 0) {
            // handshake failed
            ERR_print_errors_fp(stderr);
            SSL_free(ssl);
            close(clientSocket);
            continue;
        }

        Utils::showMessage("Client connected on socket: " + std::to_string(clientSocket));

        auto handler = std::make_shared<ClientHandler>(ssl);
        std::thread([handler]() {
            (*handler)();
        }).detach();
    }

    close(serverSocket);
}

void HSMServer::stop() {
    isRunning = false;
}
