cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(YadroSortUnitTest VERSION 1.0)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(../include/)
link_directories(../src/)

add_executable(RunTests tests.cpp)
target_link_libraries(RunTests LibYadroSorter)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../src/ ${CMAKE_CURRENT_BINARY_DIR}/src/)

target_link_libraries(RunTests ${GTEST_LIBRARIES} pthread)
