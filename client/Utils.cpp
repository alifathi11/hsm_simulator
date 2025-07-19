#include "Utils.h"

#include <iomanip>
#include <iostream>


std::string Utils::prompt(const std::string& message) {
    std::cout << message + " ";
    std::string response;
    std::cin >> response;
    return response;
}


void Utils::showMessage(const std::string &message) {
    std::cout << message << std::endl;
}

void Utils::printHex(const std::string &data) {
    std::cout << "Hex Dump (" << data.size() << " bytes):" << std::endl;
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
                  << (static_cast<unsigned int>(static_cast<unsigned char>(data[i]))) << " ";
        if ((i + 1) % 16 == 0) std::cout << std::endl;
    }
    std::cout << std::dec << std::endl;
}