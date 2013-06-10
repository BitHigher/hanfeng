/* 
 * File:   LeastAngleRegression.h
 * Author: zhf
 *
 * Created on 2013年6月11日, 上午1:49
 */

#ifndef LEASTANGLEREGRESSION_H
#define LEASTANGLEREGRESSION_H

#include "../machine/LinearMachine.h"

namespace hanfeng
{

class CLeastAngleRegression : public CLinearMachine
{
public:
    MACHINE_PROBLEM_TYPE(PT_REGRESSION);
    
    CLeastAngleRegression(bool lasso=true);
    virtual ~CLeastAngleRegression();
    
    virtual const char* get_name() const { return "LeastAngleRegression"; }
    virtual EMachineType get_classifier_type() {return CT_LARS; }
    
    inline void set_max_non_zero(int32_t n)
    {
        max_non_zero_ = n;
    }
    
    inline int32_t get_max_non_zero() const
    {
        return max_non_zero_;
    }
    
    inline void set_max_l1_norm(float64_t norm)
    {
        max_l1_norm_ = norm;
    }
    
    inline float64_t get_max_l1_norm() const
    {
        return max_l1_norm_;
    }
    
    void switch_w(int32_t num_variable)
    {
        // TODO switch_w
    }
    
protected:
    virtual bool train_machine(CFeatures *data=NULL);
    
private:
    bool lasso_;
    int32_t max_non_zero_;
    float64_t max_l1_norm_;
    int32_t num_active_;

};

}
#endif	/* LEASTANGLEREGRESSION_H */

