/* 
 * File:   LDA.h
 * Author: zhf
 *
 * Created on 2013年6月3日, 上午12:16
 */

#ifndef CLASSIFIER_LDA_H
#define CLASSIFIER_LDA_H

#include "../lib/config.h"

#ifdef HAVE_LAPACK

#include "../machine/LinearMachine.h"
#include "../features/DenseFeatures.h"

namespace hanfeng
{

class CLDA : public CLinearMachine {
public:
    MACHINE_PROBLEM_TYPE(PT_BINARY);
    CLDA(float64_t gamma=0);
    CLDA(float64_t gamma, CDenseFeatures<float64_t> *traindat, 
         CLabels *trainlab);
    
    virtual ~CLDA();

    inline void set_gamma(float64_t gamma){ gamma_ = gamma;}
    inline float64_t get_gamma() { return gamma_;}
    
    virtual EMachineType get_classifier_type()
    {
        return CT_LDA;
    }
    
    virtual void set_features(CDotFeatures *feat)
    {
        if(feat->get_feature_class() != C_DENSE ||
            feat->get_feature_type() != F_DREAL)
            HF_ERROR("LDA requires SIMPLE REAL valued features");
                
        CLinearMachine::set_features(feat);
    }
    
    const char* get_name() const {return "LDA";}
    
protected:
    virtual bool train_machine(CFeatures *data=NULL);
    
protected:
    float64_t gamma_;

};

}

#endif  /* HAVE_LAPACK */
#endif	/* CLASSIFIER_LDA_H */

