#include "backend/looped/looped.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class carinvisibility : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			ENTITY::SET_ENTITY_VISIBLE(self::veh, false, 0);
			if (g.self.local_visibility)
				NETWORK::SET_ENTITY_LOCALLY_VISIBLE(self::veh);
		}

		virtual void on_disable() override
		{
			ENTITY::SET_ENTITY_VISIBLE(self::veh, true, 0);
		}
	};

	carinvisibility g_carinvisibility("inviscar", "Car Invisiblity", "Makes your car invisible", g.vehicle.carinvisibility);
	bool_command g_localcar_visibility("localinviscar", "Visible Locally", "Makes your car visible to yourself, other players will still not be able to see it", g.vehicle.localcar_visibility);
}
