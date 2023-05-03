#pragma once

#include "backend/bool_command.hpp"
#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class speedo_meter : public looped_command
	{
		std::array<std::string_view, 3> m_speed_types = {"kmph", "miph", "mps"};

		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline speedo_meter g_speedo_meter("speedometer", "Enabled", "Enable/disable the speedo meter for vehicles.",
		    g.vehicle.speedo_meter.enabled);

		inline bool_command g_speedo_meter_gears("speedometergears", "Show current gear", "Adds the current gear the vehicle is in to the speedo meter.",
		    g.vehicle.speedo_meter.show_current_gear);

		inline bool_command g_speedo_meter_left_side("speedometerleftside", "Align to left", "Aligns the speedo meter text to the left instead of to the right.",
		    g.vehicle.speedo_meter.left_side);
	}
}
