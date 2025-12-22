#include "test_client.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

TestClient::TestClient() : socket_fd_(-1), connected_(false) {}

TestClient::~TestClient() {
    disconnect();
}

bool TestClient::connect(const std::string& host, int port) {
    socket_fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd_ < 0) {
        return false;
    }
    
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    
    if (inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr) <= 0) {
        close(socket_fd_);
        socket_fd_ = -1;
        return false;
    }
    
    // Установка таймаута
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    setsockopt(socket_fd_, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(socket_fd_, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    
    if (::connect(socket_fd_, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(socket_fd_);
        socket_fd_ = -1;
        return false;
    }
    
    connected_ = true;
    return true;
}

void TestClient::disconnect() {
    if (socket_fd_ >= 0) {
        close(socket_fd_);
        socket_fd_ = -1;
    }
    connected_ = false;
}

bool TestClient::authenticate(const std::string& login, 
                            const std::string& password,
                            const std::string& salt) {
    if (!connected_) return false;
    
    // TODO: Реализовать SHA-1 когда подключим OpenSSL
    // Пока заглушка
    std::string auth_msg = login + ":" + salt + ":dummy_hash\n";
    
    // Отправляем сообщение
    if (send(socket_fd_, auth_msg.c_str(), auth_msg.length(), 0) <= 0) {
        return false;
    }
    
    // Получаем ответ
    char response[4] = {0};
    if (recv(socket_fd_, response, 3, 0) <= 0) {
        return false;
    }
    
    response[3] = '\0';
    return std::string(response) == "OK\n";
}

bool TestClient::sendVectors(const std::vector<std::vector<uint16_t>>& vectors) {
    if (!connected_) return false;
    
    // Заглушка для компиляции
    return false;
}

bool TestClient::receiveResults(std::vector<uint16_t>& results) {
    if (!connected_) return false;
    
    // Заглушка для компиляции
    results.clear();
    return false;
}

bool TestClient::isConnected() const {
    return connected_;
}