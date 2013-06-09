/* 
 * File:   Distance.cpp
 * Author: zhf
 * 
 * Created on 2013年6月4日, 下午8:41
 */

#include "Distance.h"
#include "../base/Parameter.h"

using namespace hanfeng;

CDistance::CDistance()
{
}

CDistance::CDistance(CFeatures* lhs, CFeatures* rhs)
{
    
}

CDistance::~CDistance()
{
}

bool CDistance::init(CFeatures* lhs, CFeatures* rhs)
{
    ASSERT(lhs && rhs);
    ASSERT(lhs->get_feature_class() == rhs->get_feature_class());
    ASSERT(lhs->get_feature_type() == rhs->get_feature_type());
    
    remove_lhs_and_rhs();
    
    HF_REF(lhs);
    HF_REF(rhs);
    lhs_ = lhs;
    rhs_ = rhs;
    
    num_lhs_ = lhs->get_num_vectors();
    num_rhs_ = rhs->get_num_vectors();
    
    HF_FREE(precomputed_matrix_);
    precomputed_matrix_ = NULL;
    
    return true;
}

void CDistance::init()
{
    precomputed_matrix_ = NULL;
    precompute_matrix_ = false;
    
    lhs_ = NULL;
    rhs_ = NULL;
    num_lhs_ = 0;
    num_rhs_ = 0;
    
    HF_ADD((CHFObject**)&lhs_, "lhs", 
            "Feature vectors to occur on left hand side", MS_NOT_AVAILABLE);
    
    HF_ADD((CHFObject**)&rhs_, "rhs", 
            "Feature vectors to occur on right hand side", MS_NOT_AVAILABLE);
}

void CDistance::remove_lhs()
{
    HF_UNREF(lhs_);
    lhs_ = NULL;
    num_lhs_ = 0;
}

void CDistance::remove_rhs()
{
    HF_UNREF(rhs_);
    rhs_ = NULL;
    num_rhs_ = 0;
}

void CDistance::remove_lhs_and_rhs()
{
    HF_UNREF(lhs_);
    lhs_ = NULL;
    num_lhs_ = 0;
    
    HF_UNREF(rhs_);
    rhs_ = NULL;
    num_rhs_ = 0;
}

CFeatures* CDistance::replace_rhs(CFeatures* rhs)
{
    ASSERT(rhs);
    
    ASSERT(lhs_->get_feature_class() == rhs->get_feature_class());
    ASSERT(lhs_->get_feature_type() == rhs->get_feature_type());
    
    CFeatures *tmp = rhs_;
    rhs_ = rhs;
    num_rhs_ = rhs->get_num_vectors();
    
    HF_FREE(precomputed_matrix_);
    
    return tmp;
}

void CDistance::do_precompute_matrix()
{
    int32_t num_left = lhs_->get_num_vectors();
    int32_t num_right = rhs_->get_num_vectors();
    
    ASSERT(num_left == num_right);
    ASSERT(lhs_ == rhs_);
    int32_t num = num_left;
    
    HF_FREE(precomputed_matrix_);
    precomputed_matrix_ = HF_MALLOC(float32_t, num*(num+1)/2);
    
    for(index_t i = 0; i < num; ++i)
    {
        HF_PROGRESS(i*i, 0, num*num);
        for(index_t j = 0; j <= i; ++j)
            precomputed_matrix_[i*(i+1)/2+j] = compute(i, j);
    }
    
    HF_PROGRESS(num*num, 0, num*num);
    HF_DONE();
}