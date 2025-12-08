/**
 * @file Logger.cpp
 * @author Назарова Софья
 * @brief Реализация класса Logger
 * @version 1.0
 * @date 2025
 * @copyright WECT ПГУ
 */

#include "Logger.h"
#include <chrono>
#include <iomanip>

Logger* Logger::instance = nullptr;

/**
 * @brief Приватный конструктор
 * @param[in] filename Имя файла для записи журнала
 * @details Открывает файл в режиме добавления (append)
 */
Logger::Logger(const std::string& filename) {
    logFile.open(filename, std::ios::app);
}

/**
 * @brief Получение экземпляра логгера
 * @param[in] filename Имя файла журнала (по умолчанию /var/log/scale.log)
 * @return Ссылка на единственный экземпляр логгера
 * @note Создает экземпляр при первом вызове
 */
Logger& Logger::getInstance(const std::string& filename) {
    if (!instance) {
        instance = new Logger(filename);
    }
    return *instance;
}

/**
 * @brief Запись ошибки в журнал
 * @param[in] severity Уровень серьезности ошибки
 * @param[in] message Текст сообщения
 * @param[in] params Дополнительные параметры ошибки
 * @details Формат записи: время | уровень | сообщение | параметры
 *          Соответствует требованиям ТЗ п.4.2.6
 */
void Logger::logError(const std::string& severity, const std::string& message, 
                      const std::string& params) {
    std::lock_guard<std::mutex> lock(logMutex);
    
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    logFile << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S") << " | "
            << severity << " | " << message;
    
    if (!params.empty()) {
        logFile << " | " << params;
    }
    logFile << std::endl;
}

/**
 * @brief Деструктор
 * @details Закрывает файл журнала
 */
Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}