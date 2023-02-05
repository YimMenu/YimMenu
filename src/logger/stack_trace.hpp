#pragma once
#include "common.hpp"

namespace big
{
    class stack_trace
    {
    public:
        stack_trace(EXCEPTION_POINTERS* exception_info);
        virtual ~stack_trace();

    private:
        std::stringstream m_dump;

    };
}