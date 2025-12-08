#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>

/**
 * @class Logger
 * @brief Класс для ведения журнала работы сервера
 * @details Реализует паттерн Singleton для глобального доступа к логгеру
 *          Потокобезопасен благодаря использованию мьютекса
 */
class Logger {
private:
    static Logger* instance; ///< Единственный экземпляр класса
    std::ofstream logFile;   ///< Файл журнала
    std::mutex logMutex;     ///< Мьютекс для потокобезопасности
    
    /**
     * @brief Приватный конструктор
     * @param[in] filename Имя файла для записи журнала
     */
    Logger(const std::string& filename);
    
public:
    /**
     * @brief Получение экземпляра логгера
     * @param[in] filename Имя файла журнала (по умолчанию /var/log/scale.log)
     * @return Ссылка на единственный экземпляр логгера
     */
    static Logger& getInstance(const std::string& filename = "/var/log/scale.log");
    
    /**
     * @brief Запись ошибки в журнал
     * @param[in] severity Уровень серьезности ошибки
     * @param[in] message Текст сообщения
     * @param[in] params Дополнительные параметры ошибки
     */
    void logError(const std::string& severity, const std::string& message, 
                  const std::string& params = "");
    
    /**
     * @brief Деструктор
     * @details Закрывает файл журнала
     */
    ~Logger();
};

#endif