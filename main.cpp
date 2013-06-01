/* 
 * File:   main.cpp
 * Author: Zhu Hanfeng
 *
 * Created on 2013年5月16日, 上午11:49
 */

#include <iostream>
#include <float.h>
#include "io/HFIO.h"
#include "structure/HFVector.h"
#include "structure/HFMatrix.h"

using namespace hanfeng;

void print_error(FILE *target, const char *str)
{
    //std::cout << str << '\n';
    fputs(str, target);
}


void test_vector()
{
    std::cout << "Testing HFVector...\n";
    
    float64_t *a = new float64_t[50];
    for(int i = 0; i < 13; ++i)
        a[i] = i;
    
    HFVector<float64_t> v(a, 13);
    v.display_vector();
    
    v.random(0, 1);
    
    v.display_vector();
    
    HFVector<float64_t> v1 = v;
    
    v1.display_vector();
    
    v1.vector[0] = 13;
    
    v1.qsort();
    
    
    HFVector<float64_t> v2 = v1.clone();
    
    float64_t *b = new float64_t[11];
    HFVector<float64_t> v3(b, 2);
    
    v2 += v3;
    
    
    v2.display_vector();
}

void test_matrix()
{
    int32_t *a = new int32_t[50];
    for(int i = 0; i < 15; ++i)
    {
        a[i] = i+1;
    }
    
    HFMatrix<int32_t> m(3, 5);
    m.display_matrix();
    
    HFMatrix<int32_t>::transpose_matrix(m.matrix, m.num_rows, m.num_cols);
    m.display_matrix();
}

int main(int argc, char** argv) 
{
    std::cout << "hanfeng, a toy for Machine Learning\n";
  
    init_hanfeng(print_error, print_error, print_error);    
    
    // test_vector();
    
    test_matrix();
    return 0;
}