#include <iostream>
#include "../features/DenseFeatures.h"

using namespace std;
using namespace hanfeng;

void test_features()
{
    cout << "[test features]\n";
    
    int n1 = 3;
    int n2 = 4;
    int dim = 2;
    
    HFMatrix<float64_t> data1(dim, n1);
    for(int i = 0; i < dim*n1; ++i)
        data1.matrix[i] = i;
    
    HFMatrix<float64_t> data2(dim, n2);
    for(int i = 0; i < dim*n2; ++i)
        data2.matrix[i] = i;
    
    CDenseFeatures<float64_t> *f1 = new CDenseFeatures<float64_t>(data1);
    CDenseFeatures<float64_t> *f2 = new CDenseFeatures<float64_t>(data2);
    
    
    
    HF_UNREF(f1);
    HF_UNREF(f2);
}