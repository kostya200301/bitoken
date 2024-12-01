cmake_minimum_required(VERSION 3.10)

project(MyProject)

include_directories(${CMAKE_SOURCE_DIR}/libs)
add_subdirectory(json)
add_subdirectory(model)
add_subdirectory(tcp)
add_subdirectory(crypto)
add_subdirectory(db)

set(TESTS_OUTPUT_DIR "./")

# Make targets for REST TESTS
set(TESTS_JSON_SRC_DIR jsonTests)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

# Создаем отдельный таргет для каждого исходного файла
foreach(TEST_JSON_SRC_FILE ${SOURCES_JSON_TEST_FILES})

    # Получаем имя файла без расширения
    get_filename_component(TEST_SRC_NAME "${TEST_JSON_SRC_FILE}" NAME_WE)

    # Создаем название таргета, объединяя TestJSON и TEST_SRC_NAME
    set(TARGET_NAME "TestJSON${TEST_SRC_NAME}")

    # Выводим сообщение о создании таргета
    message(STATUS "Создание таргета для теста: ${TARGET_NAME}")

    # Создаем таргет для теста
    add_executable(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Catch.cpp ${CMAKE_CURRENT_SOURCE_DIR}/json/${TEST_JSON_SRC_FILE})

    message(STATUS "TESTS_OUTPUT_DIR: ${TESTS_OUTPUT_DIR}")
    # Устанавливаем директорию для сохранения исполняемых файлов
    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_OUTPUT_DIR})

    # Добавляем таргет как зависимость к общему таргету TestRest
    add_dependencies(TestJSON ${TARGET_NAME})

    # Добавляем заголовки и библиотеки, необходимые для каждого теста
    target_include_directories(${TARGET_NAME} PRIVATE src)
    target_link_libraries(${TARGET_NAME} PRIVATE json)
endforeach()


set(TESTS_TCP_SRC_DIR tcpTests)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

# Создаем отдельный таргет для каждого исходного файла
foreach(TEST_TCP_SRC_FILE ${SOURCES_TCP_TEST_FILES})

    # Получаем имя файла без расширения
    get_filename_component(TEST_SRC_NAME "${TEST_TCP_SRC_FILE}" NAME_WE)

    # Создаем название таргета, объединяя TestJSON и TEST_SRC_NAME
    set(TARGET_NAME "TestTCP${TEST_SRC_NAME}")

    # Выводим сообщение о создании таргета
    message(STATUS "Создание таргета для теста: ${TARGET_NAME}")

    # Создаем таргет для теста
    add_executable(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Catch.cpp ${CMAKE_CURRENT_SOURCE_DIR}/tcp/${TEST_TCP_SRC_FILE})

    message(STATUS "TESTS_OUTPUT_DIR: ${TESTS_OUTPUT_DIR}")
    # Устанавливаем директорию для сохранения исполняемых файлов
    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_OUTPUT_DIR})

    # Добавляем таргет как зависимость к общему таргету TestRest
    add_dependencies(TestTCP ${TARGET_NAME})

    # Добавляем заголовки и библиотеки, необходимые для каждого теста
    target_include_directories(${TARGET_NAME} PRIVATE src)
    target_link_libraries(${TARGET_NAME} PRIVATE tcp)
endforeach()

set(TESTS_MODEL_SRC_DIR modelTests)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

# Создаем отдельный таргет для каждого исходного файла
foreach(TEST_MODEL_SRC_FILE ${SOURCES_MODEL_TEST_FILES})

    # Получаем имя файла без расширения
    get_filename_component(TEST_SRC_NAME "${TEST_MODEL_SRC_FILE}" NAME_WE)

    # Создаем название таргета, объединяя TestJSON и TEST_SRC_NAME
    set(TARGET_NAME "TestModel${TEST_SRC_NAME}")

    # Выводим сообщение о создании таргета
    message(STATUS "Создание таргета для теста: ${TARGET_NAME}")

    # Создаем таргет для теста
    add_executable(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Catch.cpp ${CMAKE_CURRENT_SOURCE_DIR}/model/${TEST_MODEL_SRC_FILE})

    message(STATUS "TESTS_OUTPUT_DIR: ${TESTS_OUTPUT_DIR}")
    # Устанавливаем директорию для сохранения исполняемых файлов
    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_OUTPUT_DIR})

    # Добавляем таргет как зависимость к общему таргету TestRest
    add_dependencies(TestModel ${TARGET_NAME})

    # Добавляем заголовки и библиотеки, необходимые для каждого теста
    target_include_directories(${TARGET_NAME} PRIVATE src)
    target_link_libraries(${TARGET_NAME} PRIVATE model)
endforeach()

set(TESTS_CRYPTO_SRC_DIR cryptoTests)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

# Создаем отдельный таргет для каждого исходного файла
foreach(TEST_CRYPTO_SRC_FILE ${SOURCES_CRYPTO_TEST_FILES})
    # Получаем имя файла без расширения
    get_filename_component(TEST_SRC_NAME "${TEST_CRYPTO_SRC_FILE}" NAME_WE)

    # Создаем название таргета, объединяя TestJSON и TEST_SRC_NAME
    set(TARGET_NAME "TestCrypto${TEST_SRC_NAME}")

    # Выводим сообщение о создании таргета
    message(STATUS "Создание таргета для теста: ${TARGET_NAME}")

    # Создаем таргет для теста
    add_executable(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Catch.cpp ${CMAKE_CURRENT_SOURCE_DIR}/crypto/${TEST_CRYPTO_SRC_FILE})

    message(STATUS "TESTS_OUTPUT_DIR: ${TESTS_OUTPUT_DIR}")
    # Устанавливаем директорию для сохранения исполняемых файлов
    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_OUTPUT_DIR})

    # Добавляем таргет как зависимость к общему таргету TestRest
    add_dependencies(TestCrypto ${TARGET_NAME})

    # Добавляем заголовки и библиотеки, необходимые для каждого теста
    target_include_directories(${TARGET_NAME} PRIVATE src)
    target_link_libraries(${TARGET_NAME} PRIVATE crypto)
endforeach()


set(TESTS_DB_SRC_DIR DBTests)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)

# Создаем отдельный таргет для каждого исходного файла
foreach(TEST_DB_SRC_FILE ${SOURCES_DB_TEST_FILES})
    # Получаем имя файла без расширения
    get_filename_component(TEST_SRC_NAME "${TEST_DB_SRC_FILE}" NAME_WE)

    # Создаем название таргета, объединяя TestJSON и TEST_SRC_NAME
    set(TARGET_NAME "TestDB${TEST_SRC_NAME}")

    # Выводим сообщение о создании таргета
    message(STATUS "Создание таргета для теста: ${TARGET_NAME}")

    # Создаем таргет для теста
    add_executable(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/Catch.cpp ${CMAKE_CURRENT_SOURCE_DIR}/db/${TEST_DB_SRC_FILE})

    message(STATUS "TESTS_OUTPUT_DIR: ${TESTS_OUTPUT_DIR}")
    # Устанавливаем директорию для сохранения исполняемых файлов
    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TESTS_OUTPUT_DIR})

    # Добавляем таргет как зависимость к общему таргету TestRest
    add_dependencies(TestDB ${TARGET_NAME})

    # Добавляем заголовки и библиотеки, необходимые для каждого теста
    target_include_directories(${TARGET_NAME} PRIVATE src)
    target_link_libraries(${TARGET_NAME} PRIVATE db)
endforeach()
