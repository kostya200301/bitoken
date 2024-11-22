# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(bitocen)

# Указываем файлы исходного кода для сборки
set(SOURCES_CRYPTO_TEST_FILES
        TestReEncrypt.cpp
)

set(SOURCES_CRYPTO_TEST_FILES ${SOURCES_CRYPTO_TEST_FILES} PARENT_SCOPE)

# Добавляем исполняемый файл
add_executable(TestCrypto ../Catch.cpp ${SOURCES_CRYPTO_TEST_FILES})

# Указываем библиотеки, которые нужно подключить
target_link_libraries(TestCrypto crypto)

set_target_properties(TestCrypto PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TESTS_OUTPUT_DIR}")