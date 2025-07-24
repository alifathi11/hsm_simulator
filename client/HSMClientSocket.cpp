#include "HSMClientSocket.h"

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <bits/fs_fwd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "SSLContext.h"

HSMClientSocket::HSMClientSocket(): sslContext(SSLContext()) {
}


void HSMClientSocket::setSSLCTX(SSLContext& sllContext) {
    this->sslContext = sllContext;
}


void HSMClientSocket::setServerIP(const std::string& ip) {
    this->serverIP = ip;
}


void HSMClientSocket::setPort(int port) {
    this->port = port;
}

HSMClientSocket::~HSMClientSocket() {
    closeConnection();
}

bool HSMClientSocket::connectToServer() {

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Could not create socket");
        return false;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    if (inet_pton(AF_INET, serverIP.c_str(), &serverAddress.sin_addr) <= 0) {
        perror("server address not found.");
        return false;
    }

    if (connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Could not connect to server");
        return false;
    }

    ssl = SSL_new(sslContext.getCTX());
    SSL_set_fd(ssl, sockfd);

    if (SSL_connect(ssl) <= 0) {
        // handshake failed
        ERR_print_errors_fp(stderr);
        SSL_free(ssl);
        close(sockfd);
        return false;
    }

    return true;

}

bool HSMClientSocket::sendMessage(const std::string& message) {
	ssize_t byteSent = SSL_write(ssl, message.c_str(), message.size());
	return byteSent == message.size();
}

std::string HSMClientSocket::receiveMessage() {
    char buffer[1024] = {0};
    ssize_t byteReceived = SSL_read(ssl, buffer, sizeof(buffer) - 1);
    if (byteReceived > 0) return std::string(buffer, byteReceived);
    else return "";
}


bool HSMClientSocket::isConnected() {
    return sockfd != -1;
}



void HSMClientSocket::closeConnection() {
    if (sockfd != -1) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(sockfd);
        sockfd = -1;
    }
}

