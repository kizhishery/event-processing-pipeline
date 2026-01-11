add_library(postJson
    postJson.cpp
)

target_include_directories(postJson
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(utils
    PUBLIC
        CURL::libcurl
)