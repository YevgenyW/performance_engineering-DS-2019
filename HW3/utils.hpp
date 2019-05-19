//
// Created by Yevhen Pozdniakov on 5/18/19.
//

#ifndef HW3_UTILS_H
#define HW3_UTILS_H

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
};

img_t read_bmp(const char* filename);

uint64_t sum_of_pixels_in_channel(const img_t& img, colors channel);
uint64_t sum_of_pixels_in_channel_threads(const img_t& img, colors channel);
uint8_t min_in_channel(const img_t& img, colors channel);
uint8_t min_in_channel_threads(const img_t& img, colors channel);
img_t to_greyscale(const img_t& color_img);
void print_color(const img_t& color_img);
void print_grey(const img_t& grey_img);
void convert_to_integral(img_t& grey_img);


#endif //HW3_UTILS_H
