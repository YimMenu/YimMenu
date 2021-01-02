#pragma once
#include "common.hpp"
#include "gta/player.hpp"

namespace big
{
	class settings
	{
	public:
		explicit settings() = default;
		~settings() = default;

		nlohmann::json options;
		nlohmann::json default_options =
		R"({
			"disable_phone": false,
			"disable_chat_censoring": false,
			"god_mode": false,
			"join_message": false,
			"never_wanted": false,
			"no_bike_fall": false,
			"no_idle_kick": false,
			"off_radar": false,
			"parked_vehicle_density": 1.0,
			"pedestrian_population": 1.0,
			"population_modifiers": false,
			"ragdoll": false,
			"rank": 6969,
			"reveal_players": false,
			"speedo_type": 0,
			"spoof_rank": false,
			"sticky_tyres": false,
			"super_sprint": false,
			"vehicle_density": 1.0,
			"settings": {
				"protections": {
					"bounty": false,
					"ceo_ban": false,
					"ceo_kick": false,
					"ceo_money": false,
					"clear_wanted_level": false,
					"fake_deposit": false,
					"force_mission": false,
					"gta_banner": false,
					"kick": false,
					"personal_vehicle_destroyed": false,
					"remote_off_radar": false,
					"rotate_cam": false,
					"send_to_cutscene": false,
					"send_to_island": false,
					"sound_spam": false,
					"spectate": false,
					"force_teleport": false,
					"transaction_error": false,
					"vehicle_kick": false
				}
			}
		})"_json;

		bool save()
		{
			std::string settings_file = std::getenv("appdata");
			settings_file += "\\BigBaseV2\\settings.json";

			std::ofstream file(settings_file, std::ios::out | std::ios::trunc);
			file << options.dump(4);
			file.close();
			return true;
		}

		bool load()
		{
			std::string settings_file = std::getenv("appdata");
			settings_file += "\\BigBaseV2\\settings.json";

			std::ifstream file(settings_file);

			if (!file.is_open())
			{
				write_default_config();
				file.open(settings_file);
			}

			file >> options;

			bool should_save = false;
			for (auto& e : default_options.items())
			{
				if (options.count(e.key()) == 0)
				{
					should_save = true;
					options[e.key()] = e.value();
				}
					
			}

			if (should_save)
			{
				LOG(INFO) << "Updating settings.";
				save();
			}

			return true;
		}

	private:
		bool write_default_config()
		{
			std::string settings_file = std::getenv("appdata");
			settings_file += "\\BigBaseV2\\settings.json";

			std::ofstream file(settings_file, std::ios::out);
			file << default_options.dump(4);
			file.close();

			options.clear();
			options = default_options;

			return true;
		}
	};

	inline settings g_settings;
}
