/* 
 * File:   LDA.cpp
 * Author: zhf
 * 
 * Created on 2013年6月3日, 上午12:16
 */

#include "../base/common.h"

#ifdef HAVE_LAPACK

#include "LDA.h"
#include "../math/Math.h"
#include "../structure/HFMatrix.h"
#include "../io/HFIO.h"

using namespace hanfeng;

CLDA::CLDA(float64_t gamma)
: CLinearMachine(), gamma_(gamma)
{
}

CLDA::CLDA(float64_t gamma, CDenseFeatures<float64_t> *traindat, 
                CLabels *trainlab)
: CLinearMachine(), gamma_(gamma)
{
    set_features(traindat);
    set_labels(trainlab);
}

CLDA::~CLDA()
{
}

bool CLDA::train_machine(CFeatures *data)
{
    ASSERT(labels_);
    if(data)
    {
        if(!data->has_property(FP_DOT))
            HF_ERROR("Specified features are not of type CDotFeatures");
        
        set_features((CDotFeatures*)data);
    }
    
    ASSERT(features_);
    
    HFVector<int32_t> train_labels=((CBinaryLabels*)labels_)->get_int_labels();
    ASSERT(train_labels.vector);
    
    int32_t num_feat = features_->get_dim_feature_space();
    int32_t num_vec = features_->get_num_vectors();
    ASSERT(num_vec == train_labels.vlen);
    
    int32_t *classidx_neg = HF_MALLOC(int32_t, num_vec);
    int32_t *classidx_pos = HF_MALLOC(int32_t, num_vec);
    
    int32_t i = 0;
    int32_t j = 0;
    int32_t num_neg = 0;
    int32_t num_pos = 0;
    
    for(i = 0; i < num_vec; ++i)
    {
        if(train_labels.vector[i] == -1)
            classidx_neg[num_neg++] = i;
        else if(train_labels.vector[i] == 1)
            classidx_pos[num_pos++] = i;
        else
        {
            HF_ERROR("found label != +/- 1");
            return false;
        }
    }
    
    if(num_neg == 0 || num_pos == 0)
    {
        HF_ERROR("only a single class found");
        return false;
    }
    
    w_ = HFVector<float64_t>(num_feat);
    
    float64_t *mean_neg = HF_MALLOC(float64_t, num_feat);
    memset(mean_neg, 0, num_feat*sizeof(float64_t));
    
    float64_t *mean_pos = HF_MALLOC(float64_t, num_feat);
    memset(mean_pos, 0, num_feat*sizeof(float64_t));
    
    float64_t *scatter = HF_MALLOC(float64_t, num_feat*num_feat);
    float64_t *buffer = HF_MALLOC(float64_t, 
                                num_feat*CMath::max(num_neg, num_pos));

    int32_t nf = (int32_t)num_feat;
    
    CDenseFeatures<float64_t> *rf = (CDenseFeatures<float64_t>*)features_;
    
    // mean neg
    for(i = 0; i < num_neg; ++i)
    {
        // TODO
    }
    
    
    // mean pos
    for(i = 0; i < num_pos; ++i)
    {
        // TODO
    }
    
    
    float64_t trace = HFMatrix<float64_t>::trace(scatter, num_feat, num_feat);
    
#ifdef DEBUG_LDA
        // TODO
#endif
    
    // TODO
    HF_FREE(classidx_neg);
    HF_FREE(classidx_pos);
    HF_FREE(mean_neg);
    HF_FREE(mean_pos);
    HF_FREE(scatter);
    HF_FREE(buffer);
    
    return true;
}



#endif  /* HAVE_LAPACK */