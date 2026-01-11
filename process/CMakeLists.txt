add_library(process
    process.cpp
)

target_include_directories(process
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)