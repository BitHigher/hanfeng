/* 
 * File:   Features.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 下午1:32
 */

#ifndef FEATURES_FEATURES_H
#define FEATURES_FEATURES_H

#include "../base/HFObject.h"
#include "../base/common.h"
#include "../structure/SubsetStack.h"

namespace hanfeng
{

enum EFeatureProperty
{
    FP_NONE = 0,
    FP_DOT = 1,
    FP_STREAMING_DOT = 2
};

enum EFeatureClass
{
    C_UNKNOWN = 0,
    C_DENSE = 10,
    C_SPARSE = 20,
    C_STRING = 30
};
    
enum EFeatureType
{
    F_UNKNOWN = 0,
    F_BOOL = 5,
    F_CHAR = 10,
    F_BYTE = 20,
    F_DREAL = 100
};

class CFeatures : public CHFObject {
public:
    CFeatures();
    CFeatures(const CFeatures& orig);
    virtual ~CFeatures();
    
    inline bool has_property(EFeatureProperty p) const
    {
        return properties_ & p != 0;
    }
    
    virtual int32_t get_num_vectors() const = 0;
    
    virtual EFeatureClass get_feature_class() const = 0;
    virtual EFeatureType get_feature_type() const = 0;
private:
    
    uint64_t properties_;

protected:
    CSubsetStack *subset_stack_;
};

}
#endif	/* FEATURES_FEATURES_H */

