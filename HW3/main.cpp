//
// Created by Yevhen Pozdniakov on 5/6/19.
//
#include "alias.hpp"
#include "tasks.hpp"
#include "utils.hpp"

#include <stdio.h>


int main(int argc, char *argv[]) {

    printf("Function \t Time \n");
    test<Test1_CPU>();
    test<Test1_Threads>();
//    test_task1();
//    test_task1_threads();
    printf("-----------------\n");
    test<Test2_CPU>();
    test<Test2_Threads>();
//    test_task2();
//    test_task2_threads();
//    printf("-----------------\n");
//    test_task3();
    return 0;
}

