#pragma once

#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class drive_on_water : public looped_command
	{
		using looped_command::looped_command;

		const rage::joaat_t drive_on_water_surface_hash = RAGE_JOAAT("stt_prop_stunt_bblock_xl3");
		Vector3 drive_on_water_last_loc;

		void drive_on_water_hide_surface();

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline drive_on_water
		    g_drive_on_water("driveonwater", "Drive On Water", "Allows you to drive on water", g.vehicle.drive_on_water);
	}
}
