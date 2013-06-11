/* 
 * File:   KernelNormalizer.h
 * Author: zhf
 *
 * Created on 2013年6月11日, 下午12:20
 */

#ifndef KERNELNORMALIZER_H
#define KERNELNORMALIZER_H

#include "../../base/HFObject.h"

namespace hanfeng
{

enum ENormalizerType
{
    N_REGULAR = 0,
    N_MULTITASK = 1
};
    
    
class CKernelNormalizer : CHFObject
{
public:
    CKernelNormalizer()
    {
        type_ = N_REGULAR;
        
        HF_ADD(&type_, "type", "Normalizer Type", MS_NOT_AVAILABLE);
    }
         
    virtual ~CKernelNormalizer(){}
    
    virtual const char* get_name() const { return "KernelNormalizer"; }
    
    virtual bool init(CKernel *k) = 0;
    virtual float64_t normalize(float64_t value, 
                                int32_t idx_lhs, int32_t idx_rhs) = 0;
    virtual float64_t normalize_lhs(float64_t value, int32_t idx_lhs) = 0;
    virtual float64_t normalize_rhs(float64_t value, int32_t idx_rhs) = 0;
    
    inline void set_normalizer_type(ENormalizerType type) { type_ = type; }
    inline ENormalizerType get_normalizer_type() const { return type_; }
    
protected:
    ENormalizerType type_;
};


}
#endif	/* KERNELNORMALIZER_H */

