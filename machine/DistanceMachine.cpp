/* 
 * File:   DistanceMachine.cpp
 * Author: zhf
 * 
 * Created on 2013年6月4日, 下午8:38
 */

#include "DistanceMachine.h"

using namespace hanfeng;

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