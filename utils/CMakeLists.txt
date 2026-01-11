add_library(utils
    gzip_json.cpp
)

target_include_directories(utils
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(utils
    PUBLIC
        ZLIB::ZLIB
)
