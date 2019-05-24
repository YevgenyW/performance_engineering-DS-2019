//
// Created by Yevhen Pozdniakov on 5/18/19.
//

#include "utils.hpp"

#include <algorithm>
#include <math.h>

namespace
{
    uint8_t * get_channel_data(const img_t& img, colors color)
    {
        uint8_t* data = nullptr;

        if (color == colors::red)
            data = img.r;
        else if (color == colors::green)
            data = img.g;
        else
            data = img.b;

        return data;
    }
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
    img.r = &img.data[0];
    img.g = &img.data[img.height*img.width];
    img.b = &img.data[2*img.height*img.width];
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

uint64_t convert_to_integral(img_t& img, colors color)
{
    uint8_t* data = get_channel_data(img, color);

//first row
    for(auto i = 1u; i < img.width; ++i)
    {
        data[i]+=data[i-1];
    }

//first column
    for(auto i = 1u; i < img.height; ++i)
    {
        data[i*img.width]+=data[(i-1)*img.width];
    }

//all others elements
    for(auto i = 1u; i < img.height; ++i)
    {
        auto start_idx = i*img.width;
        for(auto j = 1u; j < img.width; ++j)
        {
            data[start_idx+j] += data[start_idx+j-1]
                                + data[start_idx - img.width + j]
                                - data[start_idx - img.width + j - 1];
        }
    }

    return data[img.width*img.height - 1];
}
