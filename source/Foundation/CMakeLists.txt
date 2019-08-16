project(Foundation CXX)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/Types.h
        ${CMAKE_CURRENT_LIST_DIR}/Vector3.h
        ${CMAKE_CURRENT_LIST_DIR}/AABBox.h
        ${CMAKE_CURRENT_LIST_DIR}/Prim.h
    )

target_compile_features(${PROJECT_NAME}
    INTERFACE
        cxx_std_11
    )

target_compile_options(${PROJECT_NAME}
    INTERFACE
         $<$<CXX_COMPILER_ID:MSVC>:/W4>
         $<$<CXX_COMPILER_ID:GNU>:-Wall>
    )