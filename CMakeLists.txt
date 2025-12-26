cmake_minimum_required(VERSION 3.16)

project(app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(app
    main.cpp
    exchangetype/exchangetype.cpp
    filterclass/filterclass.cpp
    instrument/equity/equity.cpp
    instrument/future/future.cpp
    instrument/option/option.cpp
)

# ---- Vendored header-only libraries ----
target_include_directories(app
    PRIVATE
        ${CMAKE_SOURCE_DIR}/external
)
