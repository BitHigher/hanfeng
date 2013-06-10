/* 
 * File:   RegressionLabels.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 上午11:07
 */

#include "RegressionLabels.h"

using namespace hanfeng;

CRegressionLabels::CRegressionLabels()
{
}

CRegressionLabels::CRegressionLabels(int32_t num_labels)
:CDenseLabels(num_labels)
{  
}

CRegressionLabels::CRegressionLabels(HFVector<float64_t> src)
{
    set_labels(src);
}

CRegressionLabels::CRegressionLabels(CFile* loader)
: CDenseLabels(loader)
{
}

CRegressionLabels::~CRegressionLabels()
{
}

CRegressionLabels* CRegressionLabels::obtain_from_generic(CLabels* base_labels)
{
    if(base_labels->get_label_type() == LT_REGRESSION)
        return (CRegressionLabels*)base_labels;
    else
        HF_SERROR("base_labels must be of dynamic type CRegressionLabels");
    
    return NULL;
}