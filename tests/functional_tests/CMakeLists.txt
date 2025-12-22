cmake_minimum_required(VERSION 3.10)
project(functional_tests)

# Находим GoogleTest
find_package(GTest REQUIRED)

# Ищем OpenSSL для SHA1 (но пока не подключаем)
find_package(OpenSSL)

# Файлы функциональных тестов
set(FUNCTIONAL_TEST_SOURCES
    functional_tests.cpp
    test_client.cpp
    test_utils.cpp
)

# Создаем исполняемый файл
add_executable(functional_tests ${FUNCTIONAL_TEST_SOURCES})

# Подключаем зависимости
target_include_directories(functional_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

# Библиотеки для линковки
target_link_libraries(functional_tests
    GTest::gtest
    GTest::gtest_main
    pthread
)

# Добавляем сокеты
if(UNIX)
    # Ничего дополнительно не нужно - сокеты в стандартной библиотеке
endif()

# Если нашли OpenSSL - подключаем для SHA1
if(OPENSSL_FOUND)
    message(STATUS "OpenSSL found, linking for SHA1 support")
    target_link_libraries(functional_tests OpenSSL::Crypto)
else()
    message(WARNING "OpenSSL not found, SHA1 functions will use dummy implementation")
endif()

# Копируем тестовые данные
if(EXISTS ${CMAKE_SOURCE_DIR}/test_data)
    add_custom_command(TARGET functional_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/test_data
        ${CMAKE_CURRENT_BINARY_DIR}/test_data
    )
endif()