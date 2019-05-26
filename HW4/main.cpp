//
// Created by Yevhen Pozdniakov on 5/6/19.
//
#include "alias.hpp"
#include "test.hpp"
#include "utils.hpp"

#include <mpi.h>

#include <numeric>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc > 1 && *argv[1] == '1')
    {
        // run first task
        MPI_Init(&argc, &argv);
        test<Test1_Processes>();
        MPI_Finalize();
    }
    else
    {
        // run second task
        MPI_Init(&argc, &argv);
        test<Test2_Processes>();
        MPI_Finalize();
    }

    return 0;
}

