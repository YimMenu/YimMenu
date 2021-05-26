#pragma once
#include "data/player_struct.hpp"
#include "enums.hpp"

#ifndef GLOBALS_H
#define GLOBALS_H

using namespace big;
struct globals {
	nlohmann::json default_options;
	nlohmann::json options;

	struct player {
		bool spectating = false;
	};

	struct self {
		bool godmode = false;
		bool off_radar = false;
		bool noclip = false;
		bool no_ragdoll = false;
	};

	struct vehicle {
		bool horn_boost = false;
		SpeedoMeter speedo_meter = SpeedoMeter::DISABLED;
	};

	struct weapons {
		CustomWeapon custom_weapon = CustomWeapon::NONE;
		char vehicle_gun_model[12] = "bus";
	};

	struct window {
		bool main = true;
		bool log = false;
		bool users = false;
		bool player = false;

		int x;
		int y;
	};

	CPlayer players[32];
	CPlayer selected_player;

	player player{};
	self self{};
	vehicle vehicle{};
	weapons weapons{};
	window window{};

	void from_json(const nlohmann::json& j)
	{
		this->self.godmode = j["self"]["godmode"];
		this->self.off_radar = j["self"]["off_radar"];
		this->self.no_ragdoll = j["self"]["no_ragdoll"];

		this->vehicle.horn_boost = j["vehicle"]["horn_boost"];
		this->vehicle.speedo_meter = (SpeedoMeter)j["vehicle"]["speedo_meter"];

		this->weapons.custom_weapon = (CustomWeapon)j["weapons"]["custom_weapon"];

		this->window.log = j["window"]["log"];
		this->window.main = j["window"]["main"];
	}

	nlohmann::json to_json()
	{
		return nlohmann::json{
			{
				"self", {
					{ "godmode", this->self.godmode },
					{ "off_radar", this->self.off_radar },
					{ "no_ragdoll", this->self.no_ragdoll }
				}
			},
			{
				"vehicle", {
					{ "horn_boost", this->vehicle.horn_boost },
					{ "speedo_meter", (int)this->vehicle.speedo_meter }
				}
			},
			{
				"weapons", {
					{ "custom_weapon", (int)this->weapons.custom_weapon }
				}
			},
			{
				"window", {
					{ "log", this->window.log },
					{ "main", this->window.main }
				}
			}
		};
	}

	void attempt_save()
	{
		nlohmann::json& j = this->to_json();
		if (j != this->options)
		{
			this->save();

			this->options = j;
		}
	}

	bool load()
	{
		this->default_options = this->to_json();

		std::string settings_file = std::getenv("appdata");
		settings_file += "\\BigBaseV2\\settings.json";

		std::ifstream file(settings_file);

		if (!file.is_open())
		{
			this->write_default_config();

			file.open(settings_file);
		}

		file >> this->options;

		bool should_save = false;
		for (auto& e : this->default_options.items())
		{
			if (this->options.count(e.key()) == 0)
			{
				should_save = true;
				this->options[e.key()] = e.value();
			}
		}

		this->from_json(this->options);

		if (should_save)
		{
			LOG(INFO) << "Updating settings.";
			save();
		}

		return true;
	}

private:
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
