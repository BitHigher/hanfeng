#include "../io/AsciiFile.h"
#include "../structure/HFMatrix.h"
#include "../structure/HFVector.h"

using namespace hanfeng;

void test_file()
{
    printf("[test file]\n");
    
    char *mfname = "/Users/zhf/Desktop/sgdata/train_data_x.asc";
    char *vfname = "/Users/zhf/Desktop/sgdata/train_data_y.asc";
    char *wfname = "/Users/zhf/Desktop/sgdata/train_data_y.txt";
    
    CAsciiFile *af = new CAsciiFile(vfname);

    HFMatrix<float64_t> matrix;
    //matrix.load(af);
    
    matrix.display_matrix();
    
    HFVector<float64_t> vector;
    vector.load(af);
    vector.display_vector();
    vector[0] = 2.55;
    printf("vlen: %d\n", vector.vlen);
    
    
    CAsciiFile *sf = new CAsciiFile(wfname, 'w');
    vector.save(sf); 
}