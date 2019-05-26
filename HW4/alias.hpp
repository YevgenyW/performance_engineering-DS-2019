//
// Created by Yevhen Pozdniakov on 5/19/19.
//

#ifndef HW4_ALIAS_H
#define HW4_ALIAS_H

#include "utils.hpp"
#include "multi_process_funcs.hpp"

#include <mpi.h>
#include <iostream>

struct Test1_Processes
{
    uint64_t perform_master(const img_t& img, colors color, std::size_t num_slaves, std::size_t block_size, MPI_Status& Stat)
    {
        return master_action_accumulate(img, color, num_slaves, block_size, Stat);
    }

    void perform_slave(std::size_t num_slaves, std::size_t block_size, MPI_Status& Stat)
    {
        slave_action_accumulate(num_slaves, block_size, Stat);
    }

    const char* desc()
    {
        return "sum(multi-threading)";
    }
};

struct Test2_Processes
{
    uint64_t perform_master(const img_t& img, colors color, std::size_t num_slaves, std::size_t block_size, MPI_Status& Stat)
    {
        return master_action_min(img, color, num_slaves, block_size, Stat);
    }

    void perform_slave(std::size_t num_slaves, std::size_t block_size, MPI_Status& Stat)
    {
        slave_action_min(num_slaves, block_size, Stat);
    }

    const char* desc()
    {
        return "min(multi-threading)";
    }
};

#endif //HW4_ALIAS_H
