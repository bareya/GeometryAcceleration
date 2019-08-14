cmake_minimum_required (VERSION 3.8)
project ("GeometryAcceleration")

option(BUILD_PLUGINS OFF)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")

add_subdirectory("source")
#add_subdirectory("tests")