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
    CBinaryLabels(const CBinaryLabels& orig);
    virtual ~CBinaryLabels();
private:

};

}
#endif	/* BINARYLABELS_H */

