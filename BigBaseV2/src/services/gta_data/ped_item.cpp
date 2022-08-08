#pragma once
#include "ped_data.hpp"

namespace big::gta_data_service
{
    ped_item::ped_item(const Hash hash, const int type_idx, const char* name) :
        hash(hash),
        type_idx(type_idx),
        name(name)
    { }

    ped_item::~ped_item() { }

    const char* ped_item::get_type() const
    {
        if (type_idx <= -1)
        {
            return "";
        }

        return ped_type_arr[type_idx];
    }
}
