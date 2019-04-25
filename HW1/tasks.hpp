//
// Created by Yevhen Pozdniakov on 4/20/19.
//

#ifndef HW1_TASKS_HPP
#define HW1_TASKS_HPP

#include <iostream>
#include <xmmintrin.h>
#include <smmintrin.h>

constexpr auto LEN = 33000u;
constexpr auto LEN2 = 100; // should be proportional to 4
constexpr auto NTIMES1 = 100000u;
constexpr auto NTIMES2 = 2000u;
constexpr auto NTIMES3 = 500u;

constexpr auto sec_const = 1000000.0;

void test_task1_slow();
void test_task1_SSE();

void test_task2_blas();
void test_task2_SSE();

void test_task3_strstr();
void test_task3_slow();
void test_task3_SSE();

#endif //HW1_TASKS_HPP
