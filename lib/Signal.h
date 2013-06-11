/* 
 * File:   Signal.h
 * Author: zhf
 *
 * Created on 2013年6月11日, 下午3:03
 */

#ifndef LIB_SIGNAL_H
#define LIB_SIGNAL_H

#include "../base/HFObject.h"

#ifndef WIN32
#include <signal.h>
#define NUMTRAPPEDSIGS 2

namespace hanfeng
{

class CSignal : public CHFObject
{
public:
    CSignal();
    virtual ~CSignal();
    
    static void handler(int signal);
    static bool set_handler();
    static bool unset_handler();
    static void clear(); 
    static void clear_cancel();
    static void set_cancel(bool immediately=false);
    
    
    virtual const char* get_name() const { return "Signal"; }

    
protected:
    static int32_t signals_[NUMTRAPPEDSIGS];
    static struct sigaction oldsigactions_[NUMTRAPPEDSIGS];
    static bool active_;
    static bool cancel_computation_;
    static bool cancel_immediately_;
};

}

#endif  /* WIN32 */
#endif	/* LIB_SIGNAL_H */

