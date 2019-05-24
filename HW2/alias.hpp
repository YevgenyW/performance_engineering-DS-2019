//
// Created by Yevhen Pozdniakov on 5/19/19.
//

#ifndef HW2_ALIAS_H
#define HW2_ALIAS_H

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
        return "sum(CPU)";
    }
};

struct Test2_CPU
{
    uint64_t perform(const img_t& img, colors channel)
    {
        return min_in_channel(img, channel);
    }
    const char* desc()
    {
        return "min(CPU)";
    }
};

struct Test3_CPU
{
    uint64_t perform(const img_t& img, colors channel)
    {
        return convert_to_integral(const_cast<img_t&>(img), channel);
    }
    const char* desc()
    {
        return "integral image(CPU)";
    }
};

#endif //HW2_ALIAS_H
