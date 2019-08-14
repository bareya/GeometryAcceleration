project(Geometry CXX)

add_library(${PROJECT_NAME} STATIC "")

target_sources(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Mesh.h
        ${CMAKE_CURRENT_LIST_DIR}/Face.h
        ${CMAKE_CURRENT_LIST_DIR}/Triangle.h
        ${CMAKE_CURRENT_LIST_DIR}/Polygon.h
    PRIVATE
        Mesh.cpp
        Face.cpp
    )

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Core
    )
