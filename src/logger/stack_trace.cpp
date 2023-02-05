#include "stack_trace.hpp"
#include <DbgHelp.h>

namespace big
{
    stack_trace::stack_trace(EXCEPTION_POINTERS *exception_info)
    {
        SymInitialize(GetCurrentProcess(), nullptr, true);

        
    }

    stack_trace::~stack_trace()
    {
        SymCleanup(GetCurrentProcess());
    }
}