/* 
 * File:   Kernel.h
 * Author: zhf
 *
 * Created on 2013年6月11日, 上午2:16
 */

#ifndef KERNEL_H
#define KERNEL_H

#include "../base/HFObject.h"
#include "../features/Features.h"


namespace hanfeng
{

enum EOptimizationType
{
    FASTBUTMEMHUNGRY,
    SLOWBUTMEMEFFICIENT
};
    
enum EKernelType
{
    K_UNKNOWN = 0,
    K_LINEAR = 10,
    K_POLY = 20,
    K_GAUSSIAN = 30
};

class CKernel : public CHFObject
{
public:
    CKernel();
    CKernel(int32_t size);
    CKernel(CFeatures *l, CFeatures *r, int32_t size);
    virtual ~CKernel();
    
    virtual const char* get_name() const { return "Kernel"; }
    
    inline float64_t kernel(int32_t idx_a, int32_t idx_b)
    {
        // TODO kernel
    }
    
    inline CFeatures* get_lhs() { HF_REF(lhs_); return lhs_; }
    inline CFeatures* get_rhs() { HF_REF(rhs_); return rhs_; }
    
    virtual int32_t get_num_vec_lhs() { return num_lhs_;}
    virtual int32_t get_num_vec_rhs() { return num_rhs_;}
    
    virtual bool init(CFeatures *lhs, CFeatures *rhs);
    
private:
    void init();
    
protected:
    int32_t cache_size_;
    CFeatures *lhs_;
    CFeatures *rhs_;
    bool lhs_equals_rhs_;
    int32_t num_lhs_;
    int32_t num_rhs_;
    float64_t combined_kernel_weight_;
    bool optimization_initialized_;
    EOptimizationType opt_type_;
    uint64_t properties_;
    
};

}

#endif	/* KERNEL_H */

