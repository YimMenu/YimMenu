#pragma once
#include "common.hpp"
#include "rage/joaat.hpp"

namespace big
{
    using hotkey_func = std::function<void()>;
    using key_t = unsigned int;

    struct hotkey
    {
        rage::joaat_t m_name_hash;
        key_t m_key;
        hotkey_func m_func;
    };
}