#include "tasks.hpp"

int main()
{

//    https://software.intel.com/en-us/mkl-tutorial-c-multiplying-matrices-using-dgemm

    printf("Function \t Time \n");

//    test_task1_slow();
//    test_task1_SSE();
//
//    test_task2_blas();
//    test_task2_SSE();

    test_task3_slow();

    std::cout<<"end"<<std::endl;
    return 0;
}
