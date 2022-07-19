#include "vehicle_item.hpp"

namespace big
{
	vehicle_item::vehicle_item()
	{
		this->name = "";
		this->display_name = "";
		this->display_manufacturer = "";
		this->clazz = "";
		this->hash = 0;
	}
	vehicle_item::vehicle_item(nlohmann::json& item_json)
	{
		this->name = item_json["Name"];
		this->display_name = item_json["Name"];
		this->display_manufacturer = "";
		this->clazz = "";
		this->hash = item_json["Hash"];

		if (!item_json["DisplayName"].is_null())
		{
			this->display_name = item_json["DisplayName"];
		}

		if (!item_json["ManufacturerDisplayName"].is_null())
		{
			this->display_manufacturer = item_json["ManufacturerDisplayName"];
		}
		else if (!item_json["Manufacturer"].is_null())
		{
			this->display_manufacturer = item_json["Manufacturer"];
		}
		
		if (!item_json["Class"].is_null())
		{
			this->clazz = item_json["Class"];
			std::transform(this->clazz.begin(), this->clazz.end(), this->clazz.begin(), ::toupper);

			if (this->clazz == "COMPACTS")
			{
				this->clazz = "COMPACT";
			}
		}
	}
}
