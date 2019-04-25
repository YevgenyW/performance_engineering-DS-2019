//
// Created by Yevhen Pozdniakov on 4/22/19.
//
#include "tasks.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>

#include <iostream>
using namespace std;

namespace
{
    constexpr char* sub = (char*) "AVK";
    constexpr char* str = (char*) "XYZAfdffVKLAfdjkjfklfdnkljfdkl;VKRAVKPZA";
}

int strpos(const char *str, const char *sub)
{
    if (!str || !sub)
    {
        return -1;
    }

    auto ptr = strstr(str, sub);

    if (!ptr)
    {
        return -1;
    }

    return ptr - str;
}

void test_task3_slow()
{
    auto start = std::chrono::high_resolution_clock::now();
    int pos = -1;
    for (std::size_t i = 0; i < NTIMES3; ++i)
    {
        for (std::size_t j = 0; j < NTIMES3; ++j)
        {
            for (std::size_t k = 0; k < NTIMES3; ++k)
            {
//                std::cout<<i<<","<<j<<","<<k<<std::endl;
                pos = strpos(str, sub);
            }
        }
    }

    std::cout<<"Substring found at "<<pos<<std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto total_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("test_task3\t %lld ms\t\n", total_processing_time.count());
}
