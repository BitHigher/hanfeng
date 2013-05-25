/* 
 * File:   HFException.h
 * Author: zhf
 *
 * Created on 2013年5月25日, 下午3:28
 */

#ifndef LIB_HFEXCEPTION_H
#define LIB_HFEXCEPTION_H

#include "../base/common.h"

namespace hanfeng
{

class HFException {
public:
    HFException(const char *str);
    HFException(const HFException& orig);
    virtual ~HFException();
    
    
    
private:
    void init(const char *str);
    char *val;
};

}
#endif	/* LIB_HFEXCEPTION_H */

