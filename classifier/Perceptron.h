/* 
 * File:   Perceptron.h
 * Author: zhf
 *
 * Created on 2013年6月4日, 上午12:43
 */

#ifndef CLASSIFIER_PERCEPTRON_H
#define CLASSIFIER_PERCEPTRON_H

#include "../machine/LinearMachine.h"
#include "../features/DotFeatures.h"

namespace hanfeng
{

class CPerceptron : public CLinearMachine{
public:
    MACHINE_PROBLEM_TYPE(PT_BINARY);
    
    CPerceptron();
    CPerceptron(CDotFeatures *traindat, CLabels *trainlab);
    virtual ~CPerceptron();
    
    virtual EMachineType get_classifier_type(){return CT_PERCEPTRON;}
    
    inline void set_learn_rate(float64_t r){learn_rate_ = r;}
    inline void set_max_iter(int32_t i){max_iter_ = i;}

    const char* get_name() const {return "Perceptron";}
    
protected:
    virtual bool train_machine(CFeatures *data = NULL);
    
protected:
    float64_t learn_rate_;
    int32_t max_iter_;
};

}

#endif	/* CLASSIFIER_PERCEPTRON_H */