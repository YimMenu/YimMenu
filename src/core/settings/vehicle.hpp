#pragma once
#include "core/enums.hpp"

namespace big
{
	inline struct g_vehicle_t
	{
		bool god_mode            = false;
		bool block_homing        = false;
		bool seatbelt            = false;
		bool vehicle_jump        = false;
		bool all_vehs_in_heists  = false;
		bool veh_boost           = false;

		AutoDriveDestination auto_drive_destination = AutoDriveDestination::STOPPED;
		AutoDriveStyle auto_drive_style             = AutoDriveStyle::LAW_ABIDING;
		float auto_drive_speed                      = 8;
		bool is_auto_driving                        = false;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(g_vehicle_t, auto_drive_destination, auto_drive_style, auto_drive_speed)
	} g_vehicle{};
}
