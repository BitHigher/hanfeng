/* 
 * File:   Machine.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 上午1:33
 */

#include "Machine.h"

using namespace hanfeng;

CMachine::CMachine() : CHFObject(),
max_train_time_(0), 
labels_(NULL),
solver_type_(ST_AUTO)
{
    data_locked_ = false;
    store_model_features_ = false;
    
    // TODO
}

CMachine::~CMachine()
{
    // TODO
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

CLabels* CMachine::apply(CFeatures* data)
{
    CLabels *result = NULL;
    
    switch(get_machine_problem_type())
    {
        case PT_BINARY:
            break;
        case PT_REGRESSION:
            break;
        case PT_MULTICLASS:
            break;
        case PT_STRUCTURED:
            break;
        case PT_LATENT:
            break;
        default:
            HF_ERROR("Unknown problem type");
            break;
    }
    
    return result;
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
    
        // TODO
        // labels_->ensure_valid(get_name());
    }
    
    bool result = train_machine(data);
    
    if(store_model_features_)
        store_model_features();
    
    return result;
}
