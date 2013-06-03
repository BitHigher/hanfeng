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

#include "base/Parallel.h"

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
    
    /*
    float64_t *b = new float64_t[11];
    HFVector<float64_t> v3(b, 2);
    
    v2 += v3;
    
    
    v2.display_vector();
     */
    
    HFVector<float64_t> w(5);
    w.display_vector();
}

void test_matrix()
{
    int32_t *a = new int32_t[50];
    for(int i = 0; i < 15; ++i)
    {
        a[i] = i+1;
    }
    
    //HFMatrix<float64_t> A = HFMatrix<float64_t>::create_centering_matrix(5);
  //  A.display_matrix();
    
    HFMatrix<float64_t> A(4, 5);
    HFMatrix<float64_t> B(5, 3);
    
    A.set_const(2.5);
    A(0,1) = 5.2;
    
    B.set_const(3.5);
    
    B.display_matrix();
    
    HFMatrix<float64_t>::matrix_multiply(A, B).display_matrix();
    
    
    HFMatrix<float64_t> C(2, 2);
    C(0, 0) = 2;
    C(0, 1) = 3;
    C(1, 0) = 4;
    C(1, 1) = 5;
    
    
    HFMatrix<float64_t>::inverse(C);
    C.display_matrix();
}

void test_parallel()
{
    std::cout << "[test parallel]\n";
    
    Parallel p;
    std::cout << "CPUs: " << p.get_num_cpus() << '\n';
}

int main(int argc, char** argv) 
{
    std::cout << "\n-------- test start --------\n";
  
    init_hanfeng(print_error, print_error, print_error);    
    
    // test_vector();
    
    // test_matrix();
    
    test_parallel();
    
    std::cout << "\n--------test finished--------\n";
    return 0;
}