/* 
 * File:   KernelMachine.cpp
 * Author: zhf
 * 
 * Created on 2013年6月11日, 上午2:14
 */

#include "KernelMachine.h"

using namespace hanfeng;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct S_THREAD_PARAM_KERNEL_MACHINE
{
    CKernelMachine *kernel_machine;
    float64_t *result;
    int32_t start;
    int32_t end;
    
    index_t *indices;
    index_t indices_len;
    bool verbose;
};

#endif


CKernelMachine::CKernelMachine()
{
    init();
}

CKernelMachine::CKernelMachine(CKernel* k, const HFVector<float64_t> alphas, 
                                const HFVector<int32_t> svs, float64_t b)
{
    init();
    
    int32_t num_sv = svs.vlen;
    ASSERT(svs.vlen == alphas.vlen);
    create_new_model(num_sv);
    set_alphas(alphas);
    set_support_vectors(svs);
    set_kernel(k);
    set_bias(b);
}

CKernelMachine::CKernelMachine(CKernelMachine* machine)
{
    init();
    
    // TODO 
}

CKernelMachine::~CKernelMachine()
{
    HF_UNREF(kernel_);
    // TODO HF_UNREF(custom_kernel_);
    HF_UNREF(kernel_backup_);
}

void CKernelMachine::set_kernel(CKernel* k)
{
    HF_REF(k);
    HF_UNREF(kernel_);
    kernel_ = k;
}

bool CKernelMachine::create_new_model(int32_t num)
{
    bias_ = 0;
    if(num > 0)
    {
        alphas_ = HFVector<float64_t>(num);
        svs_ = HFVector<int32_t>(num);
        return (alphas_.vector && svs_.vector);
    }
    else
    {
        alphas_ = HFVector<float64_t>();
        svs_ = HFVector<int32_t>();
        return true;
    }
}

void CKernelMachine::store_model_features()
{
    ASSERT(kernel_);
    
    // TODO store_model_features
}

void CKernelMachine::init()
{
    bias_ = 0.0;
    kernel_ = NULL;
    // TODO custom_kernel_ = NULL;
    kernel_backup_ = NULL;
    use_batch_computation_ = true;
    use_linadd_ = true;
    use_bias_ = true;
    
    // TODO register parameters
}

CMachine* CKernelMachine::clone()
{
    return new CKernelMachine(this);
}

HFVector<float64_t> CKernelMachine::apply_get_outputs(CFeatures* data)
{
    ASSERT(kernel_);
    ASSERT(kernel_->get_num_vec_lhs());
    
    if(data)
    {
        CFeatures *lhs = kernel_->get_lhs();
        ASSERT(lhs);
        kernel_->init(lhs, data);
        HF_UNREF(lhs);
    }
    
    CFeatures *rhs = kernel_->get_rhs();
    int32_t num_vectors = rhs?rhs->get_num_vectors():kernel_->get_num_vec_rhs();
    HF_UNREF(rhs);
    
    HFVector<float64_t> output(num_vectors);
    if(kernel_->get_num_vec_rhs() > 0)
    {
        // TODO apply_get_outputs
    }
    
    
}