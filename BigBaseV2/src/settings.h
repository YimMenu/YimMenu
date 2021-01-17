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
			"custom_gun": {
				"gravity_velocity_multiplier": 3.0,
				"type": 0,
				"vehicle_spawn_model": "bus"
			},
			"disable_phone": false,
			"disable_chat_censoring": false,
			"god_mode": false,
			"join_message": false,
			"never_wanted": false,
			"noclip": {
				"enabled": false,
				"horizontal": 5.0,
				"vertical": 1.0
			},
			"no_bike_fall": false,
			"no_idle_kick": false,
			"off_radar": false,
			"ragdoll": false,
			"rank": 6969,
			"speedo_type": 0,
			"spoof_rank": false,
			"sticky_tyres": false,
			"super_sprint": false,
			"settings": {
				"protections": {
					"attach": false,
					"cage": false,
					"version_mismatch": false
				},
				"script_protections": {
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
				},
				"logging": {
					"get_event_data": false,
					"script_events": false
				}
			},
			"world": {
				"population": {
					"enabled": false,
					"pedestrians": 1.0,
					"parked": 1.0,
					"vehicles": 1.0
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
