//
// Created by Yevhen Pozdniakov on 5/8/19.
//

#ifndef HW3_TASKS_H
#define HW3_TASKS_H

constexpr auto num_iterations = 1;

static const char * path_to_image = "../../data/img-2_big.bmp";

template <typename Action>
void test();

#include "test.ipp"

#endif //HW3_TASKS_H
