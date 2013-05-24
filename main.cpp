/* 
 * File:   main.cpp
 * Author: Zhu Hanfeng
 *
 * Created on 2013年5月16日, 上午11:49
 */

#include <iostream>
#include <float.h>
#include "structure/HFVector.h"
#include "structure/HFMatrix.h"

void test_vector()
{
    std::cout << "Testing HFVector...\n";
    
    float64_t *a = new float64_t[50];
    for(int i = 0; i < 13; ++i)
        a[i] = i;
    
    hanfeng::HFVector<float64_t> v(a, 13);
    v.display_vector();
    
    v.random(0, 1);
    
    v.display_vector();
    
    hanfeng::HFVector<float64_t> v1 = v;
    
    v1.display_vector();
    
    v1.vector[0] = 13;
    
    v1.qsort();
    
    
    hanfeng::HFVector<float64_t> v2 = v1.clone();
    
    v2 += v1;
    v2.display_vector();
}

void test_matrix()
{
    int32_t *a = new int32_t[50];
    for(int i = 0; i < 15; ++i)
    {
        a[i] = i+1;
    }
    
    hanfeng::HFMatrix<int32_t> m(3, 5);
    m.display_matrix();
}

int main(int argc, char** argv) 
{
    std::cout << "hanfeng, a toy for Machine Learning\n";
    
    //test_vector();
    
    test_matrix();
    return 0;
}