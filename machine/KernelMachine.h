/* 
 * File:   KernelMachine.h
 * Author: zhf
 *
 * Created on 2013年6月11日, 上午2:14
 */

#ifndef KERNELMACHINE_H
#define KERNELMACHINE_H

#include "../machine/Machine.h"
#include "../kernel/Kernel.h"
#include "../kernel/CustomKernel.h"

namespace hanfeng
{

class CKernelMachine : public CMachine
{
public:
    CKernelMachine();
    CKernelMachine(CKernel *k, const HFVector<float64_t> alphas, 
                        const HFVector<int32_t> svs, float64_t b);
    CKernelMachine(CKernelMachine *machine);
    
    virtual ~CKernelMachine();
    
    virtual const char* get_name() const { return "KernelMachine"; }
    
    inline void set_kernel(CKernel *k)
    {
        HF_REF(k);
        HF_UNREF(kernel_);
        kernel_ = k;
    }
    
    inline CKernel* get_kenrel()
    {
        HF_REF(kernel_);
        return kernel_;
    }
    
    inline void set_batch_computation_enabled(bool enable)
    {
        use_batch_computation_ = enable;
    }
    
    inline bool get_batch_computation_enabled() const
    {
        return use_batch_computation_;
    }
    
    inline void set_linadd_enabled(bool enable)
    {
        use_linadd_ = enable;
    }
    
    inline bool get_linadd_enabled() const
    {
        return use_linadd_;
    }
    
    inline void set_bias_enabled(bool enable)
    {
        use_bias_ = enable;
    }
    
    inline bool get_bias_enabled() const
    {
        return use_bias_;
    }
    
    inline void set_bias(float64_t bias)
    {
        bias_ = bias;
    }
    
    inline float64_t get_bias() const
    {
        return bias_;
    }
    
    inline bool set_alpha(int32_t idx, float64_t val)
    {
        if(alphas_.vector && idx < alphas_.vlen)
        {
            alphas_.vector[idx] = val;
            return true;
        }
        else
            return false;
    }
    
    inline float64_t get_alpha(int32_t idx) const
    {
        ASSERT(alphas_.vector && idx < alphas_.vlen);
        return alphas_.vector[idx];
    }
    
    inline void set_alphas(HFVector<float64_t> alphas)
    {
        alphas_ = alphas;
    }
    
    inline HFVector<float64_t> get_alphas()
    {
        return alphas_;
        // FIXME is there bug? no ref !
    }
    
    inline bool set_support_vector(int32_t idx, int32_t val)
    {
        if(svs_.vector && idx < svs_.vlen)
        {
            svs_.vector[idx] = val;
            return true;
        }
        else
            return false;
    }
    
    inline int32_t get_support_vector(int32_t idx)
    {
        ASSERT(svs_.vector && idx < svs_.vlen);
        return svs_.vector[idx];
    }
    
    inline void set_support_vectors(HFVector<int32_t> svs)
    {
        svs_ = svs;
    }
    
    inline HFVector<int32_t> get_support_vectors()
    {
        return svs_;
    }
    
    bool create_new_model(int32_t num);
    bool init_kernel_optimization();
    
    
   
    virtual CMachine* clone();
    
protected:
    HFVector<float64_t> apply_get_outputs(CFeatures *data);
    virtual void store_model_features();
    
private:
    void init();
    
protected:
    CKernel *kernel_;
    CCustomKernel *custom_kernel_;
    CKernel *kernel_backup_;
    bool use_batch_computation_;
    bool use_linadd_;
    bool use_bias_;
    float64_t bias_;
    HFVector<float64_t> alphas_;
    HFVector<int32_t> svs_; /**< support vectors */
    
};

}

#endif	/* KERNELMACHINE_H */

