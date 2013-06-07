/* 
 * File:   Machine.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 上午1:33
 */

#include "Machine.h"
#include "../base/Parameter.h"
#include "../base/ParameterMap.h"

using namespace hanfeng;

CMachine::CMachine() : CHFObject(),
max_train_time_(0), 
labels_(NULL),
solver_type_(ST_AUTO)
{
    data_locked_ = false;
    store_model_features_ = false;
    
    HF_ADD(&max_train_time_, "max_train_time",
            "Maximum training time.", MS_NOT_AVAILABLE);
    
    HF_ADD((machine_int_t*)&solver_type_, "solver_type",
            "Type of solver.", MS_NOT_AVAILABLE);
    
    HF_ADD((CHFObject**)&labels_, "labels",
            "Labels to be used.", MS_NOT_AVAILABLE);
    
    HF_ADD(&store_model_features_, "store_model_features",
            "Should feature data of model be stored after training?", 
            MS_NOT_AVAILABLE);
    
    HF_ADD(&data_locked_, "data_locked",
            "Whether data is locked?", MS_NOT_AVAILABLE);
    
    parameter_map->put(
               new HFParamInfo("data_locked", CT_SCALAR, ST_NONE, PT_BOOL, 1),
               new HFParamInfo());
    
    parameter_map->finalize_map();
}

CMachine::~CMachine()
{
    HF_UNREF(labels_);
}

void CMachine::set_labels(CLabels* labels)
{
    if(labels != NULL)
        if(!is_label_valid(labels))
            HF_ERROR("Invalid label for %s", get_name());
    
    HF_UNREF(labels_);
    HF_REF(labels);
    labels_ = labels;
}

CLabels* CMachine::get_labels()
{
    HF_REF(labels_);
    return labels_;
}

bool CMachine::train(CFeatures *data)
{
    if(data_locked_)
    {
        HF_ERROR("%s::train data_lock was called, only "
                "train_locked() is possible. Call data_unlock() "
                "if you want to call train()", get_name());
    }
    
    if(train_require_labels())
    {
        if(labels_ == NULL)
            HF_ERROR("%s@%p: No labels given", get_name(), this);
    
        labels_->ensure_valid(get_name());
    }
    
    bool result = train_machine(data);
    
    if(store_model_features_)
        store_model_features();
    
    return result;
}

CLabels* CMachine::apply(CFeatures* data)
{
    CLabels *result = NULL;
    
    switch(get_machine_problem_type())
    {
        case PT_BINARY:
            result = apply_binary(data);
            break;
        case PT_REGRESSION:
            result = apply_regression(data);
            break;
        case PT_MULTICLASS:
            result = apply_multiclass(data);
            break;
        case PT_STRUCTURED:
            result = apply_structured(data);
            break;
        case PT_LATENT:
            result = apply_latent(data);
            break;
        default:
            HF_ERROR("Unknown problem type");
            break;
    }
    
    return result;
}

CBinaryLabels* CMachine::apply_binary(CFeatures* data)
{
    HF_ERROR("%s does not support apply_binary()", get_name());
    return NULL;
}

CRegressionLabels* CMachine::apply_regression(CFeatures* data)
{
    HF_ERROR("%s does not support apply_regression()", get_name());
    return NULL;
}

CMultiClassLabels* CMachine::apply_multiclass(CFeatures* data)
{
    HF_ERROR("%s does not support apply_multiclass()", get_name());
    return NULL;
}

CStructuredLabels* CMachine::apply_structured(CFeatures* data)
{
    HF_ERROR("%s does not support apply_structured()", get_name());
    return NULL;
}

CLatentLabels* CMachine::apply_latent(CFeatures* data)
{
    HF_ERROR("%s does not support apply_latent()", get_name());
    return NULL;
}

void CMachine::set_store_model_features(bool store_model)
{
    store_model_features_ = store_model;
}