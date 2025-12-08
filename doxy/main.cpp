/**
 * @file main.cpp
 * @author Назарова Софья
 * @brief Точка входа серверного приложения
 * @version 1.0
 * @date 2025
 * @details Создает экземпляр сервера, разбирает параметры командной строки
 *          и запускает сервер
 * @copyright WECT ПГУ
 */

#include <iostream>
#include "Server.h"

/**
 * @brief Основная функция программы
 * @param[in] argc Количество аргументов командной строки
 * @param[in] argv Массив аргументов командной строки
 * @return Код завершения программы (0 - успех, 1 - ошибка)
 */
int main(int argc, char** argv) {
    Server server;
    server.parseCommandLine(argc, argv);
    server.start();
    return 0;
}