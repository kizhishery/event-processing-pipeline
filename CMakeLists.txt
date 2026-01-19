cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Dependencies ----
find_package(ZLIB REQUIRED)
find_package(CURL REQUIRED)
# find_package(nlohmann_json CONFIG REQUIRED)


# ---- Submodules ----
add_subdirectory(utils)
add_subdirectory(process)
add_subdirectory(postJson)
add_subdirectory(workflow)
add_subdirectory(FilterClass)
add_subdirectory(ExchangeType)
add_subdirectory(Instrument)

# ---- Executable ----
add_executable(main main.cpp)

# the file which link other library must be defined at top 
target_link_libraries(main
    PRIVATE
        workflow
        process
        utils
        postJson
        filterclass
        exchangetype
        instrument
        # nlohmann_json::nlohmann_json
)

target_compile_definitions(main PRIVATE HAVE_ZLIB)
