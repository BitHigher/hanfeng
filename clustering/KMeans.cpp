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
    
    HF_ADD(&max_iter_, "max_iter", "Maximum Number of iterations.", MS_AVAILABLE);
    HF_ADD(&k_, "k", "number of clusters", MS_AVAILABLE);
    HF_ADD(&dimensions_, "dimensions", "Dimensions of Data", MS_NOT_AVAILABLE);
    HF_ADD(&R_, "R", "cluster radiuses", MS_NOT_AVAILABLE);
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
 
    int32_t XSize = lhs->get_num_vectors();
    dimensions_ = lhs->get_num_features();
    
    int32_t changed = 1;
    const int32_t XDimk = dimensions_ * k_;
    
    int32_t iter = 0;
    
    R_ = HFVector<float64_t>(k_);
    mus_ = HFMatrix<float64_t>(dimensions_, k_);
    
    int32_t *ClList = HF_CALLOC(int32_t, XSize);
    float64_t *weights_set = HF_CALLOC(float64_t, k_);
    float64_t *dists = HF_CALLOC(float64_t, k_*XSize);
    
    // replace rhs features
    CDenseFeatures<float64_t> *rhs_mus = new CDenseFeatures<float64_t>(0);
    CFeatures *rhs_cache = distance_->replace_rhs(rhs_mus);
    
    int32_t vlen = 0;
    bool vfree = false;
    float64_t *vec = NULL;
    
    memset(ClList, 0, sizeof(int32_t)*XSize);
    memset(weights_set, 0, sizeof(float64_t)*k_);
    memset(mus_.matrix, 0, sizeof(float64_t)*XDimk);
    
    if(!use_old_mus)
    {
        for(index_t i = 0; i < XSize; ++i)
        {
            const int32_t Cl = CMath::random(0, k_-1);
            float64_t weight = weights_.vector[i];
            
            weights_set[Cl] += weight;
            ClList[i] = Cl;
            
            vec = lhs->get_feature_vector(i, vlen, vfree);
            for(index_t j = 0; j < dimensions_; ++j)
                mus_.matrix[Cl*dimensions_+j] += weight*vec[j];
            
            lhs->free_feature_vector(vec, i, vfree);
        }
        
        for(index_t i = 0; i < k_; ++i)
        {
            if(weights_set[i] != 0.0)
                for(index_t j = 0; j < dimensions_; ++j)
                    mus_.matrix[i*dimensions_+j] /= weights_set[i];
        }
    }
    else
    {
        ASSERT(mus_start);
        rhs_mus->copy_feature_matrix(HFMatrix<float64_t>(mus_start, 
                                                dimensions_, k_));
        
        float64_t *pdists = dists;
        
        for(index_t i = 0; i < XSize; ++i, pdists+=k_)
            distances_rhs(pdists, 0, k_, i);
        pdists = NULL;
        
        for(index_t i = 0; i < XSize; ++i)
        {
            float64_t mini = dists[i*k_];
            int32_t Cl = 0;
            
            for(index_t j = 1; j < k_; ++j)
            {
                if(dists[i*k_+j] < mini)
                {
                    Cl = j;
                    mini = dists[i*k_+j];
                }
            }
            
            ClList[i] = Cl;
        }
        // TODO
    }
    
    
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