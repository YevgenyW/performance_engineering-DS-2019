//
// Created by Yevhen Pozdniakov on 5/18/19.
//

#include "test.hpp"

#include <thread>
#include <vector>

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
Res_T parallel_action(T * first, T * last, T init)
{
    Res_T const length= last - first;

    if (!length)
    {
        return init;
    }

    Res_T const min_per_thread = 25;

    Res_T const max_threads=
            (length+min_per_thread - 1) / min_per_thread;

    Res_T const hardware_threads=
            std::thread::hardware_concurrency();

    Res_T const num_threads=
            std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    Res_T const block_size = length / num_threads;

    std::vector<Res_T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);

    auto block_start = first;

    for(auto i = 0u; i < (num_threads-1); ++i)
    {
        auto block_end = block_start + block_size;

        threads[i] = std::thread(
                Action(),
                block_start, block_end, std::ref(results[i]));

        block_start=block_end;
    }
    accumulate_block<T, Res_T>()(
            block_start, last, results[num_threads-1]);

    std::for_each(threads.begin(),threads.end(),
                  std::mem_fn(&std::thread::join));

    Res_T res = 0;
    Res()(&results[0], &results[num_threads], res);

    return res;
}
