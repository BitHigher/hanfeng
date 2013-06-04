/* 
 * File:   KMeans.h
 * Author: zhf
 *
 * Created on 2013年6月4日, 下午8:53
 */

#ifndef KMEANS_H
#define KMEANS_H

#include "../machine/DistanceMachine.h"
#include "../structure/HFMatrix.h"

namespace hanfeng
{

class CKMeans : public CDistanceMachine 
{
public:
    MACHINE_PROBLEM_TYPE(PT_MULTICLASS);
    
    CKMeans();
    CKMeans(int32_t k, CDistance *d);
    virtual ~CKMeans();
    
    virtual EMachineType get_classifier_type(){return CT_KEAMS;}
    virtual const char* get_name() const { return "KMeans";}
    
    inline int32_t get_dimensions() { return dimensions_;}
    inline int32_t get_k(){ return k_;}
    inline int32_t get_max_iter() { return max_iter_;}
    inline HFVector<float64_t> get_radiuses() { return R_;}
    HFMatrix<float64_t> get_cluster_centers();
    
    void set_k(int32_t k);
    void set_max_iter(int32_t max_iter);
    
    virtual void load(CFile *loader);
    virtual void save(CFile *saver);
private:
    void init();
    
protected:
    void clustknb(bool use_old_mus, float64_t *mus_start);
    
    virtual bool train_machine(CFeatures *data = NULL);
    
    virtual void store_model_features();
    virtual bool train_require_labels() const {return false;}
    
protected:
    int32_t max_iter_;
    int32_t k_;
    int32_t dimensions_;
    
    HFVector<float64_t> R_;
    
private:
    HFVector<float64_t> weights_;
    HFMatrix<float64_t> mus_;
};

}
#endif	/* KMEANS_H */

