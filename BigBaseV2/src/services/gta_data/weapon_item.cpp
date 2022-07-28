#include "weapon_item.hpp"

namespace big
{
	weapon_item::weapon_item()
	{
		this->name = "";
		this->weapon_type = "";
		this->hash = 0;
	}
	weapon_item::weapon_item(nlohmann::json& item_json)
	{
		this->name = item_json["Name"];

		if (
			item_json.contains("TranslatedLabel") &&
			item_json["TranslatedLabel"].contains("English") &&
			!item_json["TranslatedLabel"]["English"].is_null()
		) {
			this->name = item_json["TranslatedLabel"]["English"];
		}

		if (item_json["Category"].is_null())
		{
			this->weapon_type = "NULL";
		}
		else
		{
			this->weapon_type = item_json["Category"];
		}

		this->hash = item_json["Hash"];
	}
}
