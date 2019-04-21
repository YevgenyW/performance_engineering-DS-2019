//
// Created by Yevhen Pozdniakov on 4/20/19.
//

#ifndef HW1_TASKS_HPP
#define HW1_TASKS_HPP

#include <iostream>
#include <xmmintrin.h>
#include <smmintrin.h>

constexpr auto LEN = 33000u;
constexpr auto LEN2 = 240;
constexpr auto NTIMES1 = 100000u;
constexpr auto NTIMES2 = 200u;

constexpr auto sec_const = 1000000.0;

void test_task1_slow();
void test_task1_fast();

void test_task2_blas();
void test_task2();

#endif //HW1_TASKS_HPP
