/* 
 * File:   Machine.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 上午1:33
 */

#ifndef MACHINE_MACHINE_H
#define MACHINE_MACHINE_H

#include "../base/HFObject.h"
#include "../base/common.h"
#include "../io/HFIO.h"

#include "../labels/Labels.h"
#include "../labels/BinaryLabels.h"
#include "../labels/RegressionLabels.h"
#include "../labels/MultiClassLabels.h"
#include "../labels/StructuredLabels.h"
#include "../labels/LatentLabels.h"

#include "../features/Features.h"

namespace hanfeng
{
    
class CMath;

enum EMachineType
{
    CT_NONE = 0,
    CT_LIGHT = 10,
    CT_PERCEPTRON = 80,
    CT_LDA = 100,
    CT_LIBLINEAR = 230,
    CT_KEAMS = 240
};

enum ESolverType
{
    ST_AUTO = 0,
    ST_CPLEX = 1,
    ST_GLPK = 2,
    ST_NEWTON = 3,
    ST_DIRECT = 4,
    ST_ELASTICNET = 5,
    ST_BLOCK_NORM = 6
};

enum EProblemType
{
    PT_BINARY = 0,
    PT_REGRESSION = 1,
    PT_MULTICLASS = 2,
    PT_STRUCTURED = 3,
    PT_LATENT = 4
};

#define MACHINE_PROBLEM_TYPE(PT) \
        virtual EProblemType get_machine_problem_type() const {return PT;}

class CMachine : public CHFObject {
public:
    CMachine();
    virtual ~CMachine();
    
    virtual bool train(CFeatures *data = NULL);
    
    virtual float64_t apply_one(int32_t vec_idx)
    {
        // TODO HF_NOTIMPLEMENTED
        return 0.0;
    }
    virtual CLabels* apply(CFeatures *data = NULL);
    virtual CBinaryLabels* apply_binary(CFeatures *data = NULL);
    virtual CRegressionLabels* apply_regression(CFeatures *data = NULL);
    virtual CMultiClassLabels* apply_multiclass(CFeatures *data = NULL);
    virtual CStructuredLabels* apply_structured(CFeatures *data = NULL);
    virtual CLatentLabels* apply_latent(CFeatures *data = NULL);
    
    
    virtual void set_labels(CLabels *labels);
    virtual CLabels* get_labels();
    
    virtual const char* get_name() const {return "Machine"; }
    
    
    inline void set_max_train_time(float64_t t)
    {
        max_train_time_ = t;
    }
    
    float64_t get_max_train_time(){return max_train_time_;}
    
    void set_solver_type(ESolverType st)
    {
        solver_type_ = st;
    }
    
    ESolverType get_solver_type(){return solver_type_;}
    
    inline bool is_data_locked() const { return data_locked_;}
    
    virtual CMachine* clone()
    {
        // TODO HF_NOTIMPLEMENTED
        return NULL;
    }
    
    virtual void set_store_model_features(bool store_model);
    
protected:
    virtual bool train_machine(CFeatures *data = NULL)
    {
        HF_ERROR("train_machine is not yet implemented for %s", get_name());
        return false;
    }

    virtual void store_model_features()
    {
        // NOT IMPELMENTED
    }

    virtual EProblemType get_machine_problem_type()
    {
        // TODO
        // HF_NOTIMPLEMENTED
        return PT_BINARY;
    }
    
    virtual bool is_label_valid(CLabels *lab) const {return true;}
    virtual bool train_require_labels() {return true;}
    
protected:
    float64_t max_train_time_;
    CLabels *labels_;
    ESolverType solver_type_;
    
    bool store_model_features_;
    bool data_locked_;
    
};


}
#endif	/* MACHINE_MACHINE_H */

