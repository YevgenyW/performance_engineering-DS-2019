//
// Created by Yevhen Pozdniakov on 5/19/19.
//

#ifndef HW3_ALIAS_H
#define HW3_ALIAS_H

#include "utils.hpp"
#include <iostream>

struct Test1_CPU
{
    uint64_t perform(const img_t& img, colors channel)
    {
        return sum_of_pixels_in_channel(img, channel);
    }
    const char* desc()
    {
        return "test_task1";
    }
};

struct Test1_Threads
{
    uint64_t perform(const img_t& img, colors channel)
    {
        return sum_of_pixels_in_channel_threads(img, channel);
    }
    const char* desc()
    {
        return "test_task1_multi-threading";
    }
};

struct Test2_CPU
{
    uint64_t perform(const img_t& img, colors channel)
    {
        return min_in_channel(img, colors::red);
    }
    const char* desc()
    {
        return "test_task2";
    }
};

struct Test2_Threads
{
    uint64_t perform(const img_t& img, colors channel)
    {
        return min_in_channel_threads(img, colors::red);
    }
    const char* desc()
    {
        return "test_task2_multi-threading";
    }
};

#endif //HW3_ALIAS_H
