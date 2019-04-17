all: main.cpp
	gcc -O3 -g3 -march=haswell -ftree-vectorize -fno-omit-frame-pointer -lstdc++ -o HW1 ./main.cpp


# -march=haswell -ftree-vectorize -fopt-info-vec -fno-omit-frame-pointer


# originally it was so
#   gcc -O0 -g3 -fno-omit-frame-pointer -lstdc++ -o test ./test.c
#   gcc -O1 -g3 -march=ivybridge -ftree-vectorize -fopt-info-vec -fno-omit-frame-pointer -lstdc++ -o test ./test.c

#-march=haswell


#-ftree-vectorize(enable vectorization)
#-fno-tree-vectorize(disable vectorization)
#-march=‘you-rarchitecture’
#-O3 (enable vectorizationby default)
#-fopt-info-vec(enable messages about vectorization)
#-fopt-info-vec-missed (enable messages about missed vectorization)