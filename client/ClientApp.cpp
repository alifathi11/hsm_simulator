#include "ClientApp.h"
#include <iostream>
#include <string>
#include <bits/ostream.tcc>

#include "HSMClient.h"
#include "Utils.h"

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
    while (true) {
        showMenu();
        std::string option;
        std::cin >> option;
        handleOption(option);
    }
}


void ClientApp::handleOption(const std::string &option) {

    int optionNumber;

    try {
        optionNumber = std::stoi(option);
    } catch (const std::exception& e) {
        Utils::showMessage("\nPlease enter a valid number.\n");
        return;
    }

    HSMClient client;

    switch (optionNumber) {
        case 1:
            client.verifyCVV2();
            break;
        case 2:
            client.verifyPVV();
            break;
        case 3:
            client.encryptData();
            break;
        case 4:
            client.generateMAC();
            break;
        case 5:
            client.verifyMAC();
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
    exit(0);
}