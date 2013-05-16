/* 
 * File:   HFReferenceData.h
 * Author: zhf
 *
 * Created on 2013年5月16日, 上午11:51
 */

#ifndef STRUCTURE_HFREFERENCEDATA_H
#define	STRUCTURE_HFREFERENCEDATA_H

#include <cstdlib>

namespace hanfeng{

struct refcount_t{
    int32_t rc;
};
    
class HFReferenceData {
public:
    HFReferenceData(bool ref_counting=true);
    HFReferenceData(const HFReferenceData& orig);
    virtual ~HFReferenceData();

    HFReferenceData& operator= (const HFReferenceData& orig);
    
    int32_t ref_count();
protected:
    void copy_refcount(const HFReferenceData& orig);
    
    // increase reference
    int32_t ref();
    
    // decrease reference
    int32_t unref();
    
    /** virtual function **/
    virtual void copy_data(const HFReferenceData& orig) = 0;
    virtual void init_data() = 0;
    virtual void free_data() = 0;
    
private:
    refcount_t *refcount_;
};


}
#endif	/* STRUCTURE_HFREFERENCEDATA_H */

