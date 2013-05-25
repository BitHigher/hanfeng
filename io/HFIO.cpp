/* 
 * File:   HFIO.cpp
 * Author: zhf
 * 
 * Created on 2013年5月25日, 上午2:07
 */

#include "HFIO.h"
#include <stdarg.h>
#include <string.h>
#include "../lib/HFException.h"

using namespace hanfeng;

const EMessageType HFIO::levels[NUM_LOG_LEVELS] = {
    MSG_GCDEBUG, MSG_DEBUG, MSG_INFO,
    MSG_NOTICE, MSG_WARNING, MSG_ERROR,
    MSG_CRITICAL, MSG_EMERGENCY, MSG_MESSAGEONLY
};

const char *HFIO::message_strings[NUM_LOG_LEVELS] = {
    "[GCDEBUG] \0", "[DEBUG] \0", "[INFO] \0",
    "[NOTICE] \0", "[WARNING] \0", "[ERROR] \0",
    "[CRITICAL] \0", "[EMERGENCY] \0", "\0"
};

const char *HFIO::message_strings_highlight[NUM_LOG_LEVELS] = {
    "[GCDEBUG] \0", "[DEBUG] \0", "[INFO] \0",
    "[NOTICE] \0", "\033[1;34m[WARNING]\033[0m \0", 
    "\033[1;31m[ERROR]\033[0m \0",
    "\033[1;31m[CRITICAL]\033[0m \0",
    "\033[1;31m[EMERGENCY]\033[0m \0", "\0"
};

HFIO::HFIO()
:target(stdout), syntax_highlight(true),
 show_file_and_line(true), loglevel(MSG_WARNING)
{
}

HFIO::HFIO(const HFIO &orig) 
{
}

HFIO::~HFIO() 
{
}

void HFIO::set_loglevel(EMessageType level)
{
    loglevel = level;
}

EMessageType HFIO::get_loglevel() const
{
    return loglevel;
}

const char* HFIO::get_msg_intro(EMessageType prio) const
{
    for(int32_t i = NUM_LOG_LEVELS-1; i >= 0; --i)
    {
        if(levels[i] < loglevel && prio <= MSG_WARNING)
            return NULL;
        
        if(levels[i] == prio)
        {
            if(syntax_highlight)
                return message_strings_highlight[i];
            else
                return message_strings[i];
        }
    }
}

void HFIO::message(EMessageType prio, const char* file, int32_t line, 
                        const char* fmt, ...) const
{
    const char *msg_intro = get_msg_intro(prio);
    if(msg_intro)
    {
        char str[4096];
        snprintf(str, sizeof(str), "%s", msg_intro);
        int len = strlen(str);
        char *s = str+len;
        
        if(show_file_and_line)
        {
            snprintf(s, sizeof(str)-len, "In file %s line %d: ", file, line);
            len = strlen(str);
            s = str + len;
        }
        
        va_list list;
        va_start(list, fmt);
        vsnprintf(s, sizeof(str)-len, fmt, list);
        va_end(list);
        
        switch(prio)
        {
            case MSG_GCDEBUG:
            case MSG_DEBUG:
            case MSG_INFO:
            case MSG_NOTICE:
            case MSG_MESSAGEONLY:
                if(hf_print_message)
                    hf_print_message(target, str);
                break;
                
            case MSG_WARNING:
                if(hf_print_warning)
                    hf_print_warning(target, str);
                break;
                
            case MSG_ERROR:
            case MSG_CRITICAL:
            case MSG_ALERT:
            case MSG_EMERGENCY:
                if(hf_print_error)
                    hf_print_error(target, str);
                throw HFException(str);
                break;
                
            default:
                break;
        }
        
        fflush(target);
    }
}

void HFIO::set_target(FILE *target)
{
    this->target = target;
}
