#pragma once

#include "file_manager.hpp"
#include "file_manager/file.hpp"
#include "notify.hpp"
#include "thread_pool.hpp"

namespace big::animations
{
	inline static std::multimap<std::string, std::string> all_anims;
	inline static std::vector<std::string> all_dicts;

	enum class anim_flags
	{
		LOOPING                          = 1 << 0, 
		HOLD_LAST_FRAME                  = 1 << 1, 
		REPOSITION_WHEN_FINISHED         = 1 << 2, 
		NOT_INTERRUPTABLE                = 1 << 3, 
		UPPERBODY                        = 1 << 4, 
		SECONDARY                        = 1 << 5, 
		REORIENT_WHEN_FINISHED           = 1 << 6,
		ABORT_ON_PED_MOVEMENT            = 1 << 7, 
		ADDITIVE                         = 1 << 8, 
		TURN_OFF_COLLISION               = 1 << 9, 
		OVERRIDE_PHYSICS                 = 1 << 10,
		IGNORE_GRAVITY                   = 1 << 11,
		EXTRACT_INITIAL_OFFSET           = 1 << 12,
		EXIT_AFTER_INTERRUPTED           = 1 << 13,
		TAG_SYNC_IN                      = 1 << 14,
		TAG_SYNC_OUT                     = 1 << 15,
		TAG_SYNC_CONTINUOUS              = 1 << 16,
		FORCE_START                      = 1 << 17,
		USE_KINEMATIC_PHYSICS            = 1 << 18,
		USE_MOVER_EXTRACTION             = 1 << 19,
		HIDE_WEAPON                      = 1 << 20,
		ENDS_IN_DEAD_POSE                = 1 << 21,
		ACTIVATE_RAGDOLL_ON_COLLISION    = 1 << 22,
		DONT_EXIT_ON_DEATH               = 1 << 23,
		ABORT_ON_WEAPON_DAMAGE           = 1 << 24,
		DISABLE_FORCED_PHYSICS_UPDATE    = 1 << 25,
		PROCESS_ATTACHMENTS_ON_START     = 1 << 26,
		EXPAND_PED_CAPSULE_FROM_SKELETON = 1 << 27,
		USE_ALTERNATIVE_FP_ANIM          = 1 << 28,
		BLENDOUT_WRT_LAST_FRAME          = 1 << 29,
		USE_FULL_BLENDING                = 1 << 30 
	};

	/*
    Built with https://raw.githubusercontent.com/DurtyFree/gta-v-data-dumps/master/animDictsCompact.json in mind
    */
	inline void populate_anim_list(nlohmann::json j)
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

		if (!std::filesystem::exists(g_file_manager.get_project_file("animDictsCompact.json").get_path()))
		{
			LOG(WARNING) << "Animations file is not in directory. https://raw.githubusercontent.com/DurtyFree/gta-v-data-dumps/master/animDictsCompact.json";
			g_notification_service.push_warning("Animations", "JSON_ANIMATIONS_WARNING"_T.data());
			return;
		}

		auto path = g_file_manager.get_project_file("animDictsCompact.json").get_path();

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
