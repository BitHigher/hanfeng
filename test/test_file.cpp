#include "../io/AsciiFile.h"
#include "../structure/HFMatrix.h"
#include "../structure/HFVector.h"

using namespace hanfeng;

void test_file()
{
    printf("[test file]\n");
    
    char *mfname = "/Users/zhf/Desktop/sgdata/train_data_x.asc";
    char *vfname = "/Users/zhf/Desktop/sgdata/train_data_y.asc";
    CAsciiFile *af = new CAsciiFile(vfname);

    HFMatrix<float64_t> matrix;
    //matrix.load(af);
    
    matrix.display_matrix();
    
    HFVector<float64_t> vector;
    vector.load(af);
    vector.display_vector();
    
}