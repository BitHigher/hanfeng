/* 
 * File:   KMeans.cpp
 * Author: zhf
 * 
 * Created on 2013年6月4日, 下午8:53
 */

#include "KMeans.h"
#include "../features/DenseFeatures.h"

using namespace hanfeng;

CKMeans::CKMeans()
:CDistanceMachine()
{
    init();
}

CKMeans::CKMeans(int32_t k, CDistance* d)
: CDistanceMachine()
{
    init();
    k_ = k;
    set_distance(d);
}

CKMeans::~CKMeans()
{
}

void CKMeans::set_k(int32_t k)
{
    ASSERT(k > 0);
    k_ = k;
}

void CKMeans::set_max_iter(int32_t max_iter)
{
    ASSERT(max_iter > 0);
    max_iter_ = max_iter;
}

HFMatrix<float64_t> CKMeans::get_cluster_centers()
{
    if(!R_.vector)
        return HFMatrix<float64_t>();
    
    CDenseFeatures<float64_t> *lhs = 
                (CDenseFeatures<float64_t>*)distance_->get_lhs();
    HFMatrix<float64_t> centers = lhs->get_feature_matrix();
    
    HF_UNREF(lhs);
    return centers;
}

void CKMeans::store_model_features()
{
    CDenseFeatures<float64_t> *centers = new CDenseFeatures<float64_t>(mus_);
    
    CFeatures *rhs = distance_->get_rhs();
    distance_->init(centers, rhs);
    
    HF_UNREF(rhs);
}

void CKMeans::init()
{
    max_iter_ = 10000;
    k_ = 3;
    dimensions_ = 0;
    
    // TODO HF_ADD
}

bool CKMeans::train_machine(CFeatures *data)
{
    ASSERT(distance_);
    
    if(data)
        distance_->init(data, data);
    
    ASSERT(distance_->get_feature_type() == F_DREAL);
    
    CDenseFeatures<float64_t> *lhs = 
                (CDenseFeatures<float64_t> *)distance_->get_lhs();
    ASSERT(lhs);
    int32_t num = lhs->get_num_vectors();
    HF_UNREF(lhs);
    
    weights_ = HFVector<float64_t>(num);
    for(index_t i = 0; i < num; ++i)
        weights_.vector[i] = 1.0;
    
    clustknb(false, NULL);
    
    return true;
}

void CKMeans::clustknb(bool use_old_mus, float64_t* mus_start)
{
    ASSERT(distance_ && distance_->get_feature_type() == F_DREAL);
    CDenseFeatures<float64_t> *lhs = 
                (CDenseFeatures<float64_t>*)distance_->get_lhs();
    
    ASSERT(lhs && lhs->get_num_features()>0 && lhs->get_num_vectors() > 0);
 
    
    // TODO
    HF_NOTIMPLEMENTED
}

bool CKMeans::load(CFile *loader)
{
    HF_SET_LOCALE_C;
    HF_RESET_LOCALE;
    return false;
}

bool CKMeans::save(CFile *saver)
{
    HF_SET_LOCALE_C;
    HF_RESET_LOCALE;
    
    return false;
}