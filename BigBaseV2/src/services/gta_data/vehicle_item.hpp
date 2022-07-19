#pragma once
#include "file_manager/file.hpp"

namespace big
{
	class vehicle_item {
	public:
		vehicle_item();
		vehicle_item(nlohmann::json& item_json);

		std::string name;
		std::string display_name;
		std::string display_manufacturer;
		std::string clazz;
		Hash hash;
	};
}
