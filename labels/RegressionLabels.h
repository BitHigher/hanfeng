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
    
class CRegressionLabels : public CDenseLabels{
public:
    CRegressionLabels();
    CRegressionLabels(const CRegressionLabels& orig);
    virtual ~CRegressionLabels();
private:

};

}
#endif	/* REGRESSIONLABELS_H */

