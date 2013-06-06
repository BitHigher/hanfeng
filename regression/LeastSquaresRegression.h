/* 
 * File:   LeastSquaresRegression.h
 * Author: zhf
 *
 * Created on 2013年6月5日, 上午11:42
 */

#ifndef LEASTSQUARESREGRESSION_H
#define LEASTSQUARESREGRESSION_H

#include "../lib/config.h"

#ifdef HAVE_LAPACK

#include "LinearRidgeRegression.h"

namespace hanfeng
{

class CLeastSquaresRegression : public CLinearRidgeRegression
{
public:
    MACHINE_PROBLEM_TYPE(PT_REGRESSION);
    
    CLeastSquaresRegression();
    CLeastSquaresRegression(CDenseFeatures<float64_t> *data, CLabels *lab);
    virtual ~CLeastSquaresRegression();
    
    virtual const char* get_name() const {return "LeastSquaresRegression";}
    virtual EMachineType get_classifier_type()
    {
        return CT_LEASTSQUARESREGRESSION;
    }
    
private:
    void init();

};

}


#endif  /* HAVE_LAPACK */
#endif	/* LEASTSQUARESREGRESSION_H */

