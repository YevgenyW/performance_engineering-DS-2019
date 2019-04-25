//
// Created by Yevhen Pozdniakov on 4/20/19.
//

#include "tasks.hpp"

using namespace std;

float a[LEN] __attribute__((aligned(16))) = {0};
float b[LEN] __attribute__((aligned(16))) = {0};
float c[LEN] __attribute__((aligned(16))) = {0};
float d[LEN] __attribute__((aligned(16))) = {0};
float res[LEN] __attribute__((aligned(16))) = {0};

template <typename T>
void sum_fast(const T* arr1, const T* arr2, T* res, std::size_t N)
{
    T sum = 0;
    for (std::size_t i = 0; i < N; i+=sizeof(T))
    {
        auto chunk = _mm_add_ps(_mm_load_ps(arr1), _mm_load_ps(arr2));
        _mm_store_ps(&res[i], chunk);
    }
}

template <typename T>
void mult_fast(const T* arr1, const T* arr2, T* res, std::size_t N)
{
    for (std::size_t i = 0; i < N; i+=sizeof(T))
    {
        auto chunk = _mm_mul_ps(_mm_load_ps(arr1), _mm_load_ps(arr2));
        _mm_store_ps(&res[i], chunk);
    }
}

template <typename T>
void task1_fast(const T* A, const T* B, const T* C, const T* D, T* res, std::size_t N)
{
//    A*B + C*D,
    for (std::size_t i = 0; i < N; i+=sizeof(T))
    {
        auto chunk = _mm_add_ps(_mm_mul_ps(_mm_load_ps(&A[i]), _mm_load_ps(&B[i])),
                                _mm_mul_ps(_mm_load_ps(&C[i]), _mm_load_ps(&D[i])));
        _mm_store_ps(&res[i], chunk);
    }
}

template <typename T>
void task1_slow(const T* A, const T* B, const T* C, const T* D, T* res, std::size_t N)
{
    for (std::size_t i = 0; i < N; ++i)
    {
        res[i] = A[i] * B[i] + C[i] * D[i];
    }
}

void test_task1_slow()
{
    clock_t start_t;
    clock_t end_t;
    clock_t clock_delta;
    float clock_delta_sec;

    start_t = clock();

    for (int n = 0; n < NTIMES1; n++)
    {
        task1_slow(&a[0], &b[0], &c[0], &d[0], &res[0], LEN);
    }
    end_t = clock();
    clock_delta = end_t - start_t;
    clock_delta_sec = (float) (clock_delta / sec_const);
    printf("test_task1_slow\t %.2f s\t\n", clock_delta_sec);
}

void test_task1_SSE()
{
    clock_t start_t;
    clock_t end_t;
    clock_t clock_delta;
    float clock_delta_sec;

    start_t = clock();

    for (int n = 0; n < NTIMES1; n++)
    {
        task1_fast(&a[0], &b[0], &c[0], &d[0], &res[0], LEN);
    }
    end_t = clock();
    clock_delta = end_t - start_t;
    clock_delta_sec = (float) (clock_delta / sec_const);
    printf("test_task1_SSE\t %.2f s\t\n", clock_delta_sec);
}
