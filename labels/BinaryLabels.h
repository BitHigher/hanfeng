/* 
 * File:   BinaryLabels.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 上午11:04
 */

#ifndef BINARYLABELS_H
#define BINARYLABELS_H

#include "DenseLabels.h"

namespace hanfeng
{

class CBinaryLabels : public CDenseLabels{
public:
    CBinaryLabels();
    CBinaryLabels(int32_t num_labels);
    CBinaryLabels(HFVector<float64_t> src, float64_t threshold=0.0);
    CBinaryLabels(CFile *loader);
    
    virtual ~CBinaryLabels();
    
    virtual const char* get_name() const { return "BinaryLabels"; }
    virtual ELabelType get_label_type() {return LT_BINARY;}
    
    virtual void ensure_valid(const char *context = NULL);
    
    void scores_to_probabilities();
private:

};

}
#endif	/* BINARYLABELS_H */

