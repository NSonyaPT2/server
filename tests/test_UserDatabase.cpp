#include <UnitTest++/UnitTest++.h>
#include "../UserDatabase.h"
#include <cstdio>

SUITE(UserDatabaseTest) {
    TEST(AddUser) {
        UserDatabase db;
        db.addUser("user1", "pass1");
        CHECK(db.userExists("user1"));
    }

    TEST(AuthenticateUser) {
        UserDatabase db;
        db.addUser("user1", "pass1");
        CHECK(db.authenticate("user1", "pass1"));
        CHECK(!db.authenticate("user1", "wrongpass"));
    }

    TEST(LoadFromFile) {
        // Создаём временный файл с пользователями
        std::ofstream f("test_db.txt");
        f << "user1:pass1\nuser2:pass2\n";
        f.close();
        
        UserDatabase db;
        db.loadFromFile("test_db.txt");
        CHECK(db.userExists("user1"));
        CHECK(db.userExists("user2"));
        
        std::remove("test_db.txt");
    }
}