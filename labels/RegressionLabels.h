/* 
 * File:   RegressionLabels.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 上午11:07
 */

#ifndef REGRESSIONLABELS_H
#define REGRESSIONLABELS_H

#include "DenseLabels.h"

namespace hanfeng
{
    
class CRegressionLabels : public CDenseLabels
{
public:
    CRegressionLabels();
    CRegressionLabels(int32_t num_labels);
    CRegressionLabels(HFVector<float64_t> src);
    CRegressionLabels(CFile *loader);
    
    virtual ~CRegressionLabels();
    
    virtual const char* get_name() { return "RegressionLabels"; }
    
    virtual ELabelType get_label_type() { return LT_REGRESSION;}
    
    static CRegressionLabels* obtain_from_generic(CLabels *base_labels);

};

}
#endif	/* REGRESSIONLABELS_H */

