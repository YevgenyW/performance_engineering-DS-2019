#include "tasks.hpp"

int main()
{

//    https://software.intel.com/en-us/mkl-tutorial-c-multiplying-matrices-using-dgemm

    printf("Function \t Time \n");

    test_task1_slow();
    test_task1_fast();

    test_task2_blas();
    test_task2();

//    std::size_t size = 5;
//    auto A = matrix_init(size, 10);
//    auto B = matrix_init(size, 2);
//    auto res = matrix_init(size, 0);
//
////    auto trans_A = matrix_transpose(A, size);
////    matrix_print(trans_A, size);
////    matrix_clear(trans_A);
//
//    matrix_multiplication_blas(A, B, res, size);
//
//    matrix_print(A, size);
//    matrix_print(B, size);
//    matrix_print(res, size);
//
//    matrix_clear(A);
//    matrix_clear(B);
//    matrix_clear(res);

//    matrix_multiplcation_blas(&arr1[0], size, size,
//                              arr2, size, size,
//                              res, false, false, 1.0);

//    using namespace std;
//    auto size = 3;
//    float a[size] __attribute__((aligned(32)));
//    float c[size] __attribute__((aligned(32)));
//    float res[size] __attribute__((aligned(32)));
//    cout<<"sizeof(float)"<<sizeof(float)<<endl;
//    for (int i = 0; i < size; ++i)
//    {
//        a[i] = i;
//        c[i] = i+1;
//    }
//
//    for (int i = 0; i < size; ++i)
//    {
//        cout<<a[i]<<" ";
//        cout<<c[i]<<endl;
//    }

//    cout<<"sum = "<<vector_dot_product(a, c, size)<<endl;
    std::cout<<"end"<<std::endl;
    return 0;
}
