cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)



file(GLOB_RECURSE src_sources *.cpp)
file(GLOB_RECURSE src_headers *.h)

set(sources
    ${src_sources}
    ${src_headers}
)

add_executable(${PROJECT_NAME} ${sources})