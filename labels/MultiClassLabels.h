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
    CMultiClassLabels(const CMultiClassLabels& orig);
    virtual ~CMultiClassLabels();
private:

};

}
#endif	/* MULTICLASSLABELS_H */

