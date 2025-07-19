#include "HSMClientSocket.h"

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <bits/fs_fwd.h>


HSMClientSocket::HSMClientSocket(const std::string &serverIP, int port)
    : serverIP(serverIP), port(port), sockfd(-1) {}


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

    return true;

}

bool HSMClientSocket::sendMessage(const std::string &message) {
	ssize_t byteSent = send(sockfd, message.c_str(), message.size(), 0);
	return byteSent == message.size();
}

std::string HSMClientSocket::receiveMessage() {
    char buffer[1024] = {0};
    ssize_t byteReceived = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (byteReceived > 0) return std::string(buffer, byteReceived);
    else return "";
}


bool HSMClientSocket::isConnected() {
    return sockfd != -1;
}



bool HSMClientSocket::closeConnection() {
    if (sockfd != -1) {
        close(sockfd);
        sockfd = -1;
    }
}

