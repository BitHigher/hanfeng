/* 
 * File:   DenseFeatures.cpp
 * Author: zhf
 * 
 * Created on 2013年6月3日, 上午12:26
 */

#include "DenseFeatures.h"
#include "../base/common.h"

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
    len = num_features;
    
    if(feature_matrix.matrix)
    {
        dofree = false;
        return &feature_matrix.matrix[real_num * int64_t(num_features)];
    }
    
    T *feat = NULL;
    dofree = false;
    
    if(feature_cache)
    {
        feat = feature_cache->lock_entry(real_num);
        if(feat)
            return feat;
        else
            feat = feature_cache->set_entry(real_num);
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

template class CDenseFeatures<float64_t>;