cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include/)
add_executable(YadroTest main.cpp line_emulate.cpp line_sorter.cpp line_sorting_emulate.cpp)
