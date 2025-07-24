#include "ClientApp.h"
#include <iostream>
#include <memory>
#include <string>
#include <bits/ostream.tcc>
#include <sys/socket.h>

#include "HSMClient.h"
#include "../common/Utils.h"

// TODO: bug in SSL_READ / SSL_WRITE

std::shared_ptr<HSMClientSocket> ClientApp::socket = nullptr;
std::shared_ptr<HSMClient> ClientApp::hsmClient = nullptr;

void ClientApp::showMenu() {
    std::cout << "===== HSM Client =====" << std::endl;
    std::cout << "1. verify CVV2" << std::endl;
    std::cout << "2. verify PVV" << std::endl;
    std::cout << "3. encrypt" << std::endl;
    std::cout << "4. gen MAC" << std::endl;
    std::cout << "5. verify MAC" << std::endl;
    std::cout << "6. exit" << std::endl;
}

void ClientApp::run() {

    // initialize and connect to server
    init();

    // start main loop
    while (true) {
        showMenu();
        std::string option;
        std::cin >> option;
        handleOption(option);
    }
}

void ClientApp::init() {
    if (!socket) {
        socket = std::make_shared<HSMClientSocket>();
    }

    if (!hsmClient) {
        hsmClient = std::make_shared<HSMClient>();
    }

    socket->setServerIP(serverIP);
    socket->setPort(port);
    socket->setSSLCTX(sslContext);

    if (!socket->connectToServer()) {
        Utils::showError("Failed to connect to server\n");
        endProgram();
    }

    hsmClient->setSocket(socket.get());
}


void ClientApp::handleOption(const std::string &option) {

    int optionNumber;

    try {
        optionNumber = std::stoi(option);
    } catch (const std::exception& e) {
        Utils::showMessage("\nPlease enter a valid number.\n");
        return;
    }

    switch (optionNumber) {
        case 1:
            hsmClient->verifyCVV2();
            break;
        case 2:
            hsmClient->verifyPVV();
            break;
        case 3:
            hsmClient->encryptData();
            break;
        case 4:
            hsmClient->generateMAC();
            break;
        case 5:
            hsmClient->verifyMAC();
            break;
        case 6:
            endProgram();
            break;
        default:
            Utils::showMessage("\nPlease enter a valid number.\n");
    }

}


void ClientApp::endProgram() {
    std::cout << "\nClosing the program...\n" << std::endl;

    if (socket) {
        socket->closeConnection();
        socket.reset();
    }

    if (hsmClient) {
        hsmClient.reset();
    }

    std::exit(0);
}