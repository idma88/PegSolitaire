cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

set(field_dir ../Field/)
set(common_dir ../Common/)
set(game_dir ../Game/)
set(ui_dir ../UI/)

file(GLOB_RECURSE common_sources ${field_dir}*.cpp ${common_dir}*.cpp
     ${game_dir}*.cpp ${ui_dir}*.cpp)
file(GLOB_RECURSE common_headers ${field_dir}*.h ${common_dir}*.h
     ${game_dir}*.h ${ui_dir}*.h)

file(GLOB_RECURSE src_sources *.cpp)
file(GLOB_RECURSE src_headers *.h)

# set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/libs/SFML-2.5.1-windows-vc15-64-bit/")

find_package(
  SFML 2.5
  COMPONENTS system window graphics
  REQUIRED)

set(sources ${src_sources} ${src_headers} ${common_sources} ${common_headers})

add_executable(${PROJECT_NAME} ${sources})

find_library(GLOG_LIB glogd ${CMAKE_BINARY_DIR}/glog/Debug)
if(GLOG_LIB)
  message("GLOG FOUND!!!")
else()
  message("GLOG NOT FOUND!!!")
endif()

target_link_libraries(${PROJECT_NAME} glog sfml-system sfml-window
                      sfml-graphics)
