#include "Utils.h"


void Utils::showMessage(const std::string& message) {
    std::cout << message << std::endl;
}

void Utils::showError(const std::string& errorMessage) {
    std::cerr << errorMessage << std::endl;
}