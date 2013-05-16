/* 
 * File:   main.cpp
 * Author: Zhu Hanfeng
 *
 * Created on 2013年5月16日, 上午11:49
 */

#include <iostream>
#include "structure/HFVector.h"

void test_vector()
{
    std::cout << "Testing HFVector...\n";
    
    int *a = new int[3];
    for(int i = 0; i < 3; ++i)
        a[i] = i;
    
    bool *b = new bool[3];
    for(int i = 0; i < 3; ++i)
        b[i] = i%2;
    
    hanfeng::HFVector<bool> v(b, 3);
    std::cout << v.size();
}

int main(int argc, char** argv) 
{
    std::cout << "hanfeng, a toy for Machine Learning\n";
    
    test_vector();
    return 0;
}

