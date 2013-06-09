/* 
 * File:   DistanceMachine.cpp
 * Author: zhf
 * 
 * Created on 2013年6月4日, 下午8:38
 */

#include "DistanceMachine.h"

using namespace hanfeng;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
struct D_THREAD_PARAM
{
    CDistance *d;
    float64_t *r;
    int32_t idx_r_start;
    int32_t idx_start;
    int32_t idx_stop;
    int32_t idx_comp;
};
#endif


CDistanceMachine::CDistanceMachine()
:CMachine()
{
    init();
}

CDistanceMachine::~CDistanceMachine()
{
    HF_UNREF(distance_);
}

void CDistanceMachine::init()
{
    set_store_model_features(true);
    distance_ = NULL;
    
    // TODO add parameters
}

void CDistanceMachine::set_distance(CDistance* d)
{
    HF_UNREF(distance_);
    distance_ = d;
    HF_REF(distance_);
}

CDistance* CDistanceMachine::get_distance() const
{
    HF_REF(distance_);
    return distance_;
}

void* CDistanceMachine::run_distance_thread_rhs(void *p)
{
    D_THREAD_PARAM *param = (D_THREAD_PARAM*)p;
    CDistance *distance = param->d;
    float64_t *res = param->r;
    
    int32_t idx_res_start = param->idx_r_start;
    int32_t idx_start = param->idx_start;
    int32_t idx_stop = param->idx_stop;
    int32_t idx_comp = param->idx_comp;
    
    for(index_t i = idx_res_start; idx_start < idx_stop; ++i, ++idx_start)
        res[i] = distance->distance(idx_comp, idx_start);
}

void CDistanceMachine::distances_rhs(float64_t* result, int32_t idx_b1, 
                                        int32_t idx_b2, int32_t idx_a)
{
    int32_t num_threads = parallel->get_num_threads();
    ASSERT(num_threads > 0);
    ASSERT(result);
    
    if(num_threads < 2)
    {
        D_THREAD_PARAM param;
        param.d = distance_;
        param.r = result;
        param.idx_r_start = idx_b1;
        param.idx_start = idx_b1;
        param.idx_stop = idx_b2+1;
        param.idx_comp = idx_a;
        
        run_distance_thread_rhs((void*)&param);
    }
}