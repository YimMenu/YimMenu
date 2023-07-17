#include "backend/looped_command.hpp"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/blip.hpp"
#include "util/entity.hpp"
#include "util/vehicle.hpp"


namespace big
{
	class navigationvoice : looped_command
	{
		//bool needsNextDirection = true;
		using looped_command::looped_command;

		virtual void on_enable() override
		{
			g_notification_service->push_success("Voice Navigation", "Voice Navigation has been enabled");
		}

		virtual void on_tick() override
		{
			if (g.self.nav_voice)
			{
				if (g_player_service->get_self()->get_current_vehicle() != nullptr)
					g_fiber_pool->queue_job([] {
						int direction;
						Vector3 waypoint;
						float dist;
						blip::get_blip_location(waypoint, (int)BlipIcons::Waypoint);
						bool doesPointExist = blip::get_blip_location(waypoint, (int)BlipIcons::Waypoint);
						float v;
						PATHFIND::GENERATE_DIRECTIONS_TO_COORD(waypoint.x, waypoint.y, waypoint.z, 1, &direction, &v, &dist);

						auto plyr = g_player_service->get_self();
						if (doesPointExist)
							LOG(INFO) << std::format("{}                                              {}", direction, dist);

						if (plyr->get_current_vehicle() != nullptr)
						{
						}
					});
			}
		}

		virtual void on_disable() override
		{
			g_notification_service->push_success("Voice Navigation", "Voice Navigation has been disabled");
		}
	};
	navigationvoice
	    g_navigation_voice("navigationvoice", "Navigation Voice", "Provides Vocal Navigational Assistance", g.self.nav_voice);
}
