//
// Created by Yevhen Pozdniakov on 5/8/19.
//
#include "tasks.hpp"

#include <chrono>
#include <iostream>
#include <math.h>

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

//    std::cout << std::endl;
//    std::cout << "Name: " << filename << std::endl;
//    std::cout << "Width: " << img.width << std::endl;
//    std::cout << "Height: " << img.height << std::endl;

    int row_padded = (img.width*3 + 3) & (~3);
    img.data = new unsigned char[row_padded*img.height];
    unsigned char tmp;

    for(auto i = 0u; i < img.height; ++i)
    {
        auto start_idx = i*img.width*3;
        fread(&img.data[start_idx], sizeof(unsigned char), row_padded, f);
        for(auto j = 0u; j < img.width*3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            tmp = img.data[start_idx + j];
            img.data[start_idx + j] = img.data[start_idx + j + 2];
            img.data[start_idx + j+ 2] = tmp;

//            std::cout << "R: "<< (int)img.data[start_idx + j] << " G: " << (int)img.data[start_idx + j + 1]
//                      << " B: " << (int)img.data[start_idx + j +2]<< std::endl;
        }
    }

    fclose(f);
    return img;
}

uint64_t sum_of_pixels_in_channel(const img_t& img, colors channel)
{
    uint64_t sum = 0;

    auto start_idx = static_cast<int>(channel) - 1;

    for(auto i = start_idx; i < (img.width * img.height *3); i+=3)
    {
        sum+=img.data[i];
    }

    return sum;
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
        std::cout << "total: " << sum_of_pixels_in_channel(img, colors::blue) + sum_of_pixels_in_channel(img, colors::red) + sum_of_pixels_in_channel(img, colors::green) << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto total_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout<<"test_task1\t"<< total_processing_time.count() << "\tms\n";

    delete [] img.data;
}

uint8_t min_in_channel(const img_t& img, colors channel)
{
    uint8_t min = 0;

    auto start_idx = static_cast<int>(channel) - 1;

    for(auto i = start_idx; i < (img.height * img.height); i+=3)
    {
        if (min > img.data[i])
        {
            min = img.data[i];
        }
    }

    return min;
}

void test_task2()
{
    auto img = read_bmp("../data/img-2.bmp");

    auto start = std::chrono::high_resolution_clock::now();

    for (auto i = 0u; i < num_iterations; ++i)
    {
        min_in_channel(img, colors::red);
        min_in_channel(img, colors::green);
        min_in_channel(img, colors::blue);
//        std::cout << "min in red channel: " << (int)min_in_channel(img, colors::red) << std::endl;
//        std::cout << "min in green channel: " << (int)min_in_channel(img, colors::green) << std::endl;
//        std::cout << "min in blue channel: " << (int)min_in_channel(img, colors::blue) << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto total_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout<<"test_task2\t"<< total_processing_time.count() << "\tms\n";

    delete [] img.data;
}

img_t to_greyscale(const img_t& color_img)
{
    img_t grey_img;
    grey_img.height = color_img.height;
    grey_img.width = color_img.width;
    grey_img.data = new unsigned char[color_img.width * color_img.height];

    auto k = 0u;
    for(auto i = 0u; i < color_img.height; ++i)
    {
        auto start_idx = i*color_img.width*3;
        for(auto j = 0u; j < color_img.width*3; j += 3)
        {
            auto r = (double)color_img.data[start_idx + j + 0];
            auto g = (double)color_img.data[start_idx + j + 1];
            auto b = (double)color_img.data[start_idx + j + 2];

            r = r * 0.299;
            g = g * 0.587;
            b = b * 0.144;

            uint8_t grey = floor((r + g + b + 0.5));

            grey_img.data [k] = grey;
            ++k;
        }
    }
    return grey_img;
}

void print_color(const img_t& color_img)
{
    for(auto i = 0u; i < color_img.height; ++i)
    {
        auto start_idx = i*color_img.width*3;
        for(auto j = 0u; j < color_img.width*3; j+=3)
        {
            std::cout << (int)color_img.data[start_idx + j] << " ";
        }
        std::cout<<std::endl;
    }
}

void print_grey(const img_t& grey_img)
{
    for(auto i = 0u; i < grey_img.height; ++i)
    {
        auto start_idx = i*grey_img.width;
        for(auto j = 0u; j < grey_img.width; ++j)
        {
            std::cout << (int)grey_img.data[start_idx + j] << " ";
        }
        std::cout<<std::endl;
    }
}

void convert_to_integral(img_t& grey_img)
{
//first row
    for(auto i = 1u; i < grey_img.width; ++i)
    {
        grey_img.data[i]+=grey_img.data[i-1];
    }
//first column
    for(auto i = 1u; i < grey_img.height; ++i)
    {
        grey_img.data[i*grey_img.width]+=grey_img.data[(i-1)*grey_img.width];
    }
//all others elements
    for(auto i = 1u; i < grey_img.height; ++i)
    {
        auto start_idx = i*grey_img.width;
        for(auto j = 1u; j < grey_img.width; ++j)
        {
            grey_img.data[start_idx+j] += grey_img.data[start_idx+j-1]
                                          + grey_img.data[start_idx - grey_img.width + j]
                                          - grey_img.data[start_idx - grey_img.width + j - 1];
        }
    }
}

void test_task3()
{
    auto img = read_bmp("../data/img-2.bmp");
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