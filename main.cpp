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

void test_parallel()
{
    std::cout << "[test parallel]\n";
    
    Parallel p;
    std::cout << "CPUs: " << p.get_num_cpus() << '\n';
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

extern void test_vector();
extern void test_matrix();
extern void test_labels();
extern void test_features();
extern void test_file();
extern void test_classifier();
extern void test_clustering();
extern void test_regression();

int main(int argc, char** argv) 
{
    std::cout << "\n-------- test start --------\n";
  
    init_hanfeng_with_defaults();
    //hf_io->enable_file_and_line();
    
    //hf_io->set_loglevel(MSG_GCDEBUG);
    // test_vector();
    
    // test_matrix();
    
    // test_parallel();
    
    // test_file();
    
    // test_object();
    
    // test_math();
    
    // test_labels();
    
    // test_features();
    
    // test_classifier();
    
    // test_clustering();    
    
    test_regression();
    
    std::cout << "\n--------test finished--------\n";
    
    exit_hanfeng();
    return 0;
}