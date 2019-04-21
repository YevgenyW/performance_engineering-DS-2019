cmake_minimum_required(VERSION 3.12)
project(HW1)

set(CMAKE_CXX_STANDARD 14)

SET(SLOW_COMPILE_FLAGS "-O0 -g3 -fno-tree-vectorize -fno-omit-frame-pointer -I/usr/local/opt/openblas/include")
SET(FAST_COMPILE_FLAGS "-O3 -g3 -march=haswell -ftree-vectorize -fno-omit-frame-pointer")

SET(CMAKE_CXX_FLAGS  "${FAST_COMPILE_FLAGS}")

find_package( BLAS REQUIRED )
message( STATUS BLAS found: ${BLAS_LIBRARIES} )

add_executable(HW1 main.cpp task1.cpp task2.cpp)

target_include_directories(HW1
        PRIVATE
        /usr/local/opt/openblas/include)

target_link_libraries(HW1
        ${BLAS_LIBRARIES})
#
##FIND_PATH(OpenBLAS_INCLUDE_DIR NAMES
##        cblas.h PATHS ${Open_BLAS_INCLUDE_SEARCH_PATHS}
##        )
#
##FIND_LIBRARY(OpenBLAS_LIB NAMES
##        openblas PATHS ${Open_BLAS_LIB_SEARCH_PATHS}
##        )
#
#target_include_directories(HW1
#        PRIVATE
#        /usr/local/opt/openblas/include)
##
#link_directories(${CMAKE_SOURCE_DIR}/lib)
#
#target_link_libraries(HW1 ${OpenBLAS_LIB})

#-ftree-vectorize(enable vectorization)
#-fno-tree-vectorize(disable vectorization)
#-march=‘you-rarchitecture’
#-O3 (enable vectorizationby default)
#-fopt-info-vec(enable messages about vectorization)
#-fopt-info-vec-missed (enable messages about missed vectorization)