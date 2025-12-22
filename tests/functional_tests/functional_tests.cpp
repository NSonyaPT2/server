#include <gtest/gtest.h>
#include "test_client.h"
#include "test_utils.h"
#include "test_config.h"
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>

// Фикстура для функциональных тестов
class FunctionalTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // 1. Создаем тестовую БД пользователей
        TestUtils::createTestUserDB(TestConfig::TEST_USER_DB,
                                   TestConfig::TEST_LOGIN,
                                   TestConfig::TEST_PASSWORD);
        
        // 2. Запускаем сервер в отдельном процессе
        server_pid_ = TestUtils::startServerProcess(
            TestConfig::TEST_PORT,
            TestConfig::TEST_USER_DB,
            TestConfig::TEST_LOG_FILE
        );
        
        ASSERT_GT(server_pid_, 0) << "Не удалось запустить сервер";
        
        // 3. Ждем, пока сервер запустится
        bool server_ready = TestUtils::waitForPort(
            TestConfig::TEST_PORT,
            TestConfig::SERVER_START_TIMEOUT_MS
        );
        
        ASSERT_TRUE(server_ready) << "Сервер не запустился за отведенное время";
    }
    
    static void TearDownTestSuite() {
        // Останавливаем сервер
        if(server_pid_ > 0) {
            TestUtils::stopServerProcess(server_pid_);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    
    void SetUp() override {
        // Каждый тест начинает с нового подключения
        ASSERT_TRUE(client_.connect(TestConfig::TEST_HOST, TestConfig::TEST_PORT));
    }
    
    void TearDown() override {
        client_.disconnect();
    }
    
    TestClient client_;
    static pid_t server_pid_;
};

pid_t FunctionalTest::server_pid_ = 0;

// ТЕСТ 1: Успешная аутентификация
TEST_F(FunctionalTest, SuccessfulAuthentication) {
    std::string salt = TestConfig::TEST_SALT; // Или TestUtils::generateSalt()
    
    bool auth_result = client_.authenticate(
        TestConfig::TEST_LOGIN,
        TestConfig::TEST_PASSWORD,
        salt
    );
    
    EXPECT_TRUE(auth_result) << "Аутентификация с правильными данными должна пройти успешно";
}

// ТЕСТ 2: Неуспешная аутентификация
TEST_F(FunctionalTest, FailedAuthenticationWrongPassword) {
    std::string salt = TestUtils::generateSalt();
    
    bool auth_result = client_.authenticate(
        TestConfig::TEST_LOGIN,
        "wrong_password", // Неправильный пароль
        salt
    );
    
    EXPECT_FALSE(auth_result) << "Аутентификация с неправильным паролем должна завершиться ошибкой";
}

// ТЕСТ 3: Расчет произведения вектора
TEST_F(FunctionalTest, VectorProductCalculation) {
    // Аутентифицируемся
    ASSERT_TRUE(client_.authenticate(
        TestConfig::TEST_LOGIN,
        TestConfig::TEST_PASSWORD,
        TestConfig::TEST_SALT
    ));
    
    // Подготавливаем тестовые векторы
    std::vector<std::vector<uint16_t>> vectors = {
        {1, 2, 3, 4},           // 1 * 2 * 3 * 4 = 24
        {10, 20},               // 10 * 20 = 200
        {5, 0, 10}              // 5 * 0 * 10 = 0 (умножение на 0)
    };
    
    std::vector<uint16_t> expected_results = {24, 200, 0};
    
    // Отправляем векторы
    ASSERT_TRUE(client_.sendVectors(vectors));
    
    // Получаем результаты
    std::vector<uint16_t> results;
    ASSERT_TRUE(client_.receiveResults(results));
    
    // Проверяем результаты
    ASSERT_EQ(results.size(), expected_results.size());
    
    for(size_t i = 0; i < results.size(); i++) {
        EXPECT_EQ(results[i], expected_results[i]) 
            << "Неверный результат для вектора " << i;
    }
}

// ТЕСТ 4: Обработка переполнения (как в ТЗ)
TEST_F(FunctionalTest, OverflowHandling) {
    ASSERT_TRUE(client_.authenticate(
        TestConfig::TEST_LOGIN,
        TestConfig::TEST_PASSWORD,
        TestConfig::TEST_SALT
    ));
    
    // Вектор, который вызовет переполнение (например, 200 * 200)
    std::vector<std::vector<uint16_t>> vectors = {
        {200, 200}  // 200 * 200 = 40000, но uint16_t max = 65535
        // На самом деле нужно подобрать значения, которые точно вызовут переполнение
        // в вашей реализации (согласно ТЗ: при переполнении вверх возвращать 32767)
    };
    
    // В зависимости от вашей реализации Calculator::calculateProduct()
    // Тест может быть таким:
    vectors = {{300, 300}}; // 300 * 300 = 90000 > 65535 -> переполнение
    
    ASSERT_TRUE(client_.sendVectors(vectors));
    
    std::vector<uint16_t> results;
    ASSERT_TRUE(client_.receiveResults(results));
    
    ASSERT_EQ(results.size(), 1);
    
    // Согласно ТЗ: при переполнении вверх возвращать 32767 (2^15 - 1)
    EXPECT_EQ(results[0], 32767) 
        << "При переполнении должен возвращаться 32767";
}

// ТЕСТ 5: Нижнее переполнение (умножение на 0)
TEST_F(FunctionalTest, UnderflowHandling) {
    ASSERT_TRUE(client_.authenticate(
        TestConfig::TEST_LOGIN,
        TestConfig::TEST_PASSWORD,
        TestConfig::TEST_SALT
    ));
    
    // Согласно ТЗ: при переполнении вниз возвращать 0
    // Умножение на 0 всегда дает 0, что не является переполнением вниз
    // Но проверим обработку нулей
    std::vector<std::vector<uint16_t>> vectors = {
        {0, 100, 200},  // 0 * 100 * 200 = 0
        {1, 0, 1}       // 1 * 0 * 1 = 0
    };
    
    ASSERT_TRUE(client_.sendVectors(vectors));
    
    std::vector<uint16_t> results;
    ASSERT_TRUE(client_.receiveResults(results));
    
    ASSERT_EQ(results.size(), 2);
    EXPECT_EQ(results[0], 0);
    EXPECT_EQ(results[1], 0);
}

// ТЕСТ 6: Множественные векторы в одной сессии
TEST_F(FunctionalTest, MultipleVectorsInSession) {
    ASSERT_TRUE(client_.authenticate(
        TestConfig::TEST_LOGIN,
        TestConfig::TEST_PASSWORD,
        TestConfig::TEST_SALT
    ));
    
    // Отправляем 5 векторов разного размера
    std::vector<std::vector<uint16_t>> vectors;
    std::vector<uint16_t> expected;
    
    uint16_t product = 1;
    for(int i = 1; i <= 5; i++) {
        std::vector<uint16_t> vec;
        for(int j = 1; j <= i; j++) {
            vec.push_back(j);
            product *= j;
        }
        vectors.push_back(vec);
        expected.push_back(product);
        product = 1;
    }
    
    ASSERT_TRUE(client_.sendVectors(vectors));
    
    std::vector<uint16_t> results;
    ASSERT_TRUE(client_.receiveResults(results));
    
    ASSERT_EQ(results.size(), expected.size());
    
    for(size_t i = 0; i < results.size(); i++) {
        EXPECT_EQ(results[i], expected[i]) 
            << "Неверный результат для вектора " << i;
    }
}

// ТЕСТ 7: Неправильный формат данных (отправка без аутентификации)
TEST_F(FunctionalTest, SendDataWithoutAuthentication) {
    // Пытаемся отправить данные БЕЗ аутентификации
    std::vector<std::vector<uint16_t>> vectors = {{1, 2, 3}};
    
    // Сервер должен разорвать соединение или игнорировать данные
    // Результат зависит от вашей реализации
    bool send_result = client_.sendVectors(vectors);
    
    // Либо send_result == false, либо при попытке чтения результата будет ошибка
    if(send_result) {
        std::vector<uint16_t> results;
        bool receive_result = client_.receiveResults(results);
        EXPECT_FALSE(receive_result) << "Сервер должен отвергать данные без аутентификации";
    } else {
        EXPECT_FALSE(send_result) << "Отправка без аутентификации должна завершиться ошибкой";
    }
}

// ТЕСТ 8: Большой объем данных
TEST_F(FunctionalTest, LargeDataTransfer) {
    ASSERT_TRUE(client_.authenticate(
        TestConfig::TEST_LOGIN,
        TestConfig::TEST_PASSWORD,
        TestConfig::TEST_SALT
    ));
    
    // Создаем большой вектор (1000 элементов)
    std::vector<uint16_t> large_vector(1000);
    std::fill(large_vector.begin(), large_vector.end(), 1); // Все единицы
    
    std::vector<std::vector<uint16_t>> vectors = {large_vector};
    
    // Произведение всех единиц = 1
    ASSERT_TRUE(client_.sendVectors(vectors));
    
    std::vector<uint16_t> results;
    ASSERT_TRUE(client_.receiveResults(results));
    
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0], 1) << "Произведение 1000 единиц должно быть равно 1";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    // Инициализация (опционально)
    std::cout << "=== Запуск функциональных тестов сервера ===" << std::endl;
    std::cout << "Тестовый порт: " << TestConfig::TEST_PORT << std::endl;
    std::cout << "Хост: " << TestConfig::TEST_HOST << std::endl;
    
    int result = RUN_ALL_TESTS();
    
    // Очистка (опционально)
    std::cout << "=== Функциональные тесты завершены ===" << std::endl;
    
    return result;
}