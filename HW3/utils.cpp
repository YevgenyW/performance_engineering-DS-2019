//
// Created by Yevhen Pozdniakov on 5/18/19.
//

#include "utils.hpp"
#include "multi_thread_funcs.hpp"

#include <math.h>

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
    img.data = new uint8_t [row_padded*img.height];
    uint8_t * buf = new uint8_t [row_padded];
    for(auto i = 0u; i < img.height; ++i)
    {
//        auto start_idx = i*img.width*3;
        auto start_idx_r = i*img.width;
        auto start_idx_g = i*img.width + img.height*img.width;
        auto start_idx_b = i*img.width + img.height*img.width*2;
        fread(buf, sizeof(uint8_t), row_padded, f);
        auto k = 0u;
        for(auto j = 0u; j < row_padded; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            img.data[start_idx_r + k] = buf[j+2];// == 0 ? 1 : buf[j+2];
            img.data[start_idx_g + k] = buf[j+1];
            img.data[start_idx_b + k] = buf[j];
            ++k;

//            std::cout << "R: "<< (int)img.data[start_idx_r + j] << " G: " << (int)img.data[start_idx_g + j]
//                      << " B: " << (int)img.data[start_idx_b + j]<< std::endl;
        }
    }
    delete [] buf;
    fclose(f);
    return img;
}

uint64_t sum_of_pixels_in_channel(const img_t& img, colors channel)
{
    uint64_t sum = 0;

    auto start_idx = (static_cast<int>(channel) - 1) * img.width*img.height;
    for(auto i = start_idx; i < start_idx + (img.width * img.height); i++)
    {
        sum+=img.data[i];
    }

    return sum;
}

uint64_t sum_of_pixels_in_channel_threads(const img_t& img, colors channel)
{
    auto start_idx = (static_cast<int>(channel) - 1) * img.width*img.height;
    auto end_idx = start_idx + img.width*img.height;

    return parallel_action<uint8_t,
            uint64_t,
            accumulate_block<uint8_t, uint64_t>,
            accumulate_block<uint64_t, uint64_t> >
                                       (&img.data[start_idx]
                                               , &img.data[end_idx+1]
                                               , 0);
}

uint8_t min_in_channel(const img_t& img, colors channel)
{
    uint8_t min = 255;

    auto start_idx = (static_cast<uint8_t >(channel) - 1) * img.width*img.height;
    auto end_idx = start_idx + img.width*img.height;

    for(auto i = start_idx; i < end_idx; i++)
    {
        if (min > img.data[i])
        {
            min = img.data[i];
        }
    }

    return min;
}

uint8_t min_in_channel_threads(const img_t& img, colors channel)
{
    uint8_t min = 255;

    auto start_idx = (static_cast<uint8_t >(channel) - 1) * img.width*img.height;
    auto end_idx = start_idx + img.width*img.height;

    return parallel_action<uint8_t,
            uint64_t,
            min_in_block<uint8_t, uint64_t>,
            min_in_block<uint64_t, uint64_t> >
            (&img.data[start_idx]
                    , &img.data[end_idx+1]
                    , 0);
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
