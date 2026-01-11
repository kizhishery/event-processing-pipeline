# cmake_minimum_required(VERSION 3.16)
# project(main LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

# add_executable(main
#     main.cpp
#     utils/gzip_json.cpp
#     process/process.cpp
#     postJson/postJson.cpp
#     workflow/workflow.cpp
#     filterclass/filterclass.cpp
#     instrument/equity/equity.cpp
#     instrument/future/future.cpp
#     instrument/option/option.cpp
#     exchangetype/exchangetype.cpp
# )

# target_include_directories(main
#     PRIVATE
#         ${CMAKE_SOURCE_DIR}
# )

# find_package(ZLIB REQUIRED)
# find_package(CURL REQUIRED)
# find_package(nlohmann_json CONFIG REQUIRED)

# target_link_libraries(main
#     PRIVATE
#         ZLIB::ZLIB
#         CURL::libcurl
#         nlohmann_json::nlohmann_json
# )

# target_compile_definitions(main PRIVATE HAVE_ZLIB)


cmake_minimum_required(VERSION 3.16)
project(main LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Dependencies ----
find_package(ZLIB REQUIRED)
find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# ---- Submodules ----
add_subdirectory(utils)
add_subdirectory(process)
add_subdirectory(postJson)
add_subdirectory(workflow)
add_subdirectory(filterclass)
add_subdirectory(exchangetype)
add_subdirectory(instrument)

# ---- Executable ----
add_executable(main main.cpp)

# order is important build first which links to other hence most used linked file at bottom
target_link_libraries(main
    PRIVATE
        workflow
        process
        utils
        postJson
        filterclass
        exchangetype
        instrument
        nlohmann_json::nlohmann_json
)

target_compile_definitions(main PRIVATE HAVE_ZLIB)
