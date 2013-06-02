/* 
 * File:   LinearMachine.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 上午1:31
 */

#ifndef MACHINE_LINEARMACHINE_H
#define MACHINE_LINEARMACHINE_H

#include "Machine.h"
#include "../features/DotFeatures.h"

namespace hanfeng
{

class CLinearMachine : public CMachine{
public:
    CLinearMachine();
    CLinearMachine(CLinearMachine *machine);
    virtual ~CLinearMachine();
    
    virtual HFVector<float64_t> get_w() const {return w_;}
    
    virtual void set_w(HFVector<float64_t> src_w) {w_ = src_w;}
    
    virtual float64_t get_bias(){return bias_;}
    virtual void set_bias(float64_t bias){ bias_ = bias; }
    
    virtual void set_features(CDotFeatures *data);
    virtual CDotFeatures* get_features();
    
    virtual const char* get_name() const {return "LinearMachine";}
    
    virtual CMachine* clone();
    
    virtual float64_t apply_one(int32_t vec_idx);
    virtual CBinaryLabels* apply_binary(CFeatures *data = NULL);
    virtual CRegressionLabels* apply_regression(CFeatures *data = NULL);
    
private:
    void init();
    
protected:
    virtual void store_model_features();
    
    virtual HFVector<float64_t> apply_get_outputs(CFeatures *data);
    
protected:
    HFVector<float64_t> w_;
    float64_t bias_;
    CDotFeatures *features_;
};

}

#endif	/* MACHINE_LINEARMACHINE_H */

