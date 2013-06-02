/* 
 * File:   StructuredLabels.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 上午11:22
 */

#ifndef STRUCTUREDLABELS_H
#define STRUCTUREDLABELS_H

#include "Labels.h"

namespace hanfeng
{

class CStructuredLabels : public CLabels{
public:
    CStructuredLabels();
    CStructuredLabels(const CStructuredLabels& orig);
    virtual ~CStructuredLabels();
private:

};

}
#endif	/* STRUCTUREDLABELS_H */

