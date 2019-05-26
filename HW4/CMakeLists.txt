cmake_minimum_required(VERSION 3.12)
project(HW4)

set(CMAKE_CXX_STANDARD 14)

find_package(MPI REQUIRED)

add_executable(HW4 main.cpp utils.cpp)

target_link_libraries(HW4 PRIVATE MPI::MPI_C)
