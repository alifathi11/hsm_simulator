#include <iostream>

#include "ServerApp.h"

int main() {
    std::cout << "HSM Server started" << std::endl;

    ServerApp app;
    app.run();

    return 0;
}
