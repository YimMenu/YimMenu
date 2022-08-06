#pragma once
#include "file_manager/file.hpp"

namespace big
{
	class weapon_item {
	public:
		weapon_item();
		weapon_item(nlohmann::json& item_json);

		std::string name;
		bool throwable;
		std::string weapon_type;

		Hash hash;
		Hash reward_hash;
		Hash reward_ammo_hash;
	};
}
