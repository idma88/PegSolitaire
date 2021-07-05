cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

set(field_dir ../Field/)
set(common_dir ../Common/)

file(GLOB_RECURSE common_sources ${field_dir}*.cpp ${common_dir}*.cpp)  
file(GLOB_RECURSE common_headers ${field_dir}*.h ${common_dir}*.h)

file(GLOB_RECURSE src_sources *.cpp)
file(GLOB_RECURSE src_headers *.h)

set(sources
    ${src_sources}
    ${src_headers}
    ${common_sources}
    ${common_headers}
)

add_executable(${PROJECT_NAME} ${sources})

find_library(GLOG_LIB glogd ${CMAKE_BINARY_DIR}/glog/Debug)
if(GLOG_LIB)
    message ("GLOG FOUND!!!")
else()
    message ("GLOG NOT FOUND!!!")
endif()

target_link_libraries(${PROJECT_NAME} glog)