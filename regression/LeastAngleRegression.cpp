/* 
 * File:   LeastAngleRegression.cpp
 * Author: zhf
 * 
 * Created on 2013年6月11日, 上午1:49
 */

#include "LeastAngleRegression.h"

using namespace hanfeng;

CLeastAngleRegression::CLeastAngleRegression(bool lasso)
: lasso_(lasso), max_non_zero_(0), max_l1_norm_(0)
{
    HF_ADD(&max_non_zero_, "max_non_zero", 
                "Max number of non-zero variables", MS_AVAILABLE);
    
    HF_ADD(&max_l1_norm_, "max_l1_norm",
                "Max l1-norm of estimator", MS_AVAILABLE);
}

CLeastAngleRegression::~CLeastAngleRegression()
{
}

bool CLeastAngleRegression::train_machine(CFeatures *data)
{
    // TODO train_machine
}

