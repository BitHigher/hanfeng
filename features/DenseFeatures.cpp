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
CDenseFeatures<T>::CDenseFeatures(int32_t size)
: CDotFeatures(size)
{
    init();
}

template<class T>
CDenseFeatures<T>::CDenseFeatures(const CDenseFeatures &orig)
: CDotFeatures(orig)
{
    init();
    set_feature_matrix(orig.feature_matrix_);
    
    initialize_cache();
    
    if(orig.subset_stack_)
    {
        HF_UNREF(subset_stack_);
        subset_stack_ = new CSubsetStack(*orig.subset_stack_);
        HF_REF(subset_stack_);
    }
}

template<class T>
CDenseFeatures<T>::CDenseFeatures(HFMatrix<T> matrix)
{
    init();
    set_feature_matrix(matrix);
}

template<class T>
CDenseFeatures<T>::~CDenseFeatures()
{
    
}

template<class T>
void CDenseFeatures<T>::free_feature_matrix()
{
    subset_stack_->remove_all_subsets();
    feature_matrix_ = HFMatrix<T>();
    num_features_ = 0;
    num_vectors_ = 0;
}

template<class T>
void CDenseFeatures<T>::set_feature_matrix(HFMatrix<T> matrix)
{
    subset_stack_->remove_all_subsets();
    free_feature_matrix();
    
    feature_matrix_ = matrix;
    num_features_ = matrix.num_rows;
    num_vectors_ = matrix.num_cols;
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


template<>
float64_t CDenseFeatures<float64_t>::dense_dot(int32_t vec_idx1, 
                                const float64_t* vec2, int32_t vec2_len)
{
    ASSERT(vec2_len == num_features_);
    
    int32_t vlen;
    bool vfree;
    float64_t *vec1 = get_feature_vector(vec_idx1, vlen, vfree);
    
    ASSERT(vlen == num_features_);
    float64_t result = HFVector<float64_t>::dot(vec1, vec2, vlen);
    
    free_feature_vector(vec1, vec_idx1, vfree);
    
    return result;
}


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
void CDenseFeatures<T>::free_feature_vector(HFVector<T> vec, int32_t num)
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

template<class T>
HFMatrix<T> CDenseFeatures<T>::get_feature_matrix()
{
    // TODO
    HF_NOTIMPLEMENTED
    return HFMatrix<T>();
}

template<class T>
CFeatures* CDenseFeatures<T>::duplicate() const
{
    return new CDenseFeatures<T>(*this);
}

template<class T>
void CDenseFeatures<T>::init()
{
    num_features_ = 0;
    num_vectors_ = 0;
    
    feature_matrix_ = HFMatrix<T>();
    feature_cache_ = NULL;
    
    // TODO
    HF_NOTIMPLEMENTED
}

template<class T>
int32_t CDenseFeatures<T>::get_num_vectors() const
{
    return subset_stack_->has_subsets()?subset_stack_->get_size():num_vectors_;
}

template<class T>
int32_t CDenseFeatures<T>::get_dim_feature_space() const
{
    return num_features_;
}

template<class T>
int32_t CDenseFeatures<T>::get_size() const
{
    // TODO is this right???
    return sizeof(T);
}

template<class T>
void CDenseFeatures<T>::initialize_cache()
{
    if(subset_stack_->has_subsets())
        HF_ERROR("A subset is set, cannot call initialize_cache()");
    
    if(num_features_ && num_vectors_)
    {
        HF_UNREF(feature_cache_);
        feature_cache_ = new CCache<T>(get_cache_size(), 
                                        num_features_, num_vectors_);
        
        HF_REF(feature_cache_);
    }
}


template class CDenseFeatures<float64_t>;