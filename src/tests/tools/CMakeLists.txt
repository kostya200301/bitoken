# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(bitocen)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем файлы исходного кода для сборки
set(SOURCES_TOOLS_TEST_FILES
        TestIoContextManager.cpp
)

set(SOURCES_TOOLS_TEST_FILES ${SOURCES_TOOLS_TEST_FILES} PARENT_SCOPE)

# Добавляем исполняемый файл
add_executable(TestTools ../Catch.cpp ${SOURCES_TOOLS_TEST_FILES})

target_link_libraries(TestTools tools)

set_target_properties(TestTools PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TESTS_OUTPUT_DIR}")