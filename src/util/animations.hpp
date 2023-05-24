#pragma once

#include "file_manager.hpp"
#include "file_manager/file.hpp"
#include "notify.hpp"
#include "thread_pool.hpp"

namespace big::animations
{

	inline static std::multimap<std::string, std::string> all_anims;
	inline static std::vector<std::string> all_dicts;

	/*
    Built with https://raw.githubusercontent.com/DurtyFree/gta-v-data-dumps/master/animDictsCompact.json in mind
    */
	void populate_anim_list(nlohmann::json j)
	{
		for (const auto& animdict : j)
		{
			std::string dict = animdict["DictionaryName"];

			auto it = std::find(all_dicts.begin(), all_dicts.end(), dict);

			if (it == all_dicts.end())
				all_dicts.push_back(dict);

			for (const auto& anim : animdict["Animations"])
			{
				all_anims.emplace(dict, anim);
			}
		}
	}

	inline bool has_anim_list_been_populated()
	{
		return all_anims.size() > 0;
	}

	inline int anim_dict_count()
	{
		return all_dicts.size();
	}

	inline int total_anim_count()
	{
		return all_anims.size();
	}

	inline void fetch_all_anims()
	{
		if (has_anim_list_been_populated())
			LOG(WARNING) << "Anim list already contained data, overwriting...";

		all_anims.clear();
		all_dicts.clear();

		if (!std::filesystem::exists(g_file_manager->get_project_file("animDictsCompact.json").get_path()))
		{
			LOG(INFO) << "Animations file is not in directory. https://raw.githubusercontent.com/DurtyFree/gta-v-data-dumps/master/animDictsCompact.json";
			g_notification_service->push_warning("Animations", "Please download the appropriate animations json and put it in the mod directory.");
            return;
		}

		auto path = g_file_manager->get_project_file("animDictsCompact.json").get_path();

		try
		{
			g_thread_pool->push([=] {
				std::ifstream file(path);

				if (!file.is_open())
					return;

				nlohmann::json j;

				file >> j;
				populate_anim_list(j);
			});

			if (has_anim_list_been_populated())
				LOG(INFO) << "Succesfully fetched " << anim_dict_count() << " dictionaries with a total of " << total_anim_count() << " animations.";
		}
		catch (std::exception e)
		{
			LOG(WARNING) << "Failed fetching all anims: " << e.what();
		}
	}
}