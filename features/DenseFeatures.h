/* 
 * File:   DenseFeatures.h
 * Author: zhf
 *
 * Created on 2013年6月3日, 上午12:26
 */

#ifndef DENSEFEATURES_H
#define DENSEFEATURES_H

#include "DotFeatures.h"
#include "../structure/HFMatrix.h"
#include "../structure/Cache.h"

namespace hanfeng
{

template<class T> class CDenseFeatures : public CDotFeatures{
public:
    CDenseFeatures();
    CDenseFeatures(const CDenseFeatures& orig);
    virtual ~CDenseFeatures();

    virtual EFeatureType get_feature_type() const;
    virtual EFeatureClass get_feature_class() const {return C_DENSE;}
    
    T* get_feature_vector(int32_t num, int32_t &len, bool &dofree);
    HFVector<T> get_feature_vecotr(int32_t num);
    
    void free_feature_vector(T *feat_vec, int32_t num, bool dofree);

    virtual void add_to_dense_vec(float64_t alpha, int32_t vec_idx1, 
               float64_t *vec2, int32_t vec2_len, bool abs_val = false);
    
protected:
    int32_t num_vectors_;
    int32_t num_features_;
    
    HFMatrix<T> feature_matrix_;
    CCache<T> *feature_cache_;
};

}
#endif	/* DENSEFEATURES_H */

