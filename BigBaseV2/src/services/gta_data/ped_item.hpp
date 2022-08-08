#pragma once
#include "ped_data.hpp"

namespace big::gta_data_service
{
	class ped_item {
    public:
        const Hash hash;
        const int type_idx;
		const char* name;

        ped_item(const Hash hash, const int type_idx, const char* name);
        ~ped_item();

        const char* get_type() const;
	};
}
