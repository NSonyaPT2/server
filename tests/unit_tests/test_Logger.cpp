#include <UnitTest++/UnitTest++.h>
#include "../Logger.h"
#include <fstream>
#include <cstdio>

SUITE(LoggerTest) {
    TEST(LogToFile) {
        Logger::getInstance().setLogFile("test_log.txt");
        Logger::getInstance().log("Test message");
        
        std::ifstream file("test_log.txt");
        CHECK(file.is_open());
        
        std::string line;
        std::getline(file, line);
        CHECK(line.find("Test message") != std::string::npos);
        
        file.close();
        std::remove("test_log.txt");
    }
}