cmake_minimum_required(VERSION 3.10)
project(ServerProject)

set(CMAKE_CXX_STANDARD 17)

# Включаем поддержку Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Ищем файлы в папке src
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

message(STATUS "Found sources: ${SOURCES}")

if(SOURCES)
    add_executable(server ${SOURCES} ${HEADERS})
    
    # Правильное подключение потоков
    target_link_libraries(server PRIVATE Threads::Threads)
    
    # Для Linux добавляем pthread явно
    if(UNIX)
        target_link_libraries(server PRIVATE pthread)
    endif()
    
    message(STATUS "Build configured successfully!")
else()
    message(FATAL_ERROR "No source files found!")
endif()