# toolchain.cmake

# Укажите путь к компиляторам
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER /opt/homebrew/Cellar/mingw-w64/12.0.0/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /opt/homebrew/Cellar/mingw-w64/12.0.0/bin/x86_64-w64-mingw32-g++)

# Укажите параметры сборки
set(CMAKE_C_FLAGS "-D__MINGW32__")
set(CMAKE_CXX_FLAGS "-D__MINGW32__")

# Установите путь к библиотекам
set(CMAKE_FIND_ROOT_PATH /opt/homebrew/Cellar/mingw-w64/12.0.0)

# Укажите, что искать библиотеки и заголовки в корне кросс-компиляции
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
