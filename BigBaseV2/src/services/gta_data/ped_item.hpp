#pragma once
#include ""

namespace big::gta_data_service
{
	class ped_item {
    public:
        const Hash hash;
        const int type_idx;
		const char* name;

        ped_item(const Hash hash, const int type_idx, const char* name) : 
            hash(hash),
            type_idx(type_idx),
            name(name)
        { }

		~ped_item() { }

        const char* get_type()
        {
            return gta_data_service::m_ped_type_arr[type_idx];
        }
	};
}
