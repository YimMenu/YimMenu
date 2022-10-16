#include "wren_script.hpp"

namespace big
{
    wren_script::wren_script()
    {

    }

    wren_script::wren_script(WrenVM* vm, const std::string& module_name) :
        m_vm(vm),
        m_module_name(module_name)
    {

    }

    wren_script::~wren_script()
    {

    }
}
