#pragma once
#include "file_manager/file.hpp"

namespace big
{
	class ped_item {
	public:
		ped_item();
		ped_item(nlohmann::json& item_json);

		std::string name;
		std::string ped_type;
		Hash hash;
	};
}
