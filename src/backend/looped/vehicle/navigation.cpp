#include "backend/looped_command.hpp"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "util/audio.hpp"
#include "util/blip.hpp"
#include "util/entity.hpp"
#include "util/math.hpp"
#include "util/notify.hpp"
#include "util/vehicle.hpp"


//70 feet annouce the next action plus what is coming up


namespace big
{
	class navigation : looped_command
	{
		//bool needsNextDirection = true;
		using looped_command::looped_command;

		virtual void on_enable() override
		{
			g_notification_service->push_success("Navigation", "Navigation has been enabled");
		}

		virtual void on_tick() override
		{
			g_fiber_pool->queue_job([] {
				int direction;
				int feetToAction;
				Vector3 waypoint;
				float dist;
				float v;

				blip::get_blip_location(waypoint, (int)BlipIcons::Waypoint);
				bool doesPointExist = blip::get_blip_location(waypoint, (int)BlipIcons::Waypoint);

				if (doesPointExist)
				{
					PATHFIND::GENERATE_DIRECTIONS_TO_COORD(waypoint.x, waypoint.y, waypoint.z, 1, &direction, &v, &dist);
					feetToAction = math::divided_by_ten(math::meters_to_feet(dist));
					switch (direction)
					{
					case 1:
						if (g.self.nav_text)
							notify::above_map("Route Recalculation");
						if (g.self.nav_voice)
						{
							audio::play_sound_nav("RouteRecalc", 0);
						}
						break;
					case 2:
						if (g.self.nav_text)
							notify::above_map("Continue on Route");
						if (g.self.nav_voice)
						{
							audio::play_sound_nav("HighlightedRoute", 0);
						}
						break;
					case 3:
						switch (feetToAction)
						{
						case 130:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 5280);
							}
							break;

						case 40:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 1000);
							}
							break;
						case 25:
							if (g.self.nav_text)
								notify::above_map(std::format("Keep Left in {} feet", 500));
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 500);
							}
							break;
						case 15:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 100);
							}
							break;
						case 10:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("KeepLeft", 0);
							}
							break;
						}
						break;
					case 4:
						switch (feetToAction)
						{
						case 130:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 5280);
							}
							break;
						case 40:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 1000);
							}
							break;
						case 25:
							if (g.self.nav_text)
								notify::above_map(std::format("Keep Right in {} feet", 500));
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FiveHundredFeet", 500);
							}
							break;
						case 15:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FiveHundredFeet", 100);
							}
							break;
						case 10:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("KeepRight", 0);
							}
							break;
						}
						break;
					case 5:
						switch (feetToAction)
						{
						case 130:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 5280);
							}
							break;
						case 40:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 1000);
							}
							break;
						case 25:
							if (g.self.nav_text)
								notify::above_map(std::format("Continue Straight in {} feet", 500));
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 500);
							}
							break;
						case 15:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 100);
							}
							break;
						case 10:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("Straight", 0);
							}
							break;
						}
						break;
					case 6:
						switch (feetToAction)
						{
						case 130: audio::play_sound_nav("FeetUntilAction", 5280); break;
						case 40: audio::play_sound_nav("FeetUntilAction", 1000); break;
						case 25:
							if (g.self.nav_text)
								notify::above_map(std::format("Turn Left in {} feet", 500));
							audio::play_sound_nav("FeetUntilAction", 500);
							break;
						case 15:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 100);
							}
							break;
						case 10:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("TurnLeft", 0);
							}
							break;
						}
						break;
					case 7:
						switch (feetToAction)
						{
						case 130:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 5280);
							}
							break;
						case 40:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 1000);
							}
							break;
						case 25:
							if (g.self.nav_text)
								notify::above_map(std::format("Turn Right in {} feet", 500));
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 500);
							}
							break;
						case 15:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("FeetUntilAction", 100);
							}
							break;
						case 10:
							if (g.self.nav_voice)
							{
								audio::play_sound_nav("TurnRight", 0);
							}
							break;
						}
						break;
					case 8:
						// confusing navmesh
						if (g.self.nav_voice)
						{
							audio::play_sound_nav("RouteRecalc", 0);
						}
						break;
					}
					script::get_current()->yield(1s);
				}
			});
		}

		virtual void on_disable() override
		{
			g_notification_service->push_success("Navigation", "Navigation has been disabled");
		}
	};
	navigation g_navigation("navigation", "Navigation", "Provides Vocal and Textual Navigational Assistance", g.self.nav);
}
