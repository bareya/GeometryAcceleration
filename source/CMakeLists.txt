include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Utils)
add_subdirectory(Core)
add_subdirectory(Geometry)
add_subdirectory(Acceleration)
add_subdirectory(Serialization)

# Add source to this project's executable
add_executable (nth_element_vs_sort "nth_element_vs_sort.cpp")

target_compile_definitions(nth_element_vs_sort
    PRIVATE
        DATA_DIR="${CMAKE_SOURCE_DIR}/data/"
        )

target_link_libraries(nth_element_vs_sort
    PRIVATE
        Core
        Geometry
        Serialization
        Acceleration
        )

if(${BUILD_PLUGINS})
    add_subdirectory(plugins)
endif(${BUILD_PLUGINS})