/* 
 * File:   LogLoss.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 下午5:04
 */

#ifndef LOSS_LOGLOSS_H
#define LOSS_LOGLOSS_H

#include "LossFunction.h"

namespace hanfeng
{

class CLogLoss : public CLossFunction {
public:
    CLogLoss(): CLossFunction() {};
    virtual ~CLogLoss() {};
    
    float64_t loss(float64_t z);
    virtual float64_t first_derivative(float64_t z);
    virtual float64_t second_derivative(float64_t z);
    virtual float64_t get_update(float64_t prediction, float64_t label,
                                float64_t eta_t, float64_t norm);
    virtual float64_t get_square_grad(float64_t prediction, float64_t label);
    inline ELossType get_loss_type(){ return LT_LOGLOSS; }
    inline const char* get_name() const {return "LogLoss";}
private:

};

}

#endif	/* LOSS_LOGLOSS_H */

