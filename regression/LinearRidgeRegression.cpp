/* 
 * File:   LinearRidgeRegression.cpp
 * Author: zhf
 * 
 * Created on 2013年6月5日, 上午1:24
 */

#include "../lib/config.h"

#ifdef HAVE_LAPACK

#include "LinearRidgeRegression.h"
#include "../math/lapack.h"

using namespace hanfeng;

CLinearRidgeRegression::CLinearRidgeRegression()
{
    init();
}

CLinearRidgeRegression::CLinearRidgeRegression(float64_t tau, 
                CDenseFeatures<float64_t>* data, CLabels* lab)
{
    init();
    
    tau_ = tau;
    set_labels(lab);
    set_features(data);
}

CLinearRidgeRegression::~CLinearRidgeRegression()
{
}

void CLinearRidgeRegression::init()
{
    tau_ = 1e-6;
    HF_ADD(&tau_, "tau", "Regularization Parameter", MS_AVAILABLE);
}

bool CLinearRidgeRegression::train_machine(CFeatures *data)
{
    ASSERT(labels_);
    if(!data)
        data = features_;
    ASSERT(data);
    ASSERT(labels_->get_num_labels() == data->get_num_vectors());
    ASSERT(data->get_feature_class() == C_DENSE);
    ASSERT(data->get_feature_type() == F_DREAL);
    
    CDenseFeatures<float64_t> *feats = (CDenseFeatures<float64_t>*)data;
    int32_t num_feat = feats->get_num_features();
    int32_t num_vec = feats->get_num_vectors();
    
    // get kernel matrix
    HFMatrix<float64_t> kernel_matrix(num_feat, num_feat);
    HFVector<float64_t> y(num_feat);
    
    // init
    kernel_matrix.zero();
    y.zero();
    
    for(index_t i = 0; i < num_feat; ++i)
        kernel_matrix.matrix[i*num_feat+i] += tau_;
    
    for(index_t i = 0; i < num_vec; ++i)
    {
        HFVector<float64_t> v = feats->get_feature_vecotr(i);
        ASSERT(v.vlen == num_feat);
        
        cblas_dger(CblasColMajor, num_feat, num_feat, 1.0, v.vector, 1,
                        v.vector, 1, kernel_matrix.matrix, num_feat);
        
        cblas_daxpy(num_feat, ((CRegressionLabels*)labels_)->get_label(i),
                        v.vector, 1, y.vector, 1);
        
        feats->free_feature_vector(v, i);
    }
    
    clapack_dposv(CblasRowMajor, CblasUpper, num_feat, 1, kernel_matrix.matrix,
                        num_feat, y.vector, num_feat);
    
    set_w(y);
    
    return true;
}

bool CLinearRidgeRegression::load(CFile* loader)
{
    HF_SET_LOCALE_C;
    HF_RESET_LOCALE;
    return false;
}

bool CLinearRidgeRegression::save(CFile* saver)
{
    HF_SET_LOCALE_C;
    HF_RESET_LOCALE;
    return false;
}


#endif  /* HAVE_LAPACK */