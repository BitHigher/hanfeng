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
#include "io/File.h"
#include "structure/Subset.h"
#include "machine/Machine.h"
#include "math/Math.h"
#include "base/Parameter.h"
#include "classifier/LDA.h"


using namespace hanfeng;

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
    
    /*
    HFVector<float64_t> w(5);
    w.random(0,6);
    w.display_vector();
     */
    
    float64_t *mv1 = new float64_t[3];
    float64_t *mv2 = new float64_t[3];
    
    for(int i = 0; i < 3; ++i)
    {
        mv1[i] = i+1;
        mv2[i] = (i+3)*(i+2);
    }
    
    std::cout << "DOT: " << HFVector<float64_t>::dot(mv1, mv2, 3);
}

void test_matrix()
{
    std::cout << "[test matrix]\n";
    
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

void test_file()
{
    std::cout << "[test file]\n";
    
    size_t len = 0;
    char *fname = "/Users/zhf/Desktop/test.txt";
    char *buf = CFile::read_whole_file(fname, len);
    
    std::cout << "[length]:" << len << '\n'
                << "[Content]:\n" << buf << '\n';
}

void test_object()
{
    std::cout << "[test object]\n";
 
    /*
    EMessageType level = hf_io->get_loglevel();
    hf_io->set_loglevel(MSG_GCDEBUG);
    
    CSubset *s = new CSubset;
   
   
    s->ref_count();
    s->ref();
    
    CMachine *ss = new CMachine();
    
    s->unref();
    ss->ref();
    ss->unref();
    
    hf_io->set_loglevel(level);
    */
    
   // CMachine *mm = new CMachine();
   // mm->print_serializable();
    
    CLDA *lda = new CLDA();
    lda->print_serializable();
    
//    CSubset *sss = new CSubset;
//    sss->print_serializable();
    
}

void test_math()
{
    std::cout << "[test math]\n";
    
    int32_t arr[10];
    for(int i = 0; i < 10; ++i)
        arr[i] = CMath::random(0, 10);
    
    for(int i = 0; i < 10; ++i)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
    
    
    CMath::qsort<int32_t>(arr, 10);
    for(int i = 0; i < 10; ++i)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
}

int main(int argc, char** argv) 
{
    std::cout << "\n-------- test start --------\n";
  
    init_hanfeng_with_defaults();
    //EMessageType level = hf_io->get_loglevel();
    hf_io->set_loglevel(MSG_GCDEBUG);
    // test_vector();
    
    // test_matrix();
    
    // test_parallel();
    
    // test_file();
    
    test_object();
    
    // test_math();
    
    std::cout << "\n--------test finished--------\n";
    
    exit_hanfeng();
    return 0;
}