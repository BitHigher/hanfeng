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

class CKernel : public CHFObject
{
public:
    CKernel();
    CKernel(int32_t size);
    CKernel(CFeatures *l, CFeatures *r, int32_t size);
    virtual ~CKernel();
    
    virtual const char* get_name() const { return "Kernel"; }
    
    
private:
    void init();
    
protected:
    int32_t cache_size_;
    CFeatures *lhs_;
    CFeatures *rhs_;
    int32_t num_lhs_;
    int32_t num_rhs_;

};

}

#endif	/* KERNEL_H */

