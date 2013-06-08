/* 
 * File:   MultiClassLabels.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 上午11:06
 */

#ifndef MULTICLASSLABELS_H
#define MULTICLASSLABELS_H

#include "DenseLabels.h"

namespace hanfeng
{

class CMultiClassLabels : public CDenseLabels{
public:
    CMultiClassLabels();
    CMultiClassLabels(int32_t num_labels);
    CMultiClassLabels(HFVector<float64_t> src);
    CMultiClassLabels(CFile *loader);
    
    virtual ~CMultiClassLabels();
    
    virtual const char* get_name() const {return "MultiClassLabels"; }
    virtual ELabelType get_label_type() { return LT_MULTICLASS; }
    
    virtual void ensure_valid(const char *context = NULL);
    
    void allocate_confidences_for(int32_t n_classes);
    
    HFVector<float64_t> get_multiclass_confidences(int32_t i);
    void set_multiclass_confidences(int32_t i, HFVector<float64_t> confidences);
    
private:
    void init();
    
protected:
    HFMatrix<float64_t> multiclass_confidences_;
};

}
#endif	/* MULTICLASSLABELS_H */

