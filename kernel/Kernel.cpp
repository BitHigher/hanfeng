/* 
 * File:   Kernel.cpp
 * Author: zhf
 * 
 * Created on 2013年6月11日, 上午2:16
 */

#include "Kernel.h"

using namespace hanfeng;

CKernel::CKernel()
{
    init();
    
    // TODO register parameters;
}

CKernel::CKernel(int32_t size)
{
    init();
    
    if(size < 10)
        size = 10;
    
    cache_size_ = size;
    
    // TODO register parameters
}

CKernel::CKernel(CFeatures* l, CFeatures* r, int32_t size)
{
    
}

CKernel::~CKernel()
{
}

void CKernel::init()
{
    cache_size_ = 10;
    // TODO kernel_matrix
    lhs_ = NULL;
    rhs_ = NULL;
    num_lhs_ = 0;
    num_rhs_ = 0;
    
    // TODO init
}