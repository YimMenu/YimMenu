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

		std::vector<Entity> entity_list;
		std::chrono::steady_clock::time_point last_call_time;

		virtual void on_tick() override
		{
			auto current_time = std::chrono::steady_clock::now();
			auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_call_time).count();

			if (elapsed_time >= 1000) // Reduce black hole gather spam so it pulses only every second
			{
				entity_list = entity::get_entities(g.world.blackhole.include_vehicles, g.world.blackhole.include_peds);
				last_call_time = current_time;

				for (int i = 0; i < 30 && i < entity_list.size(); i++) // Only yeet up to 30 entities every second to prevent crashes
				{
					auto entity = entity_list[i];

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

	blackhole g_blackhole("blackhole", "GUI_TAB_BLACKHOLE", "BACKEND_LOOPED_WORLD_BLACKHOLE_DESC", g.world.blackhole.enable);
	bool_command
	    g_blackhole_peds("blackholeincpeds", "PEDS", "BACKEND_LOOPED_WORLD_BLACKHOLE_PEDS_DESC", g.world.blackhole.include_peds);
	bool_command g_blackhole_vehicles("blackholeincvehs", "VEHICLES", "BACKEND_LOOPED_WORLD_BLACKHOLE_VEHS_DESC",
	    g.world.blackhole.include_vehicles);
}