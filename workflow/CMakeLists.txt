add_library(workflow
    workflow.cpp
)

target_include_directories(workflow
    PUBLIC
        ${CMAKE_SOURCE_DIR}
)
