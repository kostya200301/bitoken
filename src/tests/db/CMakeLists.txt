# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(bitocen)

# Указываем файлы исходного кода для сборки
set(SOURCES_DB_TEST_FILES
        TestDBConnection.cpp
        TestDBInitializer.cpp
        TestUsersManagerRepo.cpp
        TestMessagesManagerRepo.cpp
        TestReKeysManagerRepo.cpp
)

set(SOURCES_DB_TEST_FILES ${SOURCES_DB_TEST_FILES} PARENT_SCOPE)

# Добавляем исполняемый файл
add_executable(TestDB ../Catch.cpp ${SOURCES_DB_TEST_FILES})

# Указываем библиотеки, которые нужно подключить
target_link_libraries(TestDB db tools)

set_target_properties(TestDB PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TESTS_OUTPUT_DIR}")