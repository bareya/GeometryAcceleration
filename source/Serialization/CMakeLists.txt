project(Serialization CXX)

add_library(${PROJECT_NAME} STATIC "")

target_sources(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/MeshSerializer.h
        ${CMAKE_CURRENT_LIST_DIR}/ObjMeshSerializer.h
    PRIVATE
        MeshSerializer.cpp
        ObjMeshSerializer.cpp
    )

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Geometry
        Utils
    )
