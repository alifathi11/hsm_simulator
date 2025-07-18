#include <iostream>

#include "ClientApp.h"


int main() {
    std::cout << "\n\nISO 8583 HSM Simulator Started\n\n" << std::endl;

    ClientApp app;
    app.run();

    return 0;
}
