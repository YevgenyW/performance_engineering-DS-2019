//
// Created by Yevhen Pozdniakov on 5/8/19.
//
#include "tasks.hpp"

#include <png.h>

#include <chrono>
#include <iostream>

constexpr auto num_iterations = 50;

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

uint64_t sum_of_pixels_in_channel(const img_t& img, colors channel)
{
    uint64_t sum = 0;

    auto start_idx = static_cast<int>(channel) - 1;

    for(auto i = start_idx; i < (img.height * img.height); i+=3)
    {
        sum+=img.data[i];
    }

    return sum;
}

img_t read_bmp(const char* filename)
{
    FILE* f = fopen(filename, "rb");

    if(f == NULL)
    {
        throw "Argument Exception";
    }

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    img_t img;
    // extract image height and width from header
    img.width = *(int*)&info[18];
    img.height = *(int*)&info[22];

    std::cout << std::endl;
    std::cout << "Name: " << filename << std::endl;
    std::cout << "Width: " << img.width << std::endl;
    std::cout << "Height: " << img.height << std::endl;

    int row_padded = (img.width*3 + 3) & (~3);
    img.data = new unsigned char[row_padded*img.height];
    unsigned char tmp;

    for(int i = 0; i < img.height; i++)
    {
        auto start_idx = i*img.height;
        fread(&img.data[start_idx], sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < img.width*3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            tmp = img.data[start_idx + j];
            img.data[start_idx + j] = img.data[start_idx + j +2];
            img.data[start_idx + j+2] = tmp;

//            std::cout << "R: "<< (int)img.data[start_idx + j] << " G: " << (int)img.data[start_idx + j + 1]
//                      << " B: " << (int)img.data[start_idx + j +2]<< std::endl;
        }
    }

    fclose(f);
    return img;
}

void test_task1()
{
    auto img = read_bmp("../data/img-2.bmp");

    auto start = std::chrono::high_resolution_clock::now();

    for (auto i = 0u; i < num_iterations; ++i)
    {
        sum_of_pixels_in_channel(img, colors::red);
        sum_of_pixels_in_channel(img, colors::green);
        sum_of_pixels_in_channel(img, colors::blue);
//        std::cout << "sum of pixels in red channel: " << sum_of_pixels_in_channel(img, colors::red) << std::endl;
//        std::cout << "sum of pixels in gree channel: " << sum_of_pixels_in_channel(img, colors::green) << std::endl;
//        std::cout << "sum of pixels in blue channel: " << sum_of_pixels_in_channel(img, colors::blue) << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto total_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("test_task1\t %llu ms\t\n", total_processing_time.count());

    delete [] img.data;
}