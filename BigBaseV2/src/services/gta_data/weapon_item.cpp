#include "weapon_item.hpp"
#include "gta/joaat.hpp"

namespace big
{
	weapon_item::weapon_item()
	{
		this->name = "";
		this->throwable = false;
		this->weapon_type = "";

		this->hash = 0;
		this->reward_hash = 0;
		this->reward_ammo_hash = 0;
	}
	weapon_item::weapon_item(nlohmann::json& item_json)
	{
		this->name = item_json["Name"];
		this->throwable = false;
		this->weapon_type = "NULL";

		if (
			item_json.contains("TranslatedLabel") &&
			item_json["TranslatedLabel"].contains("English") &&
			!item_json["TranslatedLabel"]["English"].is_null()
		) {
			this->name = item_json["TranslatedLabel"]["English"];
		}

		if (!item_json["Category"].is_null())
		{
			this->weapon_type = item_json["Category"];
		}

		this->hash = item_json["Hash"];
		this->reward_hash = 0;
		this->reward_ammo_hash = 0;

		const std::string reward_prefix = "REWARD_";
		bool is_gun = false;
		bool is_recharge = false;

		if (item_json.contains("Flags"))
		{
			auto flags = item_json["Flags"];

			for (auto& flag : flags)
			{
				if (flag == "Gun")
				{
					is_gun = true;
				}
				else if (flag == "DisplayRechargeTimeHUD")
				{
					is_recharge = true;
				}
				else if (flag == "Thrown")
				{
					this->throwable = true;
				}
			}
		}

		if (this->weapon_type == "GROUP_MELEE" || this->weapon_type == "GROUP_UNARMED" || is_gun)
		{
			this->reward_hash = rage::joaat((reward_prefix + std::string(item_json["Name"])).c_str());

			if (is_gun && !is_recharge)
			{
				std::string weapon_id = std::string(item_json["Name"]).substr(7);
				this->reward_ammo_hash = rage::joaat((reward_prefix + "AMMO_" + weapon_id).c_str());
			}
		}
	}
}
