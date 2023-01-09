#include "backend/looped/looped.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class invisibility : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			ENTITY::SET_ENTITY_VISIBLE(self::ped, false, 0);
			if (g.self.local_visibility)
				NETWORK::SET_ENTITY_LOCALLY_VISIBLE(self::ped);
		}

		virtual void on_disable() override
		{
			ENTITY::SET_ENTITY_VISIBLE(self::ped, true, 0);
		}
	};

	invisibility g_invisibility("invis", "Invisiblity", "Makes you invisible", g.self.invisibility);
	bool_command g_local_visibility("localvis", "Visible Locally", "Makes you visible to yourself, other players will still not be able to see you", g.self.local_visibility);
}
