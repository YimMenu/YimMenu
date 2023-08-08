#include "backend/looped/looped.hpp"
#include "services/outfit/outfit_service.hpp"
#include "natives.hpp"
#include "file_manager.hpp"
#include "logger/logger.hpp"

namespace big
{
	void looped::self_persist_outfit()
	{
		if (g.self.persist_outfit.empty())
			return; //Off

		if (g_local_player == nullptr || PED::IS_PED_DEAD_OR_DYING(self::ped, TRUE) || STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() || DLC::GET_IS_LOADING_SCREEN_ACTIVE())
			return; //Dead or Loading

		if (PED::GET_PED_DRAWABLE_VARIATION(self::ped, 5) == 0 && PED::GET_PED_DRAWABLE_VARIATION(self::ped, 4) >= 14 && PED::GET_PED_DRAWABLE_VARIATION(self::ped, 4) <= 18)
			return; //Showering

		if (g.self.persist_outfits_mis && NETWORK::NETWORK_IS_ACTIVITY_SESSION())
			return; //Missioning it up

		static nlohmann::json outfit{};
		static std::string persisting_outfit = "";

		if (persisting_outfit != g.self.persist_outfit)
		{
			persisting_outfit        = g.self.persist_outfit;
			folder saved_outfit_path = g_file_manager.get_project_folder("saved_outfits");
			std::ifstream i(saved_outfit_path.get_file(persisting_outfit).get_path());
			outfit.clear();
			i >> outfit;
		}

		outfit_service::apply_outfit(outfit, false);
	}
}