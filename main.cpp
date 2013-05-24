/* 
 * File:   main.cpp
 * Author: Zhu Hanfeng
 *
 * Created on 2013年5月16日, 上午11:49
 */

#include <iostream>
#include <float.h>
#include "structure/HFVector.h"

void test_vector()
{
    std::cout << "Testing HFVector...\n";
    
    float64_t *a = new float64_t[50];
    for(int i = 0; i < 3; ++i)
        a[i] = i;
    
    hanfeng::HFVector<float64_t> v(a, 3);
    v.display_vector();
    
    v.random(0, 1);
    
    v.display_vector();
    
    hanfeng::HFVector<float64_t> v1 = v;
    
    v1.display_vector();
    
    v1.vector[0] = 13;
    v.display_vector();
}

int main(int argc, char** argv) 
{
    std::cout << "hanfeng, a toy for Machine Learning\n";
    
    test_vector();
    return 0;
}