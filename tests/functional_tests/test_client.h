#ifndef TEST_CLIENT_H
#define TEST_CLIENT_H

#include <string>
#include <vector>
#include <cstdint>

class TestClient {
public:
    TestClient();
    ~TestClient();
    
    // Основные методы
    bool connect(const std::string& host, int port);
    void disconnect();
    
    // Аутентификация (по протоколу ТЗ)
    bool authenticate(const std::string& login, 
                     const std::string& password,
                     const std::string& salt);
    
    // Отправка векторов (бинарный формат)
    bool sendVectors(const std::vector<std::vector<uint16_t>>& vectors);
    
    // Получение результатов
    bool receiveResults(std::vector<uint16_t>& results);
    
    // Упрощенный метод: аутентификация + отправка одного вектора
    bool sendSingleVector(const std::vector<uint16_t>& vector, 
                         uint16_t& result);
    
    // Проверка соединения
    bool isConnected() const;
    
private:
    int socket_fd_;
    bool connected_;
    
    // Приватные вспомогательные методы
    bool sendAll(const void* data, size_t length);
    bool receiveAll(void* buffer, size_t length);
    bool sendUint32(uint32_t value);
    bool receiveUint32(uint32_t& value);
    bool sendUint16(uint16_t value);
    bool receiveUint16(uint16_t& value);
    
    // Формирование сообщения для аутентификации
    std::string createAuthMessage(const std::string& login,
                                 const std::string& salt,
                                 const std::string& hash);
};

#endif // TEST_CLIENT_H