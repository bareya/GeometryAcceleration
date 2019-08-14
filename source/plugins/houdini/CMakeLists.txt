project(SOP_BVH CXX)

find_package(Houdini REQUIRED)

add_library(${PROJECT_NAME} SHARED SOP_BVH.cpp)

target_link_libraries(${PROJECT_NAME}
    PUBLIC 
        Geometry
        Acceleration
        Houdini
    )
