#pragma once

namespace big
{
	inline struct g_vehicle
	{
		bool god_mode;
		bool block_homing;
		bool seatbelt;
		bool vehicle_jump;
		bool all_vehs_in_heists;
		bool veh_boost;

		bool spawn_inside;
		bool spawn_at_waypoint;
		bool preview_vehicle;
		std::string garage = "";
	} g_vehicle{};
}
