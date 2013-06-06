/* 
 * File:   KNN.h
 * Author: zhf
 *
 * Created on 2013年6月5日, 下午1:57
 */

#ifndef KNN_H
#define KNN_H

#include "../machine/DistanceMachine.h"

namespace hanfeng
{

class CKNN : public CDistanceMachine
{

public:
    MACHINE_PROBLEM_TYPE(PT_MULTICLASS);
    
    CKNN();
    CKNN(int32_t k, CDistance *d, CLabels *trainlabs);
    virtual ~CKNN();
    
    virtual const char* get_name() const {return "KNN";}
    virtual EMachineType get_classifier_type(){return CT_KNN;}
    
protected:
    bool train_machine(CFeatures *data = NULL);
    
private:
    void init();
    
protected:
    int32_t k_;
    float64_t q_;
    
    bool use_cover_tree_;
    
    int32_t num_classes_;
    int32_t min_labels_;
    HFVector<int32_t> train_labels_;
};

}

#endif	/* KNN_H */

