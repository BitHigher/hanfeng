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

namespace hanfeng
{

enum EFeatureProperty{
    FP_NONE = 0,
    FP_DOT = 1,
    FP_STREAMING_DOT = 2
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
    
private:
    
    uint64_t properties_;

};

}
#endif	/* FEATURES_FEATURES_H */

