/* 
 * File:   DenseLabels.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 上午11:52
 */

#ifndef DENSELABELS_H
#define DENSELABELS_H

#include "Labels.h"
#include "../io/File.h"

namespace hanfeng
{

class CDenseLabels : public CLabels{
public:
    CDenseLabels();
    CDenseLabels(int32_t num_labels);
    CDenseLabels(CFile *loader);
    virtual ~CDenseLabels();
    
    virtual void ensure_valid(const char *context = NULL);
    virtual void load(CFile *loader);
    virtual void save(CFile *saver);
    
    bool set_label(index_t index, float64_t label);
    bool set_int_label(index_t index, int32_t label);
    float64_t get_label(index_t index);
    int32_t get_int_label(index_t index);
    
    
    void set_labels(HFVector<float64_t> v);
    HFVector<float64_t> get_labels();
    HFVector<float64_t> get_labels_copy();
    
    void set_int_labels(HFVector<int32_t> v);
    HFVector<int32_t> get_int_labels();
    
    
    void set_to_one();
    void zero();
    void set_to_const(float64_t c);
    
    virtual int32_t get_num_labels();
    
    
private:
    void init();
    
protected:
    HFVector<float64_t> labels_;
};

}

#endif	/* DENSELABELS_H */

