#include <iostream>
#include <getopt.h>
#include "Server.h"

Server::Server() : port(33333) {}

void Server::parseCommandLine(int argc, char** argv) {
    int opt;
    
    static struct option long_options[] = {
        {"port", required_argument, 0, 'p'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "p:h", long_options, NULL)) != -1) {
        switch (opt) {
            case 'p':
                port = std::stoi(optarg);
                break;
            case 'h':
                std::cout << "Usage: " << argv[0] << " [-p port] [-h]\n";
                std::cout << "  -p, --port PORT  Set server port (default: 33333)\n";
                std::cout << "  -h, --help       Show this help message\n";
                exit(0);
            default:
                std::cerr << "Usage: " << argv[0] << " [-p port] [-h]\n";
                exit(1);
        }
    }
}

void Server::start() {
    std::cout << "Server starting on port " << port << std::endl;
    // Здесь должна быть реальная логика запуска сервера
}