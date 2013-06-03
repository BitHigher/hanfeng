/* 
 * File:   DotFeatures.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 下午1:35
 */

#ifndef FEATURES_DOTFEATURES_H
#define FEATURES_DOTFEATURES_H

#include "Features.h"
#include "../base/common.h"

namespace hanfeng
{

class CDotFeatures : public CFeatures {
public:
    CDotFeatures();
    CDotFeatures(const CDotFeatures& orig);
    virtual ~CDotFeatures();
    
    virtual float64_t dense_dot(int32_t vec_idx1, 
                                const float64_t *vec2,
                                int32_t vec2_len) = 0;
    
    virtual int32_t get_dim_feature_space() const = 0;
    virtual void dense_dot_range(float64_t *output, int32_t start,
                                int32_t stop, float64_t *alphas,
                                float64_t *vec, int32_t dim,
                                float64_t b);
    
    virtual void add_to_dense_vec(float64_t alpha, int32_t vec_idx1, 
               float64_t *vec2, int32_t vec2_len, bool abs_val = false) = 0;
private:

};

}

#endif	/* FEATURES_DOTFEATURES_H */

