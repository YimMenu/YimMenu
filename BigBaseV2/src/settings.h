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
			"demo bool": false,
			"demo int": 1,
			"demo double": 1.0,
			"demo combo": 0,
			"demo bitset": 62678480396171113
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
