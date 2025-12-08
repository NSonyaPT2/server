#ifndef SESSION_H
#define SESSION_H

#include "UserDatabase.h"
#include "Logger.h"
#include "Calculator.h"
#include <cstdint>
#include <vector>
#include <string>

/**
 * @class Session
 * @brief Класс для обработки клиентской сессии
 * @details Управляет всем жизненным циклом соединения с клиентом:
 *          аутентификация, прием данных, вычисления, отправка результатов
 */
class Session {
private:
    int clientSocket;         ///< Дескриптор клиентского сокета
    UserDatabase& userDB;     ///< Ссылка на базу пользователей
    Logger& logger;           ///< Ссылка на логгер
    
    /**
     * @brief Аутентификация клиента
     * @return true - успешная аутентификация, false - ошибка
     * @details Реализует шаги 2-5 протокола из ТЗ
     */
    bool authenticate();
    
    /**
     * @brief Обработка векторов данных
     * @return true - успешная обработка, false - ошибка
     * @details Реализует шаги 6-10 протокола из ТЗ
     */
    bool processVectors();
    
    /**
     * @brief Прием точного количества байт
     * @param[out] buffer Буфер для приема данных
     * @param[in] len Количество байт для приема
     * @return true - успешный прием, false - ошибка
     */
    bool receiveExactly(void* buffer, size_t len);
    
    /**
     * @brief Отправка результата клиенту
     * @param[in] result Результат вычислений
     * @return true - успешная отправка, false - ошибка
     */
    bool sendResult(uint16_t result);
    
public:
    /**
     * @brief Конструктор сессии
     * @param[in] socket Дескриптор клиентского сокета
     * @param[in] db Ссылка на базу пользователей
     * @param[in] log Ссылка на логгер
     */
    Session(int socket, UserDatabase& db, Logger& log);
    
    /**
     * @brief Обработка клиентской сессии
     * @details Выполняет всю последовательность обработки клиента
     */
    void handleSession();
};

#endif