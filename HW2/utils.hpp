//
// Created by Yevhen Pozdniakov on 5/18/19.
//

#ifndef HW2_UTILS_H
#define HW2_UTILS_H

#include <iostream>

enum class colors : uint8_t
{
    red = 1,
    green = 2,
    blue = 3,
    last
};

struct img_t
{
    int width;
    int height;
    uint8_t * data;
    uint8_t * r;
    uint8_t * g;
    uint8_t * b;
};

img_t read_bmp(const char* filename);

uint64_t sum_of_pixels_in_channel(const img_t& img, colors channel);

uint8_t min_in_channel(const img_t& img, colors channel);

uint64_t convert_to_integral(img_t& img, colors color);

#endif //HW2_UTILS_H
