//
// Created by Yevhen Pozdniakov on 4/20/19.
//

#include "tasks.hpp"

#include <cblas.h>

using namespace std;

template <typename T>
T * matrix_init(std::size_t size, float init_value = 0.0)
{
    T* A = (T *)_mm_malloc( size*size*sizeof( T ), 64 );
    for (std::size_t i = 0; i < (size*size); ++i)
    {
        A[i] = init_value + i;
    }
    return A;
}

template <typename T>
void matrix_clear(T *ptr)
{
    _mm_free(ptr);
}

template <typename T>
void matrix_print(const T* M, std::size_t size)
{
    for (std::size_t i = 0; i < (size*size); ++i)
    {
        std::cout<<M[i]<< " ";
        if ((i+1)%size ==0) std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

void matrix_multiplication_blas(const double *A, const double *B, double* res, std::size_t size)
{
//    C=alpha*A*B+beta*C
    const double alpha = 1.0;
    const double beta = .0;
    int m, k, n;
    m = k = n = size;

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, alpha, A, k, B, n, beta, res, n);
}

//template <typename T>
//T* matrix_transpose(const T *A, std::size_t size)
//{
//    auto trans = matrix_init<T>(size);
//    for (std::size_t i = 0; i < size; ++i)
//    {
//        for (std::size_t j = 0; j < size; ++j)
//        {
//            trans[i*size+j] = A[i+j*size];
//        }
//    }
//    return trans;
//}

template <typename T>
T* matrix_transpose(const T *A, std::size_t size)
{
    auto trans = matrix_init<T>(size);

    for (std::size_t i = 0; i < size; ++i)
    {
        for (std::size_t j = 0; j < size; ++j)
        {
            trans[j+i*size] = A[i+j*size];
        }
    }
    return trans;
}

template <typename T>
float vector_dot_product(const T* v1, const T* v2, std::size_t size)
{
    float res = 0;
    float temp[4];

    for (std::size_t i = 0; i < size; i+=4)
    {
        __m128 chunk = _mm_dp_ps(_mm_load_ps(&v1[i]), _mm_load_ps(&v2[i]), 0xff);
        _mm_store_ps(&temp[0], chunk);
        res+=temp[0];
    }

    return res;
}

void matrix_multiplication(const float *A, const float *B, float* res, const std::size_t size)
{
    auto trans_B = matrix_transpose(B, size);

    for (std::size_t i = 0; i < size; ++i)
    {
        for (std::size_t j = 0; j < size; ++j)
        {
            res[i*size+j] = vector_dot_product(&A[i*size], &trans_B[j*size], size);
        }
    }
    matrix_clear(trans_B);
}

void test_task2_blas()
{
    auto A = matrix_init<double>(LEN2, 1);
    auto B = matrix_init<double>(LEN2, 5);
    auto res = matrix_init<double>(LEN2, 0);

    auto start = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < NTIMES2; ++i)
    {
        matrix_multiplication_blas(A, B, res, LEN2);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto total_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("test_task2_blas\t %lld ms\t\n", total_processing_time.count());

    matrix_clear((float*) A);
    matrix_clear((float*)B);
    matrix_clear((float*)res);
}

void test_task2_SSE()
{
    auto A = matrix_init<float>(LEN2, 1);
    auto B = matrix_init<float>(LEN2, 5);
    auto res = matrix_init<float>(LEN2, 0);

    auto start = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < NTIMES2; ++i)
    {
        matrix_multiplication(A, B, res, LEN2);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto total_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("test_task2_SSE\t %lld ms\t\n", total_processing_time.count());

    matrix_clear(A);
    matrix_clear(B);
    matrix_clear(res);
}
