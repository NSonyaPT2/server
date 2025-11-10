#ifndef SESSION_H
#define SESSION_H

#include "UserDatabase.h"
#include "Logger.h"
#include "Calculator.h"
#include <cstdint>
#include <vector>
#include <string>

class Session {
private:
    int clientSocket;
    UserDatabase& userDB;
    Logger& logger;
    
    bool authenticate();
    bool processVectors();
    bool receiveExactly(void* buffer, size_t len);
    bool sendResult(uint16_t result);
    
public:
    Session(int socket, UserDatabase& db, Logger& log);
    void handleSession();
};

#endif