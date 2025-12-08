#ifndef SERVER_H
#define SERVER_H

/**
 * @class Server
 * @brief Основной класс сетевого сервера
 * @details Обрабатывает параметры командной строки и запускает сервер
 */
class Server {
private:
    int port; ///< Порт, на котором работает сервер

public:
    /**
     * @brief Конструктор по умолчанию
     * @details Инициализирует порт значением по умолчанию (33333)
     */
    Server();
    
    /**
     * @brief Разбор параметров командной строки
     * @param[in] argc Количество аргументов
     * @param[in] argv Массив аргументов
     */
    void parseCommandLine(int argc, char** argv);
    
    /**
     * @brief Запуск сервера
     * @details Запускает сервер на указанном порту
     */
    void start();
};

#endif