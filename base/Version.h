/* 
 * File:   Version.h
 * Author: zhf
 *
 * Created on 2013年6月4日, 下午6:31
 */

#ifndef BASE_VERSION_H
#define BASE_VERSION_H

#include "common.h"

namespace hanfeng
{

class Version {
public:
    Version();
    Version(const Version& orig);
    virtual ~Version();
    
    inline int32_t refcount() const
    {
        return refcount_;
    }
    
    inline int32_t ref()
    {
        return ++refcount_;
    }
    
    inline int32_t unref()
    {
        if(refcount_ == 0 || --refcount_ == 0)
        {
            delete this;
            return 0;
        }else
            return refcount_;
    }
    
private:
    int32_t refcount_;
};

}

#endif	/* BASE_VERSION_H */

