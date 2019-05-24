//
// Created by Yevhen Pozdniakov on 5/18/19.
//

#include "utils.hpp"

template <typename Action>
void test()
{
    auto img = read_bmp(path_to_image);

    auto start = std::chrono::high_resolution_clock::now();

    for (auto i = 0u; i < num_iterations; ++i)
    {
        std::cout << "red:    " << Action().perform(img, colors::red) << std::endl;
        std::cout << "green:  " << Action().perform(img, colors::green) << std::endl;
        std::cout << "blue:   " << Action().perform(img, colors::blue) << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto total_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout<<Action().desc()<<"\t"<< total_processing_time.count() << "\tms\n";

    delete [] img.data;
}

