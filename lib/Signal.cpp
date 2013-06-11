/* 
 * File:   Signal.cpp
 * Author: zhf
 * 
 * Created on 2013年6月11日, 下午3:03
 */

#include "Signal.h"

#ifndef WIN32

#include <signal.h>
#include <string.h>

using namespace hanfeng;

int32_t CSignal::signals_[NUMTRAPPEDSIGS] = {SIGINT, SIGURG};
struct sigaction CSignal::oldsigactions_[NUMTRAPPEDSIGS];
bool CSignal::active_ = false;
bool CSignal::cancel_computation_ = false;
bool CSignal::cancel_immediately_ = false;

CSignal::CSignal()
{
}

CSignal::~CSignal()
{
    if(unset_handler())
        HF_PRINT("error uninitializing signal handler\n");
}

void CSignal::handler(int signal)
{
    if(signal == SIGINT)
    {
        HF_SPRINT("\nImmediately return to prompt/ "
                   "Permaturely finish computations/ "
                   "Do nothing(I/P/D)?");
        
        char answer = fgetc(stdin);
        if(answer == 'I' || answer == 'i')
        {
            unset_handler();
            set_cancel(true);
            
            // TODO why directly use hf_print_error
            if(hf_print_error)
                hf_print_error(stdout, "hf stopped by sigint");
        }
        else if(answer == 'P' || answer == 'p')
        {
            set_cancel();
        }
        else
            HF_SPRINT("Continuing...\n");
    }
    else if(signal == SIGURG)
    {
        set_cancel();
    }
    else
        HF_SPRINT("unknown signal %d received\n", signal);
}

void CSignal::clear_cancel()
{
    cancel_computation_ = false;
    cancel_immediately_ = false;
}

void CSignal::set_cancel(bool immediately)
{
    cancel_computation_ = true;
    
    // FIXME is this bug?
    if(immediately)
        cancel_immediately_ = true;
}

void CSignal::clear()
{
    clear_cancel();
    active_ = false;
    memset(&CSignal::oldsigactions_, 0, sizeof(CSignal::oldsigactions_));
}

bool CSignal::unset_handler()
{
    if(active_)
    {
        bool result = true;
        for(index_t i = 0; i < NUMTRAPPEDSIGS; ++i)
        {
            if(sigaction(signals_[i], &oldsigactions_[i], NULL))
            {
                HF_SPRINT("error unintializing signal handler "
                          "for signal %d\n", signals_[i]);
                result = false;
            }
        }
        
        if(result)
            clear();
        
        return result;
    }
    else
        return false;
}

#endif /* WIN32 */