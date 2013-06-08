#include <iostream>

#include "../labels/BinaryLabels.h"
#include "../labels/MultiClassLabels.h"

using namespace std;
using namespace hanfeng;

void test_binary_labels()
{
    cout << "[test binary labels]\n";
    CBinaryLabels *bl = new CBinaryLabels(12);
    bl->print_serializable();
}

void test_multiclass_labels()
{
    cout << "[test multiclass labels]\n";
   
    const int n_labels = 3;
    const int n_classes = 4;
    
    CMultiClassLabels *ml = new CMultiClassLabels(n_labels);
    ml->allocate_confidences_for(n_classes);
    
    for(int i = 0; i < n_labels; ++i)
        ASSERT(ml->get_multiclass_confidences(i).size() == n_classes);
    
    for(int i = 0; i < n_labels; ++i)
    {
        HFVector<float64_t> confs(n_classes);
        
        confs.zero();
        confs[i%n_classes] = 1.0;
        
        ml->set_multiclass_confidences(i, confs);
        
        HFVector<float64_t> obtained_confs = ml->get_multiclass_confidences(i);
        for(int j = 0; j < n_classes; ++j)
        {
            if(j == i%n_classes)
                ASSERT(obtained_confs[j] == 1.0)
            else
                ASSERT(obtained_confs[j] == 0.0)
        }
    }
    HF_UNREF(ml);
}

void test_labels()
{
    cout << "[test labels]\n";
    
    // test_binary_labels();
    test_multiclass_labels();
    
}
