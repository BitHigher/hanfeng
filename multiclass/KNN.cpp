/* 
 * File:   KNN.cpp
 * Author: zhf
 * 
 * Created on 2013年6月5日, 下午1:57
 */

#include "KNN.h"

using namespace hanfeng;

CKNN::CKNN()
: CDistanceMachine()
{
    init();
}

CKNN::CKNN(int32_t k, CDistance* d, CLabels* trainlabs)
: CDistanceMachine()
{
    init();
    
    k_ = k;
    
    ASSERT(d);
    ASSERT(trainlabs);
    
    set_distance(d);
    set_labels(trainlabs);
    train_labels_.vlen = trainlabs->get_num_labels();
}

CKNN::~CKNN()
{
}

void CKNN::init()
{
    set_store_model_features(false);
    
    k_ = 3;
    q_ = 1.0;
    use_cover_tree_ = false;
    num_classes_ = 0;
    
    // TODO add parameters
}

bool CKNN::train_machine(CFeatures *data)
{
    ASSERT(distance_);
    ASSERT(labels_);
    
    if(data)
    {
        ASSERT(data->get_num_vectors() == labels_->get_num_labels());
        distance_->init(data, data);
        
    }
}
