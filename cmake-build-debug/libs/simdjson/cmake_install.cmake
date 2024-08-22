# Install script for directory: /Users/konstantinbelakov/CLionProjects/bitocen/libs/simdjson

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/opt/homebrew/opt/llvm/bin/llvm-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "simdjson_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/konstantinbelakov/CLionProjects/bitocen/cmake-build-debug/libs/simdjson/libsimdjson.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsimdjson.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsimdjson.a")
    execute_process(COMMAND "/opt/homebrew/opt/llvm/bin/llvm-ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsimdjson.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "simdjson_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/simdjson" TYPE FILE FILES
    "/Users/konstantinbelakov/CLionProjects/bitocen/cmake-build-debug/libs/simdjson/simdjson-config.cmake"
    "/Users/konstantinbelakov/CLionProjects/bitocen/cmake-build-debug/libs/simdjson/simdjson-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "simdjson_Development" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/simdjson/simdjsonTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/simdjson/simdjsonTargets.cmake"
         "/Users/konstantinbelakov/CLionProjects/bitocen/cmake-build-debug/libs/simdjson/CMakeFiles/Export/e9be1f3bf2ac05e81f5c4d20ad32d021/simdjsonTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/simdjson/simdjsonTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/simdjson/simdjsonTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/simdjson" TYPE FILE FILES "/Users/konstantinbelakov/CLionProjects/bitocen/cmake-build-debug/libs/simdjson/CMakeFiles/Export/e9be1f3bf2ac05e81f5c4d20ad32d021/simdjsonTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/simdjson" TYPE FILE FILES "/Users/konstantinbelakov/CLionProjects/bitocen/cmake-build-debug/libs/simdjson/CMakeFiles/Export/e9be1f3bf2ac05e81f5c4d20ad32d021/simdjsonTargets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/konstantinbelakov/CLionProjects/bitocen/cmake-build-debug/libs/simdjson/simdjson.pc")
endif()

