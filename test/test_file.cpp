#include "../io/AsciiFile.h"
#include "../structure/HFMatrix.h"
#include "../structure/HFVector.h"

#include "../features/DenseFeatures.h"
#include "../classifier/Perceptron.h"
#include "../classifier/LDA.h"

using namespace hanfeng;

void test_file()
{
    printf("[test file]\n");
    
    char *lfname = "/Users/zhf/Desktop/sgdata/toy/label_train_twoclass.dat";
    CAsciiFile *file = new CAsciiFile(lfname);
    
    HFVector<float64_t> vector;
    vector.load(file);
    printf("vlen: %d\n", vector.vlen);
    vector.display_vector();
    
    char *ffname = "/Users/zhf/Desktop/sgdata/toy/fm_train_real.dat";
    CAsciiFile *mfile = new CAsciiFile(ffname);
    
    HFMatrix<float64_t> matrix;
    matrix.load(mfile);
    printf("num_feat: %d, num_vec: %d\n", matrix.num_rows, matrix.num_cols);
    matrix.display_matrix();    
    
    CBinaryLabels *bl = new CBinaryLabels();
    bl->set_labels(vector);
    
    CDenseFeatures<float64_t> *df = new CDenseFeatures<float64_t>(matrix);
    
    
    CPerceptron *classifier = new CPerceptron(df, bl);
    //CLDA *classifier = new CLDA(0.01, df, bl);
    classifier->train();
}