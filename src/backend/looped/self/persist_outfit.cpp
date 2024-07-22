#include "backend/looped/looped.hpp"
#include "core/scr_globals.hpp"
#include "file_manager.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "services/outfit/outfit_service.hpp"
#include "services/tunables/tunables_service.hpp"

namespace big
{
	inline bool is_taking_shower(Hash model)
	{
		int offset = 0;
		switch (model)
		{
			case "mp_m_freemode_01"_J: [[likely]] break;
			case "mp_f_freemode_01"_J: [[likely]]
			{
				offset = 1;
				break;
			}
			default:[[unlikely]] return false; //For non-normal models
		}

		return PED::GET_PED_DRAWABLE_VARIATION(self::ped, ComponentId::AUXILIARY) == 15 && PED::GET_PED_DRAWABLE_VARIATION(self::ped, ComponentId::TORSO) == 15 && PED::GET_PED_DRAWABLE_VARIATION(self::ped, ComponentId::LEGS) == (14 + offset);
	}

	void looped::self_persist_outfit()
	{
		//Disable clothing validation
		*scr_globals::reset_clothing.as<PBOOL>() = FALSE;
		if (auto tunable = g_tunables_service->get_tunable<PBOOL>("DISABLE_CLOTHING_SAVE_SLOT_VALIDATION"_J)) [[likely]]
			*tunable = TRUE;

		if (g.self.persist_outfit.empty())
			return; //Off

		if (g_local_player == nullptr || PED::IS_PED_DEAD_OR_DYING(self::ped, TRUE) || STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() || DLC::GET_IS_LOADING_SCREEN_ACTIVE()) [[unlikely]]
			return; //Dead or Loading

		auto model = ENTITY::GET_ENTITY_MODEL(self::ped);
		if (is_taking_shower(model)) [[unlikely]]
			return; //Showering

		if (g.self.persist_outfits_mis && NETWORK::NETWORK_IS_ACTIVITY_SESSION())
			return; //Missioning it up

		static nlohmann::json outfit{};
		static std::string persisting_outfit = "";

		if (persisting_outfit != g.self.persist_outfit)
		{
			persisting_outfit                   = g.self.persist_outfit;
			folder saved_outfit_path            = g_file_manager.get_project_folder("saved_outfits");
			const auto persist_outfit_file_path = saved_outfit_path.get_file(persisting_outfit).get_path();
			if (std::filesystem::exists(persist_outfit_file_path)) [[likely]]
			{
				std::ifstream i(persist_outfit_file_path);
				if (i.is_open()) [[likely]]
				{
					outfit.clear();
					try
					{
						i >> outfit;
					}
					catch (const std::exception& e)
					{
						LOG(INFO) << e.what();

						outfit                = {};
						g.self.persist_outfit = "";
					}
				}
			}
		}

		if (outfit.contains("model") && outfit["model"].get<uint32_t>() == model)
			outfit_service::apply_outfit(outfit, false);
	}
}
