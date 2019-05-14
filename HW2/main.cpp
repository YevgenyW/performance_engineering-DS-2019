//
// Created by Yevhen Pozdniakov on 5/6/19.
//
#include "tasks.hpp"

#include <stdio.h>

int main(int argc, char *argv[]) {

    printf("Function \t Time \n");

    test_task1();
    printf("-----------------\n");
    test_task2();
    printf("-----------------\n");
    test_task3();
//    test_task3_strstr();
//    test_task3_slow();
//    test_task3_SSE();
    return 0;
}

