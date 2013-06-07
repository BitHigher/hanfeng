/* 
 * File:   Features.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 下午1:32
 */

#include "Features.h"
#include "../io/HFIO.h"
#include <string.h>
#include "../base/Parameter.h"


using namespace hanfeng;

CFeatures::CFeatures(int32_t size)
: CHFObject()
{
    init();
    cache_size_ = size;
}

CFeatures::CFeatures(const CFeatures &orig)
: CHFObject(orig)
{
    init();
    
    preproc_ = orig.preproc_;
    num_preproc_ = orig.num_preproc_;
    
    preprocessed_ = HF_MALLOC(bool, orig.num_preproc_);
    memcpy(preprocessed_, orig.preprocessed_, sizeof(bool)*num_preproc_);
}

CFeatures::CFeatures(CFile *loader)
: CHFObject()
{
    init();
    load(loader);
    
}

CFeatures::~CFeatures()
{
    //TODO clean_preprocessors();
    HF_UNREF(subset_stack_);
}

void CFeatures::init()
{
    HF_ADD(&properties_, "properties", "Feature properties", MS_NOT_AVAILABLE);
    HF_ADD(&cache_size_, "cache_size", "Size of cache", MS_NOT_AVAILABLE);
    
    // TODO
    // ADD VECTOR
    
    properties_ = FP_NONE;
    cache_size_ = 0;
    preproc_ = NULL;
    num_preproc_ = 0;
    preprocessed_ = false;
}

void CFeatures::add_subset(HFVector<index_t> subset)
{
    subset_stack_->add_subset(subset);
    subset_changed_post();
}

void CFeatures::remove_subset()
{
    subset_stack_->remove_subset();
    subset_changed_post();
}

void CFeatures::remove_all_subsets()
{
    subset_stack_->remove_all_subsets();
    subset_changed_post();
}

void CFeatures::load(CFile *loader)
{
    HF_SET_LOCALE_C;
    HF_NOTIMPLEMENTED;
    HF_RESET_LOCALE;
}

void CFeatures::save(CFile *saver)
{
    HF_SET_LOCALE_C;
    HF_NOTIMPLEMENTED;
    HF_RESET_LOCALE;
}