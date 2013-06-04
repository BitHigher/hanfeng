/* 
 * File:   Distance.cpp
 * Author: zhf
 * 
 * Created on 2013年6月4日, 下午8:41
 */

#include "Distance.h"

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
    
    // TODO add parameters
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