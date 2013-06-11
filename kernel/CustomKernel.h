/* 
 * File:   CustomKernel.h
 * Author: zhf
 *
 * Created on 2013年6月11日, 下午8:02
 */

#ifndef CUSTOMKERNEL_H
#define CUSTOMKERNEL_H

#include "Kernel.h"

namespace hanfeng
{

class CCustomKernel : public CKernel
{
public:
    CCustomKernel();
    CCustomKernel(CKernel *k);
    CCustomKernel(HFMatrix<float64_t> km);
    virtual ~CCustomKernel();

    virtual const char* get_name() const { return "CustomKernel"; }
    
    virtual bool init(CFeatures *l, CFeatures *r);
    virtual EKernelType get_kernel_type() const { return K_CUSTOM; }
    virtual EFeatureType get_feature_type() const { return F_ANY;}
    virtual EFeatureClass get_feature_class() const { return C_ANY; }
    
private:
    void init();
    
protected:
    HFMatrix<float64_t> kmatrix_;
    bool upper_diagonal_;
    CSubsetStack *row_subset_stack_;
    CSubsetStack *col_subset_stack_;
    bool free_km_;
};

}

#endif	/* CUSTOMKERNEL_H */

