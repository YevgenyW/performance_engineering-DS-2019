//
// Created by Yevhen Pozdniakov on 5/8/19.
//

#ifndef HW4_TASKS_H
#define HW4_TASKS_H

constexpr auto num_iterations = 1;

static const char * path_to_image = "../../data/img-2_small.bmp";

template <typename Action>
void test();

#include "test.ipp"

#endif //HW4_TASKS_H
