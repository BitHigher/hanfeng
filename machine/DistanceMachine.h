/* 
 * File:   DistanceMachine.h
 * Author: zhf
 *
 * Created on 2013年6月4日, 下午8:38
 */

#ifndef MACHINE_DISTANCEMACHINE_H
#define MACHINE_DISTANCEMACHINE_H

#include "Machine.h"
#include "../distance/Distance.h"

namespace hanfeng
{

class CDistanceMachine : public CMachine{
public:
    CDistanceMachine();
    virtual ~CDistanceMachine();
    
    void set_distance(CDistance *d);
    CDistance* get_distance() const;
    
protected:
    
    
private:
    void init();
    
protected:
    CDistance *distance_;
};

}

#endif	/* MACHINE_DISTANCEMACHINE_H */

