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
#include "../math/lapack.h"
#include "../structure/HFMatrix.h"
#include "../io/HFIO.h"

using namespace hanfeng;

CLDA::CLDA(float64_t gamma)
: gamma_(gamma)
{
}

CLDA::CLDA(float64_t gamma, CDenseFeatures<float64_t> *traindat, 
                CLabels *trainlab)
: gamma_(gamma)
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
        int32_t vlen;
        bool vfree;
        float64_t *vec = rf->get_feature_vector(classidx_neg[i], vlen, vfree);
        
        ASSERT(vec);
        
        for(j = 0; j < vlen; ++j)
        {
            mean_neg[j] += vec[j];
            buffer[num_feat*i+j] = vec[j];
        }
        
        rf->free_feature_vector(vec, classidx_neg[i], vfree);
    }
    
    for(j = 0; j < num_feat; ++j)
        mean_neg[j] /= num_neg;
    
    for(i = 0; i < num_neg; ++i)
    {
        for(j = 0; j < num_feat; ++j)
            buffer[i*num_feat+j] -= mean_neg[j];
    }
    
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans, nf, nf,
                num_neg, 1.0, buffer, nf, buffer, nf, 0, scatter, nf);
    
    // mean pos
    for(i = 0; i < num_pos; ++i)
    {
        int32_t vlen;
        bool vfree;
        float64_t *vec = rf->get_feature_vector(classidx_pos[i], vlen, vfree);
        
        ASSERT(vec);
        
        for(j = 0; j < vlen; ++j)
        {
            mean_pos[j] += vec[j];
            buffer[num_feat*i+j] = vec[j];
        }
        
        rf->free_feature_vector(vec, classidx_pos[i], vfree);
    }
    
    for(j = 0; j < num_feat; ++j)
        mean_pos[j] /= num_pos;
    
    for(i = 0; i < num_pos; ++i)
    {
        for(j = 0; j < num_feat; ++j)
            buffer[i*num_feat+j] -= mean_pos[j];
    }
    
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasTrans, nf, nf, num_pos,
                1.0/(train_labels.vlen-1), buffer, nf, buffer, nf,
                1.0/(train_labels.vlen-1), scatter, nf);
    
    float64_t trace = HFMatrix<float64_t>::trace(scatter, num_feat, num_feat);
    
    float64_t s = 1.0 - gamma_;
    for(i = 0; i < num_feat*num_feat; ++i)
        scatter[i] *= s;
    
    for(i = 0; i < num_feat; ++i)
        scatter[i*num_feat+i] += trace*gamma_/num_feat;
    
    float64_t *inv_scatter = (float64_t*)HFMatrix<float64_t>::pinv(
                                scatter, num_feat, num_feat, NULL);
    
    float64_t *w_pos = buffer;
    float64_t *w_neg = &buffer[num_feat];
    
    cblas_dsymv(CblasColMajor, CblasUpper, nf, 1.0, inv_scatter, nf,
                     (double*) mean_pos, 1, 0., (double*) w_pos, 1);
    cblas_dsymv(CblasColMajor, CblasUpper, nf, 1.0, inv_scatter, nf,
                     (double*) mean_neg, 1, 0, (double*) w_neg, 1);
    
    bias_ = 0.5 * (HFVector<float64_t>::dot(w_neg, mean_neg, num_feat) - 
                   HFVector<float64_t>::dot(w_pos, mean_pos, num_feat));
    
    for(i = 0; i < num_feat; ++i)
        w_.vector[i] = w_pos[i] - w_neg[i];
    
#ifdef DEBUG_LDA
    HF_PRINT("bias: %f\n", bias_);
    w_.display_vector("w");
    HFVector<float64_t>::display_vector(w_pos, num_feat, "w_pos");
    HFVector<float64_t>::display_vector(w_neg, num_feat, "w_neg");
    HFVector<float64_t>::display_vector(mean_pos, num_feat, "mean_pos");
    HFVector<float64_t>::display_vector(mean_neg, num_feat, "mean_neg");
#endif
    
    HF_FREE(classidx_neg);
    HF_FREE(classidx_pos);
    HF_FREE(mean_neg);
    HF_FREE(mean_pos);
    HF_FREE(scatter);
    HF_FREE(inv_scatter);
    HF_FREE(buffer);
    
    return true;
}



#endif  /* HAVE_LAPACK */