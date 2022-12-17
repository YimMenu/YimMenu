#include "wren_module.hpp"

namespace big
{
    wren_module::wren_module()
    {

    }

    wren_module::wren_module(WrenVM* vm, const std::string& module_name) :
        m_vm(vm),
        m_name(module_name)
    {

    }

    wren_module::~wren_module()
    {

    }
}
