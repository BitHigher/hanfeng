/* 
 * File:   Features.h
 * Author: zhf
 *
 * Created on 2013年6月2日, 下午1:32
 */

#ifndef FEATURES_FEATURES_H
#define FEATURES_FEATURES_H

#include "../base/HFObject.h"
#include "../base/common.h"
#include "../structure/SubsetStack.h"
#include "../io/File.h"
#include "../preprocessor/Preprocessor.h"
#include "FeatureType.h"

namespace hanfeng
{
    
class CPreprocessor;


class CFeatures : public CHFObject {
public:
    CFeatures(int32_t size = 0);
    CFeatures(const CFeatures& orig);
    CFeatures(CFile *loader);
    virtual ~CFeatures();
    
    virtual CFeatures* duplicate() = 0;
    virtual EFeatureClass get_feature_class() const = 0;
    virtual EFeatureType get_feature_type() const = 0;
    virtual int32_t get_num_vectors() const = 0;
    virtual int32_t get_size() const = 0;
    
    
    void set_preprocessed(int32_t num);
    bool is_preprocessed() const;
    int32_t get_num_preprocessed() const;
    int32_t get_num_preprocessors() const;
    
    virtual void load(CFile *loader);
    virtual void save(CFile *saver);
    
    inline bool has_property(EFeatureProperty p) const
    {
        return properties_ & p != 0;
    }
    
    inline void set_property(EFeatureProperty p)
    {
        properties_ |= p;
    }
    
    inline void unset_property(EFeatureProperty p)
    {
        properties_ &= ~p; 
    }
    
    virtual void add_subset(HFVector<index_t> subset);
    virtual void remove_subset();
    virtual void remove_all_subsets();
    
private:
    void init();
    
private:
    uint64_t properties_;
    int32_t cache_size_;
    int32_t num_preproc_;
    
    CPreprocessor **preproc_;
    bool *preprocessed_;
    
protected:
    CSubsetStack *subset_stack_;
};

}
#endif	/* FEATURES_FEATURES_H */

