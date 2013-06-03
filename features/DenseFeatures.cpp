/* 
 * File:   DenseFeatures.cpp
 * Author: zhf
 * 
 * Created on 2013年6月3日, 上午12:26
 */

#include "DenseFeatures.h"
#include "../base/common.h"
#include "../math/Math.h"

using namespace hanfeng;

template<class T>
CDenseFeatures<T>::CDenseFeatures()
{
}

template<class T>
CDenseFeatures<T>::~CDenseFeatures() {
}


namespace hanfeng
{

#define GET_FEATURE_TYPE(f_type, hf_type) \
template<> EFeatureType CDenseFeatures<hf_type>::get_feature_type() const \
{ \
    return f_type; \
}

GET_FEATURE_TYPE(F_BOOL, bool)
GET_FEATURE_TYPE(F_DREAL, float64_t)

#undef GET_FEATURE_TYPE

}

template<class T>
T* CDenseFeatures<T>::get_feature_vector(int32_t num, int32_t& len, bool& dofree)
{
    int32_t real_num = subset_stack_->subset_idx_conversion(num);
    len = num_features_;
    
    if(feature_matrix_.matrix)
    {
        dofree = false;
        return &feature_matrix_.matrix[real_num * int64_t(num_features_)];
    }
    
    T *feat = NULL;
    dofree = false;
    
    if(feature_cache_)
    {
        feat = feature_cache_->lock_entry(real_num);
        if(feat)
            return feat;
        else
            feat = feature_cache_->set_entry(real_num);
    }
    
    // TODO
    
    return NULL;
}

template<class T>
HFVector<T> CDenseFeatures<T>::get_feature_vecotr(int32_t num)
{
    int32_t real_num = subset_stack_->subset_idx_conversion(num);
    
    // TODO num , not real_num ???
    if(num >= get_num_vectors())
        HF_ERROR("Index out of bound (number of vectors %d, "
                "you requested %d)", get_num_vectors(), real_num);
    
    int32_t vlen;
    bool do_free;
    T *vector = get_feature_vector(num, vlen, do_free);
    return HFVector<T>(vector, vlen, do_free);
}

template<class T>
void CDenseFeatures<T>::free_feature_vector(T* feat_vec, 
                                                int32_t num, bool dofree)
{
    // TODO
}

template<class T>
void CDenseFeatures<T>::add_to_dense_vec(float64_t alpha, int32_t vec_idx1, 
                float64_t* vec2, int32_t vec2_len, bool abs_val)
{
    ASSERT(vec2_len == num_features_);
    
    int32_t vlen;
    bool vfree;
    T *vec1 = get_feature_vector(vec_idx1, vlen, vfree);
    
    ASSERT(vlen == num_features_);
    
    if(abs_val)
    {
        for(index_t i = 0; i < num_features_; ++i)
            vec2[i] += alpha * CMath::abs(vec1[i]);
    }
    else
    {
        for(index_t i = 0; i < num_features_; ++i)
            vec2[i] += alpha * vec1[i];
    }
    
    free_feature_vector(vec1, vec_idx1, vfree);
}

template class CDenseFeatures<float64_t>;