cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(LibYadroSorter VERSION 1.0)

include_directories(../include/)
add_library(LibYadroSorter line_emulate.cpp line_sorter.cpp line_sorting_emulate.cpp)
