#define LEN 33000
#define LEN2 1024
#define NTIMES1 100000
#define NTIMES2 300

#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include <time.h>
#include <xmmintrin.h>

#include <cblas.h>

#include <iostream>
#include <chrono>

const float sec_const = 1000000.0;

float a[LEN] __attribute__((aligned(16)));
float b[LEN] __attribute__((aligned(16)));
float c[LEN] __attribute__((aligned(16)));
float d[LEN2] __attribute__((aligned(16)));
float res[LEN2] __attribute__((aligned(16)));

float ma[LEN2][LEN2] __attribute__((aligned(16)));
float sum[LEN2] __attribute__((aligned(16)));

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
        auto chunk = _mm_add_ps(_mm_mul_ps(_mm_load_ps(A), _mm_load_ps(B)),
                                _mm_mul_ps(_mm_load_ps(C), _mm_load_ps(D)));
        _mm_store_ps(&res[i], chunk);
    }
}

template <typename T>
void task1_slow(const T* A, const T* B, const T* C, const T* D, T* res, std::size_t N)
{
    for (std::size_t i = 0; i < N; ++i)
    {
        res[i] = a[i] * b[i] + c[i] * d[i];
    }
}

double * init_matrix(std::size_t size, double def_value)
{
    double* A = (double *)_mm_malloc( size*size*sizeof( double ), 64 );
    for (std::size_t i = 0; i < (size*size); ++i)
    {
        A[i] = def_value;
    }
    return A;
}

void clear_matrix(double* ptr)
{
    _mm_free(ptr);
}

void print_matrix(const double* M, std::size_t size)
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

//    printf (" Computing matrix product using Intel(R) MKL dgemm function via CBLAS interface \n\n");
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, alpha, A, k, B, n, beta, res, n);
//    printf ("\n Computations completed.\n\n");
}



int test_task1_slow()
{
    clock_t start_t;
    clock_t end_t;
    clock_t clock_delta;
    double clock_delta_sec;

    start_t = clock();

    for (int n = 0; n < NTIMES1; n++)
    {
        task1_slow(&a[0], &b[0], &c[0], &d[0], &res[0], LEN);
    }
    end_t = clock();
    clock_delta = end_t - start_t;
    clock_delta_sec = (double) (clock_delta / sec_const);
    printf("test_task1_slow\t %.2f s\t\n", clock_delta_sec);

    return 0;
}

int test_task1_fast()
{
    clock_t start_t;
    clock_t end_t;
    clock_t clock_delta;
    double clock_delta_sec;

    start_t = clock();

    for (int n = 0; n < NTIMES1; n++)
    {
        task1_fast(&a[0], &b[0], &c[0], &d[0], &res[0], LEN);
    }
    end_t = clock();
    clock_delta = end_t - start_t;
    clock_delta_sec = (double) (clock_delta / sec_const);
    printf("test_task1_fast\t %.2f s\t\n", clock_delta_sec);

    return 0;
}

void test_task2_blas()
{
    std::size_t size = 1000;
    auto A = init_matrix(size, 1);
    auto B = init_matrix(size, 5);
    auto res = init_matrix(size, 0);

//    clock_t start_t;
//    clock_t end_t;
//    clock_t clock_delta;
//    double clock_delta_sec;
//
//    start_t = clock();
    auto start = std::chrono::high_resolution_clock::now();
    for (std::size_t i = 0; i < NTIMES2; ++i)
    {
        matrix_multiplication_blas(A, B, res, size);
    }
//    end_t = clock();
//    clock_delta = end_t - start_t;
//    clock_delta_sec = (double) (clock_delta / sec_const);
    auto end = std::chrono::high_resolution_clock::now();
    auto total_processing_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("test_task2_blas\t %lld ms\t\n", total_processing_time.count());
//    std::cout << "Total processing time " << total_processing_time.count() << " ms" << std::endl;


    clear_matrix(A);
    clear_matrix(B);
    clear_matrix(res);
}

//void matrix_multiplcation_blas(double *A, int A_width, int A_height,
//                               double *B, int B_width, int B_height,
//                               double *AB, bool tA, bool tB, double beta)
//{
//    A_height = tA ? A_width  : A_height;
//    A_width  = tA ? A_height : A_width;
//
//    B_height = tB ? B_width  : B_height;
//    B_width  = tB ? B_height : B_width;
//
//    int m = A_height;
//    int n = B_width;
//    int k = A_width;
//
//    // Error, width and height should match!
//    assert(A_width == B_height);
//
//    int lda = tA ? m : k;
//    int ldb = tB ? k : n;
//
//#define TRANSPOSE(X) ((X) ? CblasTrans : CblasNoTrans)
//
//    //http://www.netlib.org/lapack/explore-html/d1/d54/group__double__blas__level3_gaeda3cbd99c8fb834a60a6412878226e1.html#gaeda3cbd99c8fb834a60a6412878226e1
//    cblas_dgemm(CblasRowMajor,
//                TRANSPOSE(tA), TRANSPOSE(tB),
//                m, n, k, 0.1,
//                A, lda,
//                B, ldb,
//                beta,
//                AB, n);
//
//#undef TRANSPOSE(X)
//}



