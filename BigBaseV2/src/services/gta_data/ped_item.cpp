#include "ped_item.hpp"

namespace big
{
	ped_item::ped_item()
	{
		this->name = "";
		this->ped_type = "";
		this->hash = 0;
	}
	ped_item::ped_item(nlohmann::json& item_json)
	{
		this->name = item_json["Name"];

		this->ped_type = item_json["Pedtype"];
		std::transform(this->ped_type.begin(), this->ped_type.end(), this->ped_type.begin(), ::toupper);

		this->hash = item_json["Hash"];
	}
}
