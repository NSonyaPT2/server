#!/bin/bash
# Скрипт для запуска тестового сервера

set -e  # Выход при ошибке

echo "=== Запуск тестового сервера ==="

# Параметры
PORT=${1:-33444}
USER_DB="test_data/users_test.txt"
LOG_FILE="test_data/server_test.log"
SERVER_BIN="./bin/server"  # Путь к исполняемому файлу сервера

# Проверяем существование файлов
if [ ! -f "$SERVER_BIN" ]; then
    echo "Ошибка: Исполняемый файл сервера не найден: $SERVER_BIN"
    echo "Соберите проект командой: mkdir build && cd build && cmake .. && make"
    exit 1
fi

if [ ! -f "$USER_DB" ]; then
    echo "Создание тестовой БД пользователей..."
    echo "testuser:testpass" > "$USER_DB"
    echo "admin:admin123" >> "$USER_DB"
fi

echo "Порт: $PORT"
echo "БД пользователей: $USER_DB"
echo "Лог файл: $LOG_FILE"

# Запускаем сервер
"$SERVER_BIN" \
    --port "$PORT" \
    --users "$USER_DB" \
    --log "$LOG_FILE" \
    --daemon

SERVER_PID=$!

echo "Сервер запущен с PID: $SERVER_PID"
echo "Для остановки выполните: kill $SERVER_PID"

# Ждем завершения
wait $SERVER_PID

echo "Сервер остановлен"