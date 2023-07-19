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

#include <thread_pool.hpp>


//70 feet annouce the next action plus what is coming up


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
			// taken from a native db website.
			/*
			distToNxJunction seems to be the distance in metres * 10.0f

		direction:

		0 = This happens randomly during the drive for seemingly no reason but if you consider that this native is only used in trevor3, it seems to mean "Next frame, stop whatever's being said and tell the player the direction."
		1 = Route is being calculated or the player is going in the wrong direction
		2 = Please Proceed the Highlighted Route
		3 = In (distToNxJunction) Turn Left
		4 = In (distToNxJunction) Turn Right
		5 = In (distToNxJunction) Keep Straight
		6 = In (distToNxJunction) Turn Sharply To The Left
		7 = In (distToNxJunction) Turn Sharply To The Right
		8 = Route is being recalculated or the navmesh is confusing. This happens randomly during the drive but consistently at {2044.0358, 2996.6116, 44.9717} if you face towards the bar and the route needs you to turn right. In that particular case, it could be a bug with how the turn appears to be 270 deg. CCW instead of "right." Either way, this seems to be the engine saying "I don't know the route right now."
			*/


			g_fiber_pool->queue_job([] {
				int direction;
				int feetToAction;
				Vector3 waypoint;
				float dist;
				float v;
				// most important variables have been declared upfront
				blip::get_blip_location(waypoint, (int)BlipIcons::Waypoint);
				bool doesPointExist = blip::get_blip_location(waypoint, (int)BlipIcons::Waypoint);
				// the if statement allows the function to not run if there is no player waypoint
				if (doesPointExist)
				{
					PATHFIND::GENERATE_DIRECTIONS_TO_COORD(waypoint.x, waypoint.y, waypoint.z, 1, &direction, &v, &dist);
					feetToAction = math::divided_by_ten(math::meters_to_feet(dist));
					// only display notifications if setting is on
					switch (direction)
					{
					case 1:
						//g_notification_service->push_warning("Navigation", "Route Recalculation");
						if (g.self.nav_text)
							notify::above_map("Route Recalculation");
						if (g.self.nav_voice)
						{
							audio::play_sound("RouteRecalc", 0);
						}
						break;
					case 2:
						//g_notification_service->push_warning("Navigation", "Please proceed to the highlighted route");
						if (g.self.nav_text)
							notify::above_map("Continue on Route");
						if (g.self.nav_voice)
						{
							audio::play_sound("HighlightedRoute", 0);
						}
						break;
					case 3:
						switch (feetToAction)
						{
						case 130:
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 5280);
								audio::play_sound("KeepLeft", 0);
							}
							break;

						case 40:
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 1000);
								audio::play_sound("KeepLeft", 0);
							}
							break;
						case 25:
							if (g.self.nav_text)
								notify::above_map(std::format("Keep Left in {} feet", 500));
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 500);
								audio::play_sound("KeepLeft", 0);
							}
							break;
						case 15:
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 100);
								audio::play_sound("KeepLeft", 0);
							}
							break;
						case 10:
							if (g.self.nav_voice)
							{
								audio::play_sound("KeepLeft", 0);
							}
							break;
						}
						//g_notification_service->push_warning("Navigation", std::format("In {} feet, keep left", feetToAction));
						break;
					case 4:
						switch (feetToAction)
						{
						case 130:
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 5280);
								audio::play_sound("KeepRight", 0);
							}
							break;
						case 40:
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 1000);
								audio::play_sound("KeepRight", 0);
							}
							break;
						case 25:
							if (g.self.nav_text)
								notify::above_map(std::format("Keep Right in {} feet", 500));
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 500);
								audio::play_sound("KeepRight", 0);
							}
							break;
						case 15:
							audio::play_sound("FeetUntilAction", 100);
							audio::play_sound("KeepRight", 0);
							break;
						case 10:
							if (g.self.nav_voice)
							{
								audio::play_sound("KeepRight", 0);
							}
							break;
						}
						//g_notification_service->push_warning("Navigation", std::format("In {} feet, keep right", feetToAction));
						break;
					case 5:
						switch (feetToAction)
						{
						case 130:
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 5280);
								audio::play_sound("Straight", 0);
							}
							break;
						case 40:
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 1000);
								audio::play_sound("Straight", 0);
							}
							break;
						case 25:
							if (g.self.nav_text)
								notify::above_map(std::format("Continue Straight in {} feet", 500));
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 500);
								audio::play_sound("Straight", 0);
							}
							break;
						case 15:
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 100);
								audio::play_sound("Straight", 0);
							}
							break;
						case 10:
							if (g.self.nav_voice)
							{
								audio::play_sound("Straight", 0);
							}
							break;
						}
						//g_notification_service->push_warning("Navigation", std::format("In {} feet, keep straight", feetToAction));
						break;
					case 6:
						switch (feetToAction)
						{
						case 130:
							audio::play_sound("FeetUntilAction", 5280);
							audio::play_sound("TurnLeft", 0);
							break;
						case 40:
							audio::play_sound("FeetUntilAction", 1000);
							audio::play_sound("TurnLeft", 0);
							break;
						case 25:
							if (g.self.nav_text)
								notify::above_map(std::format("Turn Left in {} feet", 500));
							audio::play_sound("FeetUntilAction", 500);
							audio::play_sound("TurnLeft", 0);
							break;
						case 15:
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 100);
								audio::play_sound("TurnLeft", 0);
							}
							break;
						case 10:
							if (g.self.nav_voice)
							{
								audio::play_sound("TurnLeft", 0);
							}
							break;
						}
						//g_notification_service->push_warning("Navigation", std::format("In {} feet, turn left", feetToAction));
						break;
					case 7:
						switch (feetToAction)
						{
						case 130:
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 5280);
								audio::play_sound("TurnRight", 0);
							}
							break;
						case 40:
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 1000);
								audio::play_sound("TurnRight", 0);
							}
							break;
						case 25:
							if (g.self.nav_text)
								notify::above_map(std::format("Turn Right in {} feet", 500));
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 500);
								audio::play_sound("TurnRight", 0);
							}
							break;
						case 15:
							if (g.self.nav_voice)
							{
								audio::play_sound("FeetUntilAction", 100);
								audio::play_sound("TurnRight", 0);
							}
							break;
						case 10:
							if (g.self.nav_voice)
							{
								audio::play_sound("TurnRight", 0);
							}
							break;
						}
						//g_notification_service->push_warning("Navigation", std::format("In {} feet, turn right", feetToAction));
						break;
					case 8:
						//confusing navmesh
						//g_notification_service->push_warning("Navigation", "Route Recalculation");
						if (g.self.nav_voice)
						{
							audio::play_sound("RouteRecalc", 0);
						}
						break;
					}
					LOG(INFO) << std::format("{}                                              {}", direction, math::divided_by_ten(math::meters_to_feet(dist)));
				}
			});
		}

		virtual void on_disable() override
		{
			g_notification_service->push_success("Voice Navigation", "Voice Navigation has been disabled");
		}
	};
	navigationvoice
	    g_navigationvoice("navigationvoice", "Navigation Voice", "Provides Vocal Navigational Assistance", g.self.nav);
}
