/* 
 * File:   LogLoss.cpp
 * Author: zhf
 * 
 * Created on 2013年6月2日, 下午5:04
 */

#include "LogLoss.h"

using namespace hanfeng;

float64_t CLogLoss::loss(float64_t z)
{
    return (z>=0)?log(1+exp(-z)) : -z + log(1+exp(z));
}

float64_t CLogLoss::first_derivative(float64_t z)
{
    /* both postive and negative have the same derivative */
    return -1/(1+exp(z));
}

float64_t CLogLoss::second_derivative(float64_t z)
{
    float64_t ez = exp(z);
    return ez/(ez*(ez+2)+1);
}

float64_t CLogLoss::get_update(float64_t prediction, float64_t label, 
                                float64_t eta_t, float64_t norm)
{
    
    
    // TODO
}

float64_t CLogLoss::get_square_grad(float64_t prediction, float64_t label)
{
    float64_t d = CLossFunction::first_derivative(prediction, label);
    return d*d;
}