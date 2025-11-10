#include "Session.h"
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>

Session::Session(int socket, UserDatabase& db, Logger& log) 
    : clientSocket(socket), userDB(db), logger(log) {}

void Session::handleSession() {
    try {
        // Аутентификация
        if (!authenticate()) {
            logger.logError("ERROR", "Authentication failed");
            close(clientSocket);
            return;
        }
        
        // Обработка векторов
        if (!processVectors()) {
            logger.logError("ERROR", "Vector processing failed");
            close(clientSocket);
            return;
        }
        
        close(clientSocket);
        
    } catch (const std::exception& e) {
        logger.logError("CRITICAL", "Session exception", e.what());
        close(clientSocket);
    }
}

bool Session::authenticate() {
    // TODO: Реализация аутентификации по протоколу
    // Шаги 2-5 из ТЗ
    return true; // временная заглушка
}

bool Session::processVectors() {
    // TODO: Реализация обработки векторов
    // Шаги 6-10 из ТЗ
    return true; // временная заглушка
}