#include "../regression/LinearRidgeRegression.h"
#include "../io/AsciiFile.h"

using namespace hanfeng;

void test_regression()
{
    printf("[test regression]\n");
    
 //   hf_io->set_loglevel(MSG_GCDEBUG);
    
    CAsciiFile *file = new CAsciiFile("/Users/zhf/Desktop/sgdata/toy/fm_train_real.dat");
    HFMatrix<float64_t> matrix(2, 2);
    //matrix.load(file);
    matrix(0, 0) = 1;
    matrix(1, 0) = 2;
    matrix(0, 1) = 3;
    matrix(1, 1) = 4;
    
    matrix.display_matrix("Feature Matrix");
    
    CAsciiFile *lfile = new CAsciiFile("/Users/zhf/Desktop/sgdata/toy/label_train_regression.dat");
    HFVector<float64_t> vector(2);
    //vector.load(lfile);
    vector[0] = 4;
    vector[1] = 10;
    
    vector.display_vector("Labels");
    
    CDenseFeatures<float64_t> *f = new CDenseFeatures<float64_t>(matrix);
    CRegressionLabels *l = new CRegressionLabels(vector);
    
    
    
    CLinearRidgeRegression *reg = new CLinearRidgeRegression();
    reg->set_features(f);
    reg->set_labels(l);
    
    reg->train();
    
    reg->get_w().display_vector("w");
    printf("bias: %.18lg\n", reg->get_bias());
    
}