#pragma once
#include "core/enums.hpp"

namespace big
{
	inline struct auto_drive
	{
		AutoDriveDestination auto_drive_destination = AutoDriveDestination::STOPPED;
		AutoDriveStyle auto_drive_style             = AutoDriveStyle::LAW_ABIDING;
		float auto_drive_speed                      = 8;
		bool is_auto_driving                        = false;
	} g_auto_drive{};
}
