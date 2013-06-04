/* 
 * File:   Distance.h
 * Author: zhf
 *
 * Created on 2013年6月4日, 下午8:41
 */

#ifndef DISTANCE_DISTANCE_H
#define DISTANCE_DISTANCE_H

#include "../base/HFObject.h"
#include "../features/Features.h"

namespace hanfeng
{

class CDistance : public CHFObject {
public:
    CDistance();
    CDistance(CFeatures *lhs, CFeatures *rhs);
    virtual ~CDistance();
    
    inline CFeatures* get_lhs(){HF_REF(lhs_); return lhs_;}
    inline CFeatures* get_rhs(){HF_REF(rhs_); return rhs_;}
    
    virtual bool init(CFeatures *lhs, CFeatures *rhs);
    
    virtual EFeatureType get_feature_type() = 0;
    
private:
    void init();
    
protected:
    float32_t *precomputed_matrix_;
    bool precompute_matrix_;
    
    CFeatures *lhs_;
    CFeatures *rhs_;
    
    int32_t num_lhs_;
    int32_t num_rhs_;
};

}

#endif	/* DISTANCE_DISTANCE_H */