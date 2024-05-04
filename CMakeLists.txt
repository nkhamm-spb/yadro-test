cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(YadroTest VERSION 1.0)

include_directories(include/)
link_directories(src/)
add_executable(YadroTest main.cpp)
target_link_libraries(YadroTest LibYadroSorter)
add_subdirectory(src/)