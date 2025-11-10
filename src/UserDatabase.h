#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <string>
#include <unordered_map>

class UserDatabase {
private:
    std::unordered_map<std::string, std::string> users;
    
public:
    UserDatabase();
    bool loadFromFile(const std::string& filename);
    bool checkUser(const std::string& login);
    std::string getPassword(const std::string& login);
};

#endif