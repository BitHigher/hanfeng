#include "../structure/HFVector.h"

using namespace hanfeng;


void test_vector()
{
    printf("[test vector]\n");
    
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
    
    printf("DOT: %f\n", HFVector<float64_t>::dot(mv1, mv2, 3));
}