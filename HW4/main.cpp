//
// Created by Yevhen Pozdniakov on 5/6/19.
//
#include "alias.hpp"
#include "test.hpp"
#include "utils.hpp"

#include <mpi.h>

#include <vector>
#include <numeric>

int main(int argc, char *argv[]) {

    MPI_Init(&argc,&argv);

    MPI_Status Stat;

    int num_processes;
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    auto img = read_bmp(path_to_image);
    uint8_t* data = get_channel_data(img, colors::red);

    auto num_slaves = num_processes - 1;

    uint8_t * block = nullptr;
    auto total_size = img.width*img.height;
    auto const block_size = total_size / num_slaves;

    auto tag = 0;

    if (rank == 0)
    {
        std::vector<uint64_t> results(num_slaves);

        block = &data[0];
        for(auto i = 0u; i < num_slaves; ++i)
        {
            auto dest = i + 1;

            MPI_Send(block, block_size, MPI_UNSIGNED_CHAR, dest, tag, MPI_COMM_WORLD);
            auto source = i + 1;
            MPI_Recv(&results[i], 1, MPI_UNSIGNED_LONG_LONG, source, tag, MPI_COMM_WORLD, &Stat);

            block+=block_size;
        }
        auto sum = std::accumulate(results.begin(), results.end(), 0);
        sum = std::accumulate(block, data + total_size, sum);

        std::cout<<sum<<std::endl;
    }
    else
    {
        block = new uint8_t [block_size];
        for(auto i = 0u; i < num_slaves; ++i)
        {
            MPI_Recv(block, block_size, MPI_UNSIGNED_CHAR, 0, tag, MPI_COMM_WORLD, &Stat);
            uint64_t sum = std::accumulate(block, block + block_size, 0);

            MPI_Send(&sum, 1, MPI_UNSIGNED_LONG_LONG, 0, tag, MPI_COMM_WORLD);
        }
        delete [] block;
    }

    MPI_Finalize();

    return 0;
}

