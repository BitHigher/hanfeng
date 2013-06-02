/* 
 * File:   Labels.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 上午11:03
 */

#include "Labels.h"

using namespace hanfeng;

CLabels::CLabels() : CHFObject()
{
    init();
}

CLabels::~CLabels()
{
    HF_UNREF(subset_stack_);
}

void CLabels::init()
{
    // TODO HF_ADD
    
    subset_stack_ = new CSubsetStack();
    HF_REF(subset_stack_);
}

void CLabels::add_subset(HFVector<index_t> subset)
{
    subset_stack_->add_subset(subset);
}

void CLabels::remove_subset()
{
    subset_stack_->remove_subset();
}

void CLabels::remove_all_subsets()
{
    subset_stack_->remove_all_subsets();
}

float64_t CLabels::get_value(index_t index)
{
    ASSERT(current_values_.vector && index < get_num_labels());
    
    index_t real_num = subset_stack_->subset_idx_conversion(index);
    return current_values_.vector[real_num];
}

HFVector<float64_t> CLabels::get_values()
{
    return current_values_;
}

void CLabels::set_value(float64_t value, index_t index)
{
    // TODO
    
    index_t real_num = subset_stack_->subset_idx_conversion(index);
    current_values_.vector[real_num] = value;
}

void CLabels::set_values(HFVector<float64_t> values)
{
    if(current_values_.vlen != 0 && current_values_.vlen != get_num_labels())
    {
        HF_ERROR("length of values should match number of labels or "
                "have zero length (len(labels)=%d, len(values)=%d)",
                get_num_labels(), current_values_.vlen);
    }
    
    current_values_ = values;
}