
#include "../classifier/LDA.h"

using namespace hanfeng;

void test_classifier()
{
    printf("[test classifer]\n");
    
    // features
    int num_feat = 5;
    int num_vector = 10; 
    
    HFMatrix<float64_t> matrix(num_feat, num_vector);
    
    for(int i = 0; i < num_feat; ++i)
        matrix.matrix[i] = -i;
    
    for(int i = num_feat; i < num_feat*num_vector; ++i)
        matrix.matrix[i] = i+2;
    
    matrix.display_matrix();
    
    CDenseFeatures<float64_t> *df = new CDenseFeatures<float64_t>(matrix);
    
    // labels
    CBinaryLabels *bl = new CBinaryLabels(num_vector);
    for(int i = 0; i < num_vector; ++i)
        bl->set_label(i, 1);
    bl->set_label(0, -1);
    
    
    CLDA *lda = new CLDA(0.1, df, bl);
    
    lda->train();
    
    HF_UNREF(lda);
}