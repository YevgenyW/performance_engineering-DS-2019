//
// Created by Yevhen Pozdniakov on 5/6/19.
//
#include "alias.hpp"
#include "test.hpp"
#include "utils.hpp"

int main(int argc, char *argv[]) {

    printf("Function \t Time \n");

    test<Test1_CPU>();
    printf("-----------------\n");

    test<Test2_CPU>();
    printf("-----------------\n");

    test<Test3_CPU>();
    return 0;
}

