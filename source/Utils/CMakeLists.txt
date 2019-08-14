project(Utils CXX)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/Parsing.h
        ${CMAKE_CURRENT_LIST_DIR}/Format.h
    )

target_compile_features(${PROJECT_NAME}
    INTERFACE
        cxx_std_11
)
