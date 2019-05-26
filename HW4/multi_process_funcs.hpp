//
// Created by Yevhen Pozdniakov on 5/18/19.
//

#include "test.hpp"

#include <mpi.h>

#include <algorithm>
#include <numeric>
#include <vector>

constexpr auto tag = 0u;

uint64_t master_action_accumulate(const img_t& img, colors color, std::size_t num_slaves, std::size_t block_size, MPI_Status& Stat)
{
    uint8_t* data = get_channel_data(img, color);

    std::vector<uint64_t> results(num_slaves);

    auto block = &data[0];
    for(auto i = 0u; i < num_slaves; ++i)
    {
        auto dest = i + 1;

        MPI_Send(block, block_size, MPI_UNSIGNED_CHAR, dest, tag, MPI_COMM_WORLD);
        auto source = i + 1;
        MPI_Recv(&results[i], 1, MPI_UNSIGNED_LONG_LONG, source, tag, MPI_COMM_WORLD, &Stat);

        block+=block_size;
    }
    auto sum = std::accumulate(results.begin(), results.end(), 0);
    sum = std::accumulate(block, data + img.width*img.height, sum);

    return sum;
}

void slave_action_accumulate(std::size_t num_slaves, std::size_t block_size, MPI_Status& Stat)
{
    auto block = new uint8_t [block_size];
    for(auto i = 0u; i < num_slaves; ++i)
    {
        MPI_Recv(block, block_size, MPI_UNSIGNED_CHAR, 0, tag, MPI_COMM_WORLD, &Stat);
        uint64_t sum = std::accumulate(block, block + block_size, 0);
        MPI_Send(&sum, 1, MPI_UNSIGNED_LONG_LONG, 0, tag, MPI_COMM_WORLD);
    }
    delete [] block;
}

uint64_t master_action_min(const img_t& img, colors color, std::size_t num_slaves, std::size_t block_size, MPI_Status& Stat)
{
    uint8_t* data = get_channel_data(img, color);

    std::vector<uint8_t> mins(num_slaves);

    auto block = &data[0];
    for(auto i = 0u; i < num_slaves; ++i)
    {
        auto dest = i + 1;

        MPI_Send(block, block_size, MPI_UNSIGNED_CHAR, dest, tag, MPI_COMM_WORLD);
        auto source = i + 1;
        MPI_Recv(&mins[i], 1, MPI_UNSIGNED_CHAR, source, tag, MPI_COMM_WORLD, &Stat);

        block+=block_size;
    }
    auto min = std::min_element(mins.begin(), mins.end());

    return *min;
}

void slave_action_min(std::size_t num_slaves, std::size_t block_size, MPI_Status& Stat)
{
    auto block = new uint8_t [block_size];
    for(auto i = 0u; i < num_slaves; ++i)
    {
        MPI_Recv(block, block_size, MPI_UNSIGNED_CHAR, 0, tag, MPI_COMM_WORLD, &Stat);
        uint8_t min = *(std::min_element(block, block + block_size));

        MPI_Send(&min, 1, MPI_UNSIGNED_CHAR, 0, tag, MPI_COMM_WORLD);
    }
    delete [] block;
}