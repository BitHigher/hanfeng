#include "init.h"
#include "../io/HFIO.h"
#include "../base/Parallel.h"
#include "../base/Version.h"
#include "../math/Math.h"

namespace hanfeng
{
    HFIO *hf_io = NULL;
    Parallel *hf_parallel = NULL;
    Version *hf_version = NULL;
    CMath *hf_math = NULL;
    
    void (*hf_print_message)(FILE *target, const char *str) = NULL;
    void (*hf_print_warning)(FILE *target, const char *str) = NULL;
    void (*hf_print_error)(FILE *target, const char *str) = NULL;
    void (*hf_cancel_computations)(bool &delayed, bool &immediately) = NULL;

    void init_hanfeng(
                void (*print_message)(FILE *target, const char *str),
                void (*print_warning)(FILE *target, const char *str),
                void (*print_error)(FILE *target, const char *str),
                void (*cancel_computations)(bool &delayed, bool &immediately))
    {
        if(!hf_io)
            hf_io = new HFIO();
        if(!hf_parallel)
            hf_parallel = new Parallel();
        if(!hf_version)
            hf_version = new Version();
        if(!hf_math)
            hf_math = new CMath();
        
        hf_print_message = print_message;
        hf_print_warning = print_warning;
        hf_print_error = print_error;
        hf_cancel_computations = cancel_computations;
    }
    
    void exit_hanfeng()
    {
        hf_print_message = NULL;
        hf_print_warning = NULL;
        hf_print_error = NULL;
        hf_cancel_computations = NULL;
    }
    
    void hf_global_print_default(FILE *target, const char *str)
    {
        fprintf(target, "%s", str);
    }
    
    void init_hanfeng_with_defaults()
    {
        init_hanfeng(hf_global_print_default, hf_global_print_default,
                hf_global_print_default);
    }
}