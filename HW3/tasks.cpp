//
// Created by Yevhen Pozdniakov on 5/8/19.
//
#include "tasks.hpp"
#include "utils.hpp"
#include "multi_thread_funcs.hpp"

#include <chrono>
#include <iostream>
#include <math.h>

void test_task3()
{
    auto img = read_bmp(path_to_image);
    auto grey_img = to_greyscale(img);
    
    convert_to_integral(grey_img);

    auto start = std::chrono::high_resolution_clock::now();

    for (auto i = 0u; i < num_iterations; ++i)
    {
        convert_to_integral(grey_img);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto total_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout<<"test_task3\t"<< total_processing_time.count() << "\tms\n";

    delete [] grey_img.data;
    delete [] img.data;
}