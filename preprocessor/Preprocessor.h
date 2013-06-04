/* 
 * File:   Preprocessor.h
 * Author: zhf
 *
 * Created on 2013年6月4日, 下午5:14
 */

#ifndef PREPROCESSOR_PREPROCESSOR_H
#define PREPROCESSOR_PREPROCESSOR_H

#include "../base/HFObject.h"
#include "../features/Features.h"
#include "../features/FeatureType.h"

namespace hanfeng
{
    
class CFeatures;
    
enum EPreprocessorType
{
    P_UNKNOWN = 0,
    P_NORMONE = 10,
    P_LOGPLUSONE = 20,
    P_PNORM = 190
};

class CPreprocessor : public CHFObject
{
public:
    CPreprocessor() : CHFObject(){};
    virtual ~CPreprocessor(){};
    
    virtual bool init(CFeatures *features) = 0;
    virtual void cleanup() = 0;
    virtual EFeatureType get_feature_type() = 0;
    virtual EFeatureClass get_feature_class() = 0;
    virtual EPreprocessorType get_type() = 0;
    
    virtual const char* get_name() const {return "Preprocessor";}

};

}
#endif	/* PREPROCESSOR_PREPROCESSOR_H */

