/* 
 * File:   LinearMachine.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 上午1:31
 */

#include "LinearMachine.h"

using namespace hanfeng;

CLinearMachine::CLinearMachine()
: CMachine(), bias_(0), features_(NULL)
{
    init();
}

CLinearMachine::CLinearMachine(CLinearMachine *machine)
: CMachine(), bias_(0), features_(NULL)
{
    set_w(machine->get_w().clone());
    set_bias(machine->get_bias());

    init();
}

CLinearMachine::~CLinearMachine()
{
    HF_UNREF(features_);
}

void CLinearMachine::init()
{
    // TOOD
    // HF_ADD()
}

void CLinearMachine::set_features(CDotFeatures *data)
{
    HF_REF(data);
    HF_UNREF(features_);
    features_ = data;
}

CDotFeatures* CLinearMachine::get_features()
{
    HF_REF(features_);
    return features_;
}

CMachine* CLinearMachine::clone()
{
    return new CLinearMachine(this);
}

void CLinearMachine::store_model_features()
{
}

float64_t CLinearMachine::apply_one(int32_t vec_idx)
{
    return features_->dense_dot(vec_idx, w_.vector, w_.vlen) + bias_;
}

CBinaryLabels* CLinearMachine::apply_binary(CFeatures* data)
{
    HFVector<float64_t> outputs = apply_get_outputs(data);
    //return new CBinaryLabels(outputs);
    return NULL;
}

CRegressionLabels* CLinearMachine::apply_regression(CFeatures* data)
{
    HFVector<float64_t> outputs = apply_get_outputs(data);
    // return new CRegressionLabels(outputs);
    return NULL;
}

HFVector<float64_t> CLinearMachine::apply_get_outputs(CFeatures* data)
{
    if(data)
    {
        if(!data->has_property(FP_DOT))
            HF_ERROR("Specified features are not of type CDotFeatures");
    
        set_features((CDotFeatures*)data);
    }
    
    if(!features_)
        return HFVector<float64_t>();
    
    // TODO
    int32_t num = features_->get_num_vectors();
    ASSERT(num > 0);
    ASSERT(w_.vlen == features_->get_dim_feature_space());

    float64_t *out = HF_MALLOC(float64_t, num);
    features_->dense_dot_range(out, 0, num, NULL, w_.vector, w_.vlen, bias_);
    
    return HFVector<float64_t>(out, num);
}