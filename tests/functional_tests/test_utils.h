#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <string>
#include <vector>
#include <cstdint>
#include <chrono>

namespace TestUtils {
    // Генерация случайной соли (64 бита -> 16 hex символов)
    std::string generateSalt();
    
    // Вычисление SHA-1 хеша (как в ТЗ: HASH = SHA1(SALT || PASSWORD))
    std::string calculateSHA1(const std::string& salt, const std::string& password);
    
    // Создание тестовой БД пользователей
    bool createTestUserDB(const std::string& filename, 
                          const std::string& login, 
                          const std::string& password);
    
    // Запуск сервера в отдельном процессе
    pid_t startServerProcess(int port, 
                            const std::string& userDb, 
                            const std::string& logFile);
    
    // Остановка сервера
    bool stopServerProcess(pid_t pid);
    
    // Ожидание доступности порта
    bool waitForPort(int port, int timeoutMs = 5000);
    
    // Создание тестового вектора
    std::vector<uint16_t> createTestVector(size_t size, uint16_t maxValue = 100);
}

#endif // TEST_UTILS_H