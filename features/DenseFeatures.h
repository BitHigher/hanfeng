/* 
 * File:   DenseFeatures.h
 * Author: zhf
 *
 * Created on 2013年6月3日, 上午12:26
 */

#ifndef DENSEFEATURES_H
#define DENSEFEATURES_H

#include "DotFeatures.h"

namespace hanfeng
{

template<class T> class CDenseFeatures : public CDotFeatures{
public:
    CDenseFeatures();
    CDenseFeatures(const CDenseFeatures& orig);
    virtual ~CDenseFeatures();

    virtual EFeatureType get_feature_type() const;
    virtual EFeatureClass get_feature_class() const {return C_DENSE;}
};

}
#endif	/* DENSEFEATURES_H */

