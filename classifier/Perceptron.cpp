/* 
 * File:   Perceptron.cpp
 * Author: zhf
 * 
 * Created on 2013年6月4日, 上午12:43
 */

#include "Perceptron.h"
#include "../math/Math.h"
#include "../io/HFIO.h"

using namespace hanfeng;

CPerceptron::CPerceptron()
: learn_rate_(0.1), max_iter_(1000)
{
}

CPerceptron::CPerceptron(CDotFeatures* traindat, CLabels* trainlab)
: learn_rate_(0.1), max_iter_(1000)
{
    set_features(traindat);
    set_labels(trainlab);
}

CPerceptron::~CPerceptron()
{
}

bool CPerceptron::train_machine(CFeatures *data)
{
    ASSERT(labels_);
    ASSERT(labels_->get_label_type() == LT_BINARY);
    
    if(data)
    {
        if(!data->has_property(FP_DOT))
            HF_ERROR("Specified features are not of type CDotFeatures");
        
        set_features((CDotFeatures*)data);
    }
    
    ASSERT(features_);
    bool converged = false;
    int32_t iter = 0;
    
    HFVector<int32_t> train_labels = ((CBinaryLabels*)labels_)->get_int_labels();
    int32_t num_feat = features_->get_dim_feature_space();
    int32_t num_vec = features_->get_num_vectors();
    
    ASSERT(num_vec == train_labels.vlen);
    w_ = HFVector<float64_t>(num_feat);
    float64_t *output = HF_MALLOC(float64_t, num_vec);
    
    // starts with uniform w, bias = 0
    bias_ = 0.0;
    for(index_t i = 0; i < num_feat; ++i)
        w_.vector[i] = 1.0/num_feat;
    
    // loop till either get everything classified right or reach max_iter_
    while(!converged && iter < max_iter_)
    {
        converged = true;
        for(index_t i = 0; i < num_vec; ++i)
        {
            output[i] = apply_one(i);
            if(CMath::sign<float64_t>(output[i]) != train_labels.vector[i])
            {
                converged = false;
                bias_ += learn_rate_ * train_labels.vector[i];
                features_->add_to_dense_vec(learn_rate_*train_labels.vector[i],
                                                i, w_.vector, w_.vlen);
            }
        }
        
        iter++;
    }
    
    if(converged)
        HF_INFO("Perceptron algorithm converged after %d iterations.", iter)
    else
        HF_WARNING("Perceptron algorithm dit not converge "
                   "after %d iterations.", iter);
    
#ifdef DEBUG_PERCEPTRON
    HF_PRINT("Perceptron algorithm converged after %d iterations.\n", iter)
    HF_PRINT("bias: %f\n", bias_);
    HFVector<float64_t>::display_vector(w_, num_feat, "w");
#endif
    
    
    HF_FREE(output);
    
    return converged;
}
