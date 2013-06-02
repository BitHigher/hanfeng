/* 
 * File:   LossFunction.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 下午4:52
 */

#ifndef LOSS_LOSSFUNCTION_H
#define LOSS_LOSSFUNCTION_H

#include "../base/HFObject.h"
#include "../base/common.h"

#include <math.h>

namespace hanfeng
{

enum ELossType
{
    LT_HINGELOSS = 0,
    LT_SMOOTHHINGELOSS = 10,
    LT_SQUAREDHINGELOSS = 20,
    LT_LOGLOSS = 100
};
    
class CLossFunction : public CHFObject {
public:
    CLossFunction(): CHFObject() {}
    virtual ~CLossFunction(){}
    
    inline const char* get_name() const {return "LossFunction";}

    virtual float64_t loss(float64_t prediction, float64_t label)
    {
        return loss(prediction * label);
    }
    
    virtual float64_t loss(float64_t z) = 0;
    
    virtual float64_t first_derivative(float64_t prediction, float64_t label)
    {
        return loss(prediction * label);
    }
    
    virtual float64_t first_derivative(float64_t z) = 0;
    
    virtual float64_t second_derivative(float64_t prediction, float64_t label)
    {
        return loss(prediction * label);
    }
    
    virtual float64_t second_derivative(float64_t z) = 0;
    
    virtual float64_t get_update(float64_t prediction, float64_t label,
                                float64_t eta_t, float64_t norm) = 0;

    virtual float64_t get_square_grad(float64_t prediction, float64_t label)=0;

    virtual ELossType get_loss_type() = 0;
};

}
#endif	/* LOSS_LOSSFUNCTION_H */

