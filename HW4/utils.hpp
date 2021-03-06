//
// Created by Yevhen Pozdniakov on 5/18/19.
//

#ifndef HW4_UTILS_H
#define HW4_UTILS_H

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

uint8_t * get_channel_data(const img_t& img, colors color);
img_t read_bmp(const char* filename);

#endif //HW4_UTILS_H
