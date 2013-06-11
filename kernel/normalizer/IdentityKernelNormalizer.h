/* 
 * File:   IdentityKernelNormalizer.h
 * Author: zhf
 *
 * Created on 2013年6月11日, 下午1:01
 */

#ifndef IDENTITYKERNELNORMALIZER_H
#define IDENTITYKERNELNORMALIZER_H

#include "KernelNormalizer.h"

namespace hanfeng
{
 
class CIdentityKernelNormalizer : public CKernelNormalizer
{
public:
    CIdentityKernelNormalizer(){}
    virtual ~CIdentityKernelNormalizer(){}
    
    virtual const char* get_name() const { return "IdentityKernelNormalizer"; }
    
    virtual bool init(CKernel *k)
    {
        return true;
    }
    
    virtual float64_t normalize(float64_t value, int32_t idx_lhs, 
                                int32_t idx_rhs)
    {
        return value;
    }
    
    virtual float64_t normalize_lhs(float64_t value, int32_t idx_lhs)
    {
        return value;
    }
    
    virtual float64_t normalize_rhs(float64_t value, int32_t idx_rhs)
    {
        return value;
    }
};
    
}


#endif	/* IDENTITYKERNELNORMALIZER_H */

