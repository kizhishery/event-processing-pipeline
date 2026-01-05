cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES CXX)

# --------------------
# C++ standard
# --------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --------------------
# Executable
# --------------------
add_executable(main
    main.cpp
    filterclass/filterclass.cpp
    exchangetype/exchangetype.cpp
    instrument/equity/equity.cpp
    instrument/future/future.cpp
    instrument/option/option.cpp
)

# --------------------
# Include paths
# --------------------
target_include_directories(main
    PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/external   # cppcodec
)

# --------------------
# Dependencies
# --------------------
find_package(ZLIB REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
# find_package(Boost REQUIRED COMPONENTS iostreams)

# --------------------
# Link libraries
# --------------------
target_link_libraries(main
    PRIVATE
        ZLIB::ZLIB
        # Boost::iostreams
        nlohmann_json::nlohmann_json
)

# --------------------
# Compile definitions
# --------------------
target_compile_definitions(main PRIVATE HAVE_ZLIB)
