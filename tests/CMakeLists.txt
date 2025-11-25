find_package(UnitTest++ REQUIRED)

add_executable(run_tests
    test_main.cpp
    test_Calculator.cpp
    test_Logger.cpp
    test_UserDatabase.cpp
    test_Session.cpp
)

target_link_libraries(run_tests
    UnitTest++::UnitTest++
    # ваша основная библиотека
)

add_test(NAME run_tests COMMAND run_tests)