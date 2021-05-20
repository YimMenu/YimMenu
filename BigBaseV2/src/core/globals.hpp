#pragma once
#include "enums.hpp"

#ifndef GLOBALS_H
#define GLOBALS_H

using namespace big;
struct globals {
	struct self {
		bool godmode = false;
		bool noclip = false;
	};

	struct vehicle {
		SpeedoMeter speedo_meter = SpeedoMeter::DISABLED;
	};

	struct weapons {
		CustomWeapon custom_weapon = CustomWeapon::NONE;
	};

	self self{};
	vehicle vehicle{};
	weapons weapons{};

	void from_json(const nlohmann::json& j)
	{
		this->self.godmode = j["self"]["godmode"];

		this->vehicle.speedo_meter = (SpeedoMeter)j["vehicle"]["speedo_meter"];

		this->weapons.custom_weapon = (CustomWeapon)j["weapons"]["custom_weapon"];
	}

	nlohmann::json to_json()
	{
		return nlohmann::json{
			{
				"self", {
					{
						"godmode", this->self.godmode
					}
				}
			},
			{
				"vehicle", {
					{
						"speedo_meter", (int)this->vehicle.speedo_meter
					}
				}
			},
			{
				"weapons", {
					{
						"custom_weapon", (int)this->weapons.custom_weapon
					}
				}
			}
		};
	}

	bool load()
	{
		std::string settings_file = std::getenv("appdata");
		settings_file += "\\BigBaseV2\\settings.json";

		std::ifstream file(settings_file);

		if (!file.is_open())
		{
			this->write_default_config();

			file.open(settings_file);
		}

		nlohmann::json j;
		file >> j;

		nlohmann::json default_j = this->to_json();

		bool should_save = false;
		for (auto& e : default_j.items())
		{
			if (j.count(e.key()) == 0)
			{
				should_save = true;
				j[e.key()] = e.value();
			}
		}

		if (should_save)
		{
			LOG(INFO) << "Updating settings.";

			default_j.merge_patch(j);
			j = default_j;

			save();
		}
		this->from_json(j);

		return true;
	}

	bool save()
	{
		std::string settings_file = std::getenv("appdata");
		settings_file += "\\BigBaseV2\\settings.json";

		std::ofstream file(settings_file, std::ios::out | std::ios::trunc);
		file << this->to_json().dump(4);
		file.close();

		return true;
	}

	bool write_default_config()
	{
		std::string settings_file = std::getenv("appdata");
		settings_file += "\\BigBaseV2\\settings.json";

		std::ofstream file(settings_file, std::ios::out);
		file << this->to_json().dump(4);
		file.close();

		return true;
	}
};

inline struct globals g;
#endif // !GLOBALS_H
