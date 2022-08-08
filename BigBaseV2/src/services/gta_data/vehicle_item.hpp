#pragma once
#include ""

namespace big::gta_data_service
{
	class vehicle_item {
    public:
        const Hash hash;
        const int class_idx;
		const char* name;
		const int manufacturer_idx;

        vehicle_item(const Hash hash, const int class_idx, const char* name, const int manufacturer_idx) : 
            hash(hash),
            class_idx(class_idx),
            name(name),
            manufacturer_idx(manufacturer_idx)
        { }

		~vehicle_item() { }

        const char* get_class()
        {
            return gta_data_service::m_vehicle_class_arr[class_idx];
        }

        const char* get_manufacturer()
        {
            return gta_data_service::m_vehicle_m_vehicle_manufacturer_arr_arr[manufacturer_idx];
        }
	};
}
