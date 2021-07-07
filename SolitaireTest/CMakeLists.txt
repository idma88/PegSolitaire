cmake_minimum_required(VERSION 3.10.2)

project(SolitaireTest)

find_library(GTEST_LIB gtest ${CMAKE_BINARY_DIR}/lib/Debug)

#if(GTEST_LIB)
#    message("Gtest library found")
#else()
#    message("Gtest library not found")
#    message(${CMAKE_BINARY_DIR})
#endif()


#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR} *.cpp)

add_executable(testmain ${TEST_SRC_FILES})

target_link_libraries(testmain gtest gtest_main)


#add_executable(testmain testmain.cpp SolitaireTest.cpp)
#target_link_libraries(testmain gtest gmock_main)
add_test(NAME testmain COMMAND testmain)