#include "../structure/HFMatrix.h"

using namespace hanfeng;

void test_matrix()
{
    printf("[test matrix]\n");
    
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