#include "tasks.hpp"

int main()
{
    printf("Function \t Time \n");

    test_task1_slow();
    test_task1_SSE();
    printf("-----------------\n");
    test_task2_blas();
    test_task2_SSE();
    printf("-----------------\n");
    test_task3_strstr();
    test_task3_slow();
    test_task3_SSE();

    return 0;
}
