/* 
 * File:   Labels.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 上午11:03
 */

#ifndef LABELS_H
#define LABELS_H

#include "../base/common.h"
#include "../structure/HFVector.h"
#include "../structure/SubsetStack.h"
#include "../base/HFObject.h"

namespace hanfeng
{

enum ELabelType
{
    LT_BINARY = 0,
    LT_MULTICLASS = 1,
    LT_REGRESSION = 2,
    LT_STRUCTURED = 3,
    LT_LATENT = 4
};
    
class CLabels : public CHFObject {
public:
    CLabels();
    virtual ~CLabels();
    
    virtual void ensure_valid(const char *context = NULL) = 0;
    virtual int32_t get_num_labels() = 0;
    virtual ELabelType get_label_type() = 0;
    
    virtual void add_subset(HFVector<index_t> subset);
    virtual void remove_subset();
    virtual void remove_all_subsets();
    
    virtual void set_value(float64_t value, index_t index);
    virtual float64_t get_value(index_t index);
    virtual void set_values(HFVector<float64_t> values);
    virtual HFVector<float64_t> get_values();
    
private:
    void init();

protected:
    CSubsetStack *subset_stack_;
    HFVector<float64_t> current_values_;
};

}

#endif	/* LABELS_H */