int main()
{

//    https://software.intel.com/en-us/mkl-tutorial-c-multiplying-matrices-using-dgemm

    printf("Function \t Time \n");

    test_task1_slow();
    test_task1_fast();

    test_task2_blas();

    std::size_t size = 3;
    auto A = init_matrix(size, 1);
    auto B = init_matrix(size, 5);
    auto res = init_matrix(size, 0);

    matrix_multiplication_blas(A, B, res, size);

//    print_matrix(res, size);

    clear_matrix(A);
    clear_matrix(B);
    clear_matrix(res);

//    matrix_multiplcation_blas(&arr1[0], size, size,
//                              arr2, size, size,
//                              res, false, false, 1.0);

//    using namespace std;
//    auto size = 4;
//    float a[size] __attribute__((aligned(32)));
//    float c[size] __attribute__((aligned(32)));
//    cout<<"sizeof(float)"<<sizeof(float)<<endl;
//    for (int i = 0; i < size; ++i)
//    {
//    a[i] = i;
//    }
//
//    task1_fast(&a[0], &a[0], &a[0], &a[0], &c[0], size);
//    //
//    ////  for (int i = 0; i < size; i+= sizeof(float))
//    ////  {
//    ////    auto rA = _mm_load_ps(&a[i]);
//    ////    _mm_store_ps(&c[i],rA);
//    ////    cout<<"step: "<<i<<endl;
//    ////  }
//    //
//    for (int i = 0; i < size; ++i)
//    {
//    cout<<c[i]<<endl;
//    }
//    cout<<"end"<<endl;
    return 0;
}


int e00()
{
    clock_t start_t;
    clock_t end_t;
    clock_t clock_delta;
    double clock_delta_sec;

    start_t = clock();

    for (int n = 0; n < NTIMES1; n++) {
        for (int i = 0; i < LEN; i++) {
            c[i] = a[i] * b[i];
        }
//    nothing_00(a,b,c);
    }
    end_t = clock();
    clock_delta = end_t - start_t;
    clock_delta_sec = (double) (clock_delta / sec_const);
    printf("E00\t %.2f \t\n", clock_delta_sec);

    return 0;
}


int e01()
{

    clock_t start_t;
    clock_t end_t;
    clock_t clock_delta;
    double clock_delta_sec;

    start_t = clock();

    __m128 rA,rB,rC;
    for (int n = 0; n < NTIMES1; n++) {
        for (int i = 0; i < LEN; i+=4) {
            rA = _mm_load_ps(&a[i]);
            rB = _mm_load_ps(&b[i]);
            rC = _mm_mul_ps(rA,rB);
            _mm_store_ps(&c[i],rC);
        }
//        nothing_00(a, b, c);
    }
    end_t = clock();
    clock_delta = end_t - start_t;
    clock_delta_sec = (double) (clock_delta / sec_const);
    printf("E01\t %.2f \t\n", clock_delta_sec);
    return 0;
}

int e10()
{

    clock_t start_t;
    clock_t end_t;
    clock_t clock_delta;
    double clock_delta_sec;
    start_t = clock();

    for (int n = 0; n < NTIMES1/500; n++) {
        for (int i = 0; i < LEN2; i++){
            float sum = 0;
            for (int j = 0; j < LEN2; j++){
                sum += ma[j][i];
            }
            d[i] = sum;
        }
//        nothing_10(a, ma, d);
    }

    end_t = clock();
    clock_delta = end_t - start_t;
    clock_delta_sec = (double) (clock_delta / sec_const);
    printf("E10\t %.2f \t\n", clock_delta_sec);
    return 0;
}


int e11()
{

    clock_t start_t;
    clock_t end_t;
    clock_t clock_delta;
    double clock_delta_sec;
    start_t = clock();

    for (int nl = 0; nl < NTIMES1/500; nl++) {
        for (int i = 0; i < LEN2; i++){
            sum[i] = 0;
            for (int j = 0; j < LEN2; j++){
                sum[i] += ma[j][i];
            }
            d[i] = sum[i];
        }
//        nothing_10(a, ma, d);
    }

    end_t = clock();
    clock_delta = end_t - start_t;
    clock_delta_sec = (double) (clock_delta / sec_const);
    printf("E11\t %.2f \t\n", clock_delta_sec);
    return 0;
}