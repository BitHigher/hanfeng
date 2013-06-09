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
    
    virtual void remove_lhs();
    virtual void remove_rhs();
    virtual void remove_lhs_and_rhs();
    
    CFeatures* replace_rhs(CFeatures *rhs);
    
    virtual float64_t distance(int32_t idx_a, int32_t idx_b)
    {
        ASSERT(idx_a >= 0 && idx_b >= 0);
        ASSERT(lhs_ && rhs_);
        
        if(lhs_ == rhs_)
        {
            int32_t num_vectors = lhs_->get_num_vectors();
            if(idx_a >= num_vectors)
                idx_a = 2*num_vectors-1-idx_a;
            
            if(idx_b >= num_vectors)
                idx_b = 2*num_vectors-1-idx_b;
        }
        
        ASSERT(idx_a < lhs_->get_num_vectors());
        ASSERT(idx_b < rhs_->get_num_vectors());
        
        if(precompute_matrix_ && (precomputed_matrix_ == NULL) && lhs_ == rhs_)
            do_precompute_matrix();
        
        if(precompute_matrix_ && precomputed_matrix_)
        {
            if(idx_a >= idx_b)
                return precomputed_matrix_[idx_a*(idx_a+1)/2 + idx_b];
            else
                return precomputed_matrix_[idx_b*(idx_b+1)/2 + idx_a];
        }
        
        return compute(idx_a, idx_b);
    }
    
protected:
    static void* run_distance_thread(void *p);
    virtual float64_t compute(int32_t x, int32_t y) = 0;
    void do_precompute_matrix();
    
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