/* 
 * File:   MultiClassLabels.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 上午11:06
 */

#include "MultiClassLabels.h"

using namespace hanfeng;

CMultiClassLabels::CMultiClassLabels()
{
    init();
}

CMultiClassLabels::CMultiClassLabels(int32_t num_labels)
: CDenseLabels(num_labels)
{
    init();
}

CMultiClassLabels::CMultiClassLabels(HFVector<float64_t> src)
{
    init();
    set_labels(src);
}

CMultiClassLabels::CMultiClassLabels(CFile *loader)
:CDenseLabels(loader)
{
    init();
}

CMultiClassLabels::~CMultiClassLabels()
{
}

void CMultiClassLabels::init()
{
    multiclass_confidences_ = HFMatrix<float64_t>(); 
}

void CMultiClassLabels::ensure_valid(const char *context)
{
    CDenseLabels::ensure_valid(context);
    
    int32_t subset_size = get_num_labels();
    for(index_t i = 0; i < subset_size; ++i)
    {
        // TODO 
    }
    
    // TOD ensure_valid
}

void CMultiClassLabels::allocate_confidences_for(int32_t n_classes)
{
    int32_t n_labels = labels_.size(); // FIXME why not get_num_labels();
    
    REQUIRE(n_labels, "%s::allocate_confidences_for(): "
            "There should be labels to store confidences", get_name());
    
    multiclass_confidences_ = HFMatrix<float64_t>(n_classes, n_labels);
}

HFVector<float64_t> CMultiClassLabels::get_multiclass_confidences(int32_t i)
{
    HFVector<float64_t> confs(multiclass_confidences_.num_rows);
    
    for(index_t j = 0; j < confs.size(); ++j)
        confs.vector[j] = multiclass_confidences_(j, i);
    
    return confs;
}

void CMultiClassLabels::set_multiclass_confidences(int32_t i, 
                                HFVector<float64_t> confidences)
{
    ASSERT(confidences.size() == multiclass_confidences_.num_rows);
    
    for(index_t j = 0; j < confidences.size(); ++j)
        multiclass_confidences_(j, i) = confidences[j];
}