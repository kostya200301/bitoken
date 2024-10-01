# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(bitocen)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем файлы исходного кода для сборки
set(SOURCES_TCP_TEST_FILES
        TestTcpServer.cpp
        TestTcpClient.cpp
        TestTcpMessagesManager.cpp
        TestBuffersPool.cpp
        TestBuffers.cpp
)

set(SOURCES_TCP_TEST_FILES ${SOURCES_TCP_TEST_FILES} PARENT_SCOPE)

# Добавляем исполняемый файл
add_executable(TestTCP ../Catch.cpp ${SOURCES_TCP_TEST_FILES})

# Указываем библиотеки, которые нужно подключить
target_link_libraries(TestTCP tcp)

set_target_properties(TestTCP PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TESTS_OUTPUT_DIR}")