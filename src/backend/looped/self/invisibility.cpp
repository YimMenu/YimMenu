#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "core/scr_globals.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "services/script_patcher/script_patcher_service.hpp"

#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	class invisibility : looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override
		{
			g_script_patcher_service->update();
		}

		virtual void on_tick() override
		{
			ENTITY::SET_ENTITY_VISIBLE(self::ped, false, 0);

			if (g.self.local_visibility)
				NETWORK::SET_ENTITY_LOCALLY_VISIBLE(self::ped);

			scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].IsInvisible = true;
		}

		virtual void on_disable() override
		{
			ENTITY::SET_ENTITY_VISIBLE(self::ped, true, 0);
			scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].IsInvisible = false;
			g_script_patcher_service->update();
		}
	};

	invisibility g_invisibility("invis", "Invisiblity", "Makes you invisible", g.self.invisibility);
	bool_command g_local_visibility("localvis", "Visible Locally", "Makes you visible to yourself, but other players would still not be able to see you",
	    g.self.local_visibility);
}
