/* 
 * File:   LinearRidgeRegression.h
 * Author: zhf
 *
 * Created on 2013年6月5日, 上午1:24
 */

#ifndef LINEARRIDGEREGRESSION_H
#define LINEARRIDGEREGRESSION_H

#include "../lib/config.h"

#ifdef HAVE_LAPACK

#include "../machine/LinearMachine.h"
#include "../features/DenseFeatures.h"

namespace hanfeng
{

class CLinearRidgeRegression : public CLinearMachine{
public:
    MACHINE_PROBLEM_TYPE(PT_REGRESSION);
    
    CLinearRidgeRegression();
    CLinearRidgeRegression(float64_t tau, CDenseFeatures<float64_t> *data,
                                        CLabels *lab);
    virtual ~CLinearRidgeRegression();
    
    virtual const char* get_name() const {return "LinearRidgeRegression";}
    
    inline void set_tau(float64_t tau) { tau_ = tau;}
    
    virtual EMachineType get_classifier_type()
    {
        return CT_LINEARRIDGEREGRESSION;
    }
    
protected:
    virtual bool train_machine(CFeatures *data = NULL);
    
private:
    void init();
    
protected:
    float64_t tau_;
    
};

}

#endif  /* HAVE_LAPACK */
#endif	/* LINEARRIDGEREGRESSION_H */

