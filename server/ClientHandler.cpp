#include "ClientHandler.h"

#include <optional>
#include <string>
#include "ClientHandler.h"

#include <chrono>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <openssl/err.h>
#include <sys/socket.h>
#include <openssl/ssl.h>

#include "../common/Utils.h"


ClientHandler::ClientHandler(SSL* ssl) : ssl(ssl), clientSocket(SSL_get_fd(ssl)) {}

ClientHandler::~ClientHandler() {
    closeClientSocket();
}


void ClientHandler::operator()() {

    while (true) {

        // get the client(switch) ISO8583 message
        auto msgOpt = receiveMessage();

        // check if the client is connected
        if (!msgOpt.has_value()) {
            Utils::showMessage("client " + std::to_string(clientSocket) + " disconnected.");
            break;
        }

        // extract message
        std::string message = msgOpt.value();

        if (message.empty()) {
            continue;
        }

        // handle the ISO8583 message and make a response
        std::string response = handleMessage(message);

        // send the response to the client
        bool success = sendResponse(response);

        // report the result
        if (success) Utils::showMessage("Response sent to socket " + std::to_string(clientSocket) + " successfully.");
        else Utils::showMessage("Failed to send response.");
    }

    closeClientSocket();
}

std::optional<std::string> ClientHandler::receiveMessage() {

    size_t bufferSize = 1024;
    char buffer[bufferSize];
    std::memset(buffer, 0, bufferSize);

    ssize_t bytesReceived = SSL_read(ssl, buffer, bufferSize - 1);

    if (bytesReceived > 0) {
        return std::string(buffer, bytesReceived);
    } else {
        int sslErr = SSL_get_error(ssl, bytesReceived);

        if (sslErr == SSL_ERROR_ZERO_RETURN) {
            std::cout << "Client closed connection\n";
            return std::nullopt;
        } else if (sslErr == SSL_ERROR_WANT_READ || sslErr == SSL_ERROR_WANT_WRITE) {
            return "";
        } else {
            ERR_print_errors_fp(stderr);
            Utils::showError("SSL_read failed with error: " + std::to_string(sslErr));
            return std::nullopt;
        }
    }
}

std::string ClientHandler::handleMessage(const std::string& message) {
    return "00";
    // TODO: implement handleMessage
    // ISO8583Processor processor(message);
    // std::string response = processor.process();
    // return response;
}

bool ClientHandler::sendResponse(const std::string& response) {
    ssize_t totalSent = 0;
    size_t toSend = response.size();
    const char* buffer = response.c_str();

    while (totalSent < toSend) {
        // try to send response
        ssize_t sent = SSL_write(ssl, buffer + totalSent, toSend - totalSent);
        // check if the socket is connected
        if (sent <= 0) {
            Utils::showError("error sending response");
            return false;
        }
        // update total sent bytes
        totalSent += sent;
    }

    return true;
}

void ClientHandler::closeClientSocket() {
    Utils::showMessage("Closing socket " + std::to_string(clientSocket));
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(clientSocket);
}


