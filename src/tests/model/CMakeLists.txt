# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(bitocen)

# Указываем файлы исходного кода для сборки
set(SOURCES_MODEL_TEST_FILES
        TestMessagesQueue.cpp
        TestUsers.cpp
)

set(SOURCES_MODEL_TEST_FILES ${SOURCES_MODEL_TEST_FILES} PARENT_SCOPE)

# Добавляем исполняемый файл
add_executable(TestModel ../Catch.cpp ${SOURCES_MODEL_TEST_FILES})

# Указываем библиотеки, которые нужно подключить
target_link_libraries(TestModel model)

set_target_properties(TestModel PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TESTS_OUTPUT_DIR}")