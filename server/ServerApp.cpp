#include "ServerApp.h"

#include "HSMServer.h"


void ServerApp::run() {

    int port = 12345; // temporary

    HSMServer server(port);
    server.start();
}
