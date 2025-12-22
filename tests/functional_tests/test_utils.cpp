#include "test_utils.h"
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sstream>
#include <iomanip>
#include <random>

namespace TestUtils {
    std::string generateSalt() {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> dis;
        
        uint64_t salt = dis(gen);
        std::stringstream ss;
        ss << std::hex << std::setw(16) << std::setfill('0') << salt;
        return ss.str();
    }
    
    // ВРЕМЕННАЯ ЗАГЛУШКА вместо SHA1
    std::string calculateSHA1(const std::string& salt, const std::string& password) {
        // TODO: Заменить на реальный SHA1 когда подключим OpenSSL
        return "dummy_sha1_hash_for_now";
    }
    
    bool createTestUserDB(const std::string& filename, 
                         const std::string& login, 
                         const std::string& password) {
        std::ofstream file(filename);
        if (!file.is_open()) return false;
        
        file << login << ":" << password << std::endl;
        file.close();
        return true;
    }
    
    bool waitForPort(int port, int timeoutMs) {
        auto start = std::chrono::steady_clock::now();
        
        while (std::chrono::steady_clock::now() - start < 
               std::chrono::milliseconds(timeoutMs)) {
            int sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock < 0) continue;
            
            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
            
            if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
                close(sock);
                return true;
            }
            close(sock);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        return false;
    }
    
    // Упрощенные версии остальных функций
    pid_t startServerProcess(int port, 
                            const std::string& userDb, 
                            const std::string& logFile) {
        // Заглушка
        return -1;
    }
    
    bool stopServerProcess(pid_t pid) {
        return true;
    }
    
    std::vector<uint16_t> createTestVector(size_t size, uint16_t maxValue) {
        std::vector<uint16_t> result(size, 1);
        return result;
    }
}