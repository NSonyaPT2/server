#include "Logger.h"
#include <chrono>
#include <iomanip>

Logger* Logger::instance = nullptr;

Logger::Logger(const std::string& filename) {
    logFile.open(filename, std::ios::app);
}

Logger& Logger::getInstance(const std::string& filename) {
    if (!instance) {
        instance = new Logger(filename);
    }
    return *instance;
}

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

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}