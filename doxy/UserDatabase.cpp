/**
 * @file UserDatabase.cpp
 * @author Назарова Софья
 * @brief Реализация класса UserDatabase
 * @version 1.0
 * @date 2025
 * @copyright WECT ПГУ
 */

#include "UserDatabase.h"
#include <fstream>
#include <iostream>

/**
 * @brief Конструктор по умолчанию
 */
UserDatabase::UserDatabase() {}

/**
 * @brief Загрузка базы пользователей из файла
 * @param[in] filename Имя файла с базой пользователей
 * @return true - успешная загрузка, false - ошибка
 * @details Формат файла: логин:пароль (по одной паре на строку)
 * @note Соответствует требованиям ТЗ п.4.2.2
 */
bool UserDatabase::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string login = line.substr(0, pos);
            std::string password = line.substr(pos + 1);
            users[login] = password;
        }
    }
    
    file.close();
    return true;
}

/**
 * @brief Проверка наличия пользователя в базе
 * @param[in] login Логин пользователя
 * @return true - пользователь существует, false - не существует
 */
bool UserDatabase::checkUser(const std::string& login) {
    return users.find(login) != users.end();
}

/**
 * @brief Получение пароля пользователя
 * @param[in] login Логин пользователя
 * @return Пароль пользователя или пустую строку, если пользователь не найден
 */
std::string UserDatabase::getPassword(const std::string& login) {
    auto it = users.find(login);
    return (it != users.end()) ? it->second : "";
}