/* 
 * File:   LPM.h
 * Author: zhf
 *
 * Created on 2013年6月3日, 上午10:26
 */

#ifndef CLASSIFIER_LPM_H
#define CLASSIFIER_LPM_H

#include "../lib/config.h"

#ifdef USE_CPLEX

namespace hanfeng
{

class CLPM {
public:
    CLPM();
    CLPM(const CLPM& orig);
    virtual ~CLPM();
private:

};

}


#endif  /* USE_CPLEX */
#endif	/* CLASSIFIER_LPM_H */

