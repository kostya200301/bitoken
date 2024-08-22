
cmake_minimum_required(VERSION 3.10)

project(MyProject)

include_directories(${CMAKE_SOURCE_DIR}/libs)

add_subdirectory(json)

set(TESTS_OUTPUT_DIR "./")

find_package(PkgConfig REQUIRED)

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
