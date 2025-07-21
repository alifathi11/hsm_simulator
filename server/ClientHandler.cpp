#include "ClientHandler.h"

#include <optional>
#include <string>
#include "ClientHandler.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include "Utils.h"


ClientHandler::ClientHandler(int clientSocket) : clientSocket(clientSocket) {}

void ClientHandler::operator()() {

    while (true) {

        // get the client(switch) ISO8583 message
        auto msgOpt = recieveMessage();

        // check if the client is connected
        if (!msgOpt.has_value()) {
            Utils::showMessage("client " + std::to_string(clientSocket) + " disconnected.");
            break;
        }

        // extract message
        std::string message = msgOpt.value();

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

    ssize_t bytesReceived = recv(clientSocket, buffer, bufferSize - 1, 0);

    if (bytesReceived > 0) {
        return std::string(buffer, bytesReceived);
    } else if (bytesReceived == 0) {
        return std::nullopt;
    } else {
        Utils::showError("error receiving data from client " + std::to_string(clientSocket));
        return std::nullopt;
    }
}

std::string ClientHandler::handleMessage(const std::string& message) {
    ISO8583Processor processor(message);
    std::string response = processor.process();
    return response;
}

bool ClientHandler::sendResponse(const std::string& response) {
    ssize_t totalSent = 0;
    size_t toSend = response.size();
    const char* buffer = response.c_str();

    while (totalSent < toSend) {
        // try to send response
        ssize_t sent = send(clientSocket, buffer + totalSent, toSend - totalSent, 0);
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
    close(clientSocket);
}