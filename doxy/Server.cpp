/**
 * @file Server.cpp
 * @author Назарова Софья
 * @brief Реализация класса Server
 * @version 1.0
 * @date 2025
 * @copyright WECT ПГУ
 */

#include <iostream>
#include <getopt.h>
#include "Server.h"

/**
 * @brief Конструктор по умолчанию
 * @details Инициализирует порт значением по умолчанию (33333)
 */
Server::Server() : port(33333) {}

/**
 * @brief Разбор параметров командной строки
 * @param[in] argc Количество аргументов
 * @param[in] argv Массив аргументов
 * @details Поддерживает параметры:
 *          -p, --port PORT - установка порта сервера
 *          -h, --help      - вывод справки
 */
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

/**
 * @brief Запуск сервера
 * @details Запускает сервер на указанном порту
 * @note В текущей реализации содержит заглушку для демонстрации
 */
void Server::start() {
    std::cout << "Server starting on port " << port << std::endl;
    // Здесь должна быть реальная логика запуска сервера
}