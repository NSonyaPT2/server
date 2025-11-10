#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>

class Logger {
private:
    static Logger* instance;
    std::ofstream logFile;
    std::mutex logMutex;
    
    Logger(const std::string& filename);
    
public:
    static Logger& getInstance(const std::string& filename = "/var/log/scale.log");
    void logError(const std::string& severity, const std::string& message, 
                  const std::string& params = "");
    ~Logger();
};

#endif