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
    
    
    void distances_lhs(float64_t *result, int32_t idx_a1,
                                int32_t idx_a2, int32_t idx_b);
    void distances_rhs(float64_t *result, int32_t idx_b1, 
                                int32_t idx_b2, int32_t idx_a);
    
protected:
    static void* run_distance_thread_lhs(void *p);
    static void* run_distance_thread_rhs(void *p);
    
private:
    void init();
    
protected:
    CDistance *distance_;
};

}

#endif	/* MACHINE_DISTANCEMACHINE_H */

