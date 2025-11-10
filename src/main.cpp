#include <iostream>
#include "Server.h"

int main(int argc, char** argv) {
    Server server;
    server.parseCommandLine(argc, argv);
    server.start();
    return 0;
}