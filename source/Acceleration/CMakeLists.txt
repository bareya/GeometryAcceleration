project(Acceleration CXX)

add_library(${PROJECT_NAME} STATIC "")

target_sources(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/BVH.h
    PRIVATE
        BVH.cpp
    )

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Geometry
    )
