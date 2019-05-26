//
// Created by Yevhen Pozdniakov on 5/18/19.
//

#include "utils.hpp"
//#include "multi_process_funcs.hpp"

#include <mpi.h>
#include <vector>
#include <numeric>

template <typename Action>
void test()
{
    MPI_Status Stat;

    int num_processes;
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    auto img = read_bmp(path_to_image);

    auto num_slaves = num_processes - 1;

    uint8_t * block = nullptr;
    auto total_size = img.width*img.height;
    auto const block_size = total_size / num_slaves;

    if (rank == 0)
    {
        printf("Function \t Time \n");
        auto start = std::chrono::high_resolution_clock::now();

        std::cout << "red:    " << Action().perform_master(img, colors::red, num_slaves, block_size, Stat) << std::endl;
        std::cout << "green:  " << Action().perform_master(img, colors::green, num_slaves, block_size, Stat) << std::endl;
        std::cout << "blue:   " << Action().perform_master(img, colors::blue, num_slaves, block_size, Stat) << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        auto total_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout<<Action().desc()<<"\t"<< total_processing_time.count() << "\tms\n";
        printf("-----------------\n");

    }
    else
    {
        Action().perform_slave(num_slaves, block_size, Stat);
    }

    delete [] img.data;
}
