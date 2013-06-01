/* 
 * File:   maintest.cpp
 * Author: Zhu Hanfeng <zhuhanfeng@gmail.com>
 *
 * Created on 2013-6-1, 15:56:48
 */

#include <stdlib.h>
#include <iostream>

/*
 * Simple C++ Test Suite
 */

void test1() {
    std::cout << "maintest test 1" << std::endl;
}

void test2() {
    std::cout << "maintest test 2" << std::endl;
    std::cout << "%TEST_FAILED% time=0 testname=test2 (maintest) message=error message sample" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% maintest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% test1 (maintest)" << std::endl;
    test1();
    std::cout << "%TEST_FINISHED% time=0 test1 (maintest)" << std::endl;

    std::cout << "%TEST_STARTED% test2 (maintest)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (maintest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

