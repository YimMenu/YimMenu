#include "invisibility.hpp"

#include "core/scr_globals.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "services/script_patcher/script_patcher_service.hpp"

#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	void invisibility::on_enable()
	{
		g_script_patcher_service->update();
	}

	void invisibility::on_tick()
	{
		ENTITY::SET_ENTITY_VISIBLE(self::ped, false, 0);

		if (g.self.local_visibility)
			NETWORK::SET_ENTITY_LOCALLY_VISIBLE(self::ped);

		scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].IsInvisible = true;
	}

	void invisibility::on_disable()
	{
		ENTITY::SET_ENTITY_VISIBLE(self::ped, true, 0);
		scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].IsInvisible = false;
		g_script_patcher_service->update();
	}
}
