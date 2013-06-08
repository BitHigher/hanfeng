/* 
 * File:   DenseLabels.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 上午11:52
 */

#include "DenseLabels.h"
#include "../io/HFIO.h"


using namespace hanfeng;

CDenseLabels::CDenseLabels(): CLabels()
{
    init();
}

CDenseLabels::CDenseLabels(int32_t num_labels) : CLabels()
{
    init();
    labels_ = HFVector<float64_t>(num_labels);
}

CDenseLabels::CDenseLabels(CFile *loader): CLabels()
{
    init();
    load(loader);
}

CDenseLabels::~CDenseLabels()
{
}

void CDenseLabels::init()
{
    HF_ADD(&labels_, "labels", "The labels", MS_NOT_AVAILABLE);
}

void CDenseLabels::set_to_const(float64_t c)
{
    ASSERT(labels_.vector);
    index_t subset_size = get_num_labels();
    
    for(index_t i = 0; i < subset_size; ++i)
        labels_.vector[subset_stack_->subset_idx_conversion(i)] = c;
}

void CDenseLabels::set_to_one()
{
    set_to_const(1.0);
}

void CDenseLabels::zero()
{
    set_to_const(0.0);
}

void CDenseLabels::set_labels(HFVector<float64_t> v)
{
    if(subset_stack_->has_subsets())
        HF_ERROR("A subset is set, cannot set labels");
    
    labels_ = v;
}

HFVector<float64_t> CDenseLabels::get_labels()
{
    if(subset_stack_->has_subsets())
        HF_ERROR("get_labels() is not possible on subset");

    return labels_;
}

HFVector<float64_t> CDenseLabels::get_labels_copy()
{
    // TODO
}

void CDenseLabels::ensure_valid(const char* context)
{
    if(labels_.vector == NULL)
        HF_ERROR("%s%sempty content (NULL) for labels", 
                context?context:"", context?": ":"");
}

int32_t CDenseLabels::get_num_labels()
{
    return subset_stack_->has_subsets() ?
        subset_stack_->get_size() : labels_.vlen;
}

void CDenseLabels::load(CFile *loader)
{
    remove_subset();
    labels_ = HFVector<float64_t>();
    labels_.load(loader);
}

void CDenseLabels::save(CFile *saver)
{
    if(subset_stack_->has_subsets())
        HF_ERROR("save() is not possible on subset");
    
    labels_.save(saver);
}

int32_t CDenseLabels::get_int_label(index_t index)
{
    int real_num = subset_stack_->subset_idx_conversion(index);
    ASSERT(labels_.vector && index < get_num_labels());
    
    // TODO more check
    
    return int32_t(labels_.vector[real_num]);
}

HFVector<int32_t> CDenseLabels::get_int_labels()
{
    HFVector<int32_t> intlabs(get_num_labels());
    
    for(index_t i = 0; i < get_num_labels(); ++i)
        intlabs.vector[i] = get_int_label(i);
    
    return intlabs;
}

float64_t CDenseLabels::get_label(index_t index)
{
    int32_t real_num = subset_stack_->subset_idx_conversion(index);
    ASSERT(labels_.vector && index < get_num_labels());
    return labels_.vector[real_num];
}