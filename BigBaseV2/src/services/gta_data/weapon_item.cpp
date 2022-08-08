#pragma once
#include "weapon_data.hpp"

namespace big::gta_data_service
{
    weapon_item::weapon_item(const Hash hash, const int type_idx, const char* name, const bool throwable, const Hash reward_hash, const Hash reward_ammo_hash) :
        hash(hash),
        type_idx(type_idx),
        name(name),
        throwable(throwable),
        reward_hash(reward_hash),
        reward_ammo_hash(reward_ammo_hash)
    { }

    weapon_item::~weapon_item() { }

    const char* weapon_item::get_type()
    {
        if (type_idx <= -1)
        {
            return "";
        }

        return weapon_type_arr[type_idx];
    }
}
