# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(bitocen)

# Указываем файлы исходного кода для сборки
set(SOURCES_JSON_TEST_FILES
        TestJSONHelper.cpp
)

set(SOURCES_JSON_TEST_FILES ${SOURCES_JSON_TEST_FILES} PARENT_SCOPE)

# Добавляем исполняемый файл
add_executable(TestJSON ../Catch.cpp ${SOURCES_JSON_TEST_FILES})

# Указываем библиотеки, которые нужно подключить
target_link_libraries(TestJSON json)

set_target_properties(TestJSON PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TESTS_OUTPUT_DIR}")