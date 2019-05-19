//
// Created by Yevhen Pozdniakov on 5/18/19.
//

#include "tasks.hpp"

template<typename T, typename res_T>
struct accumulate_block
{
    void operator()(T* first, T* last, res_T& sum)
    {
        for (auto ptr = first; ptr < last; ++ptr)
        {
            sum += *ptr;
        }
    }
};

template<typename T, typename res_T>
struct min_in_block
{
    void operator()(T* first, T* last, res_T& min)
    {
        min = *first;
        for (auto ptr = first; ptr < last; ++ptr)
        {
            if (min > *ptr)
            min = *ptr;
        }
    }
};

template<typename T, typename Res_T, typename Action, typename Res>
Res_T parallel_action(T * first, T * last, T init);

#include "multi_thread_funcs.ipp"