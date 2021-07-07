cmake_minimum_required(VERSION 3.10.2)

project(SolitaireTest)

find_library(GTEST_LIB gtestd ${CMAKE_BINARY_DIR}/lib/Debug)

if(GTEST_LIB)
    message("Gtest library found")
else()
    message("Gtest library not found")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

message("CMAKE_BINARY_DIR = " ${CMAKE_BINARY_DIR})
include_directories("${CMAKE_BINARY_DIR}/googletest")


if (CMAKE_VERSION VERSION_LESS 2.8.11)

    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")

    message(gtest_SOURCE_DIR ${gtest_SOURCE_DIR})
    message(gmock_SOURCE_DIR ${gmock_SOURCE_DIR})  

endif()

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR} *.cpp)

add_executable(testmain ${TEST_SRC_FILES})
target_link_libraries(testmain gtest gtest_main)
add_test(NAME testmain COMMAND testmain)