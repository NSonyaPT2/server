#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <string>
#include <unordered_map>

/**
 * @class UserDatabase
 * @brief Класс для работы с базой данных пользователей
 * @details Хранит пары "логин:пароль" и предоставляет методы для проверки
 */
class UserDatabase {
private:
    std::unordered_map<std::string, std::string> users; ///< Хэш-таблица пользователей
    
public:
    /**
     * @brief Конструктор по умолчанию
     */
    UserDatabase();
    
    /**
     * @brief Загрузка базы пользователей из файла
     * @param[in] filename Имя файла с базой пользователей
     * @return true - успешная загрузка, false - ошибка
     * @details Формат файла: логин:пароль (по одной паре на строку)
     */
    bool loadFromFile(const std::string& filename);
    
    /**
     * @brief Проверка наличия пользователя в базе
     * @param[in] login Логин пользователя
     * @return true - пользователь существует, false - не существует
     */
    bool checkUser(const std::string& login);
    
    /**
     * @brief Получение пароля пользователя
     * @param[in] login Логин пользователя
     * @return Пароль пользователя или пустую строку, если пользователь не найден
     */
    std::string getPassword(const std::string& login);
};

#endif