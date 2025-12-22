#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

#include <string>

namespace TestConfig {
    // Параметры тестового сервера
    const std::string TEST_HOST = "127.0.0.1";
    const int TEST_PORT = 33444;  // Отличный от стандартного 33333
    const int SERVER_START_TIMEOUT_MS = 2000;
    const int CLIENT_TIMEOUT_MS = 5000;
    
    // Пути к тестовым файлам
    const std::string TEST_USER_DB = "test_data/users_test.txt";
    const std::string TEST_LOG_FILE = "test_data/server_test.log";
    
    // Тестовые учетные данные
    const std::string TEST_LOGIN = "testuser";
    const std::string TEST_PASSWORD = "testpass";
    const std::string TEST_SALT = "a1b2c3d4e5f67890"; // 16 hex символов
}

#endif // TEST_CONFIG_H