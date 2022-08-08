#pragma once
#include "vehicle_data.hpp"

namespace big::gta_data_service
{
    vehicle_item::vehicle_item(const Hash hash, const int class_idx, const char* name, const int manufacturer_idx) :
        hash(hash),
        class_idx(class_idx),
        name(name),
        manufacturer_idx(manufacturer_idx)
    { }

    vehicle_item::~vehicle_item() { }

    const char* vehicle_item::get_class()
    {
        return vehicle_class_arr[class_idx];
    }

    const char* vehicle_item::get_manufacturer()
    {
        return vehicle_manufacturer_arr[manufacturer_idx];
    }
}
