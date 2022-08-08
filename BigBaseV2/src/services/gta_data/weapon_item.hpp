#pragma once
#include ""

namespace big::gta_data_service
{
	class weapon_item {
    public:
        const Hash hash;
        const int type_idx;
		const char* name;
		const bool throwable;
		const Hash reward_hash;
		const Hash reward_ammo_hash;

        weapon_item(const Hash hash, const int type_idx, const char* name, const bool throwable, const Hash reward_hash, const Hash reward_ammo_hash) : 
            hash(hash),
            type_idx(type_idx),
            name(name),
            throwable(throwable),
            reward_hash(reward_hash),
            reward_ammo_hash(reward_ammo_hash)
        { }

		~weapon_item() { }

        const char* get_type()
        {
            return gta_data_service::m_weapon_type_arr[type_idx];
        }
	};
}
