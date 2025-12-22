#include <UnitTest++/UnitTest++.h>
#include "../Session.h"
#include "../UserDatabase.h"

SUITE(SessionTest) {
    TEST(AuthenticateValidUser) {
        UserDatabase db;
        db.addUser("user1", "pass1");
        
        Session session(db);
        CHECK(session.authenticate("user1", "pass1"));
    }

    TEST(AuthenticateInvalidUser) {
        UserDatabase db;
        Session session(db);
        CHECK(!session.authenticate("nonexistent", "pass"));
    }
}