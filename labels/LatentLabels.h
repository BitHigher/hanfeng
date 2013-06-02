/* 
 * File:   LatentLabels.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 上午11:23
 */

#ifndef LATENTLABELS_H
#define LATENTLABELS_H

#include "Labels.h"

namespace hanfeng
{

class CLatentLabels : public CLabels{
public:
    CLatentLabels();
    CLatentLabels(const CLatentLabels& orig);
    virtual ~CLatentLabels();
private:

};


}
#endif	/* LATENTLABELS_H */

