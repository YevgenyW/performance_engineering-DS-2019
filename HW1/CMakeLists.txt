cmake_minimum_required(VERSION 3.12)
project(HW1)

set(CMAKE_CXX_STANDARD 14)

SET(SLOW_COMPILE_FLAGS "-O0 -g3 -fno-tree-vectorize -fno-omit-frame-pointer -I/usr/local/opt/openblas/include")
SET(FAST_COMPILE_FLAGS "-O3 -g3 -march=haswell -ftree-vectorize -fno-omit-frame-pointer")

SET(CMAKE_CXX_FLAGS  "${FAST_COMPILE_FLAGS}")

find_package( BLAS REQUIRED )
message( STATUS BLAS found: ${BLAS_LIBRARIES} )

add_executable(HW1 main.cpp task1.cpp task2.cpp task3.cpp)

target_include_directories(HW1
        PRIVATE
        /usr/local/opt/openblas/include)

target_link_libraries(HW1
        ${BLAS_LIBRARIES})
