#include "backend/looped_command.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"
#include "util/mobile.hpp"

namespace big
{

	class blackhole : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			for (auto entity : entity::get_entities(g.world.blackhole.include_vehicles, g.world.blackhole.include_peds))
			{
				if (entity::take_control_of(entity, 0))
				{
					auto entity_coord = ENTITY::GET_ENTITY_COORDS(entity, false);
					ENTITY::APPLY_FORCE_TO_ENTITY(entity,
					    1,
					    ((g.world.blackhole.pos.x - entity_coord.x) * 9.f),
					    ((g.world.blackhole.pos.y - entity_coord.y) * 9.f),
					    ((g.world.blackhole.pos.z - entity_coord.z) * 9.f),
					    0.f,
					    0.f,
					    0.f,
					    0,
					    false,
					    true,
					    true,
					    0,
					    0);
				}
			}

			//draw blackhole
			GRAPHICS::DRAW_MARKER(28,
			    g.world.blackhole.pos.x,
			    g.world.blackhole.pos.y,
			    g.world.blackhole.pos.z,
			    0.f,
			    0.f,
			    0.f,
			    0,
			    0,
			    0,
			    15.f,
			    15.f,
			    15.f,
			    g.world.blackhole.color[0] * 255,
			    g.world.blackhole.color[1] * 255,
			    g.world.blackhole.color[2] * 255,
			    g.world.blackhole.alpha,
			    0,
			    0,
			    0,
			    0,
			    0,
			    0,
			    0);
		}
	};

	blackhole g_blackhole("blackhole", "Blackhole", "Spawns a black hole that picks up all the peds and vehicles in your area.",
	    g.world.blackhole.enable);
	bool_command g_blackhole_peds("blackholeincpeds", "Peds", "Includes all nearby peds in the blackholes path of destruction",
	    g.world.blackhole.include_peds);
	bool_command g_blackhole_vehicles("blackholeincvehs", "Vehicles", "Includes all nearby vehicles in the blackholes path of destruction",
	    g.world.blackhole.include_vehicles);
}