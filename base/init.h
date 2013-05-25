/* 
 * File:   init.h
 * Author: zhf
 *
 * Created on 2013年5月25日, 上午11:40
 */

#ifndef BASE_INIT_H
#define BASE_INIT_H

#include "common.h"

namespace hanfeng
{   
    class HFIO;
    
    extern void (*hf_print_message)(FILE *target, const char *str);
    extern void (*hf_print_warning)(FILE *target, const char *str);
    extern void (*hf_print_error)(FILE *target, const char *str);

    void init_hanfeng(
                void (*print_message)(FILE *target, const char *str) = NULL,
                void (*print_warning)(FILE *target, const char *str) = NULL,
                void (*print_error)(FILE *target, const char *str) = NULL,
                void (*cancel_computations)(bool &delayed, bool &immediately) = NULL);
    
    void exit_hanfeng();
}


#endif	/* BASE_INIT_H */

