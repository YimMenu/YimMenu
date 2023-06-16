#include "backend/bool_command.hpp"
#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "util/vehicle.hpp"


namespace big
{
	class speedo_meter : looped_command
	{
		std::array<std::string_view, 3> m_speed_types = {"kmph", "miph", "mps"};

		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (!self::veh || !g_local_player->m_vehicle || HUD::IS_PAUSE_MENU_ACTIVE() || HUD::IS_WARNING_MESSAGE_ACTIVE() || CAM::IS_SCREEN_FADED_OUT() || CAM::IS_SCREEN_FADING_OUT() || CAM::IS_SCREEN_FADING_IN())
			{
				return;
			}

			HUD::SET_TEXT_FONT(2);
			HUD::SET_TEXT_SCALE(.9f, .9f);
			HUD::SET_TEXT_OUTLINE();
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(m_speed_types[(int)g.vehicle.speed_unit].data());
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(g.vehicle.speedo_meter.x, g.vehicle.speedo_meter.y, 1);

			const auto vehicle_speed = vehicle::mps_to_speed(g_local_player->m_vehicle->get_speed(), g.vehicle.speed_unit);
			auto char_width{0};
			if (!g.vehicle.speedo_meter.left_side)
			{
				char_width = g.vehicle.speed_unit == SpeedUnit::KMPH ? 4 : 3;
			}
			HUD::SET_TEXT_FONT(2);
			HUD::SET_TEXT_SCALE(.9f, .9f);
			HUD::SET_TEXT_OUTLINE();
			HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(std::format("{1:>{0}.0f}", char_width, vehicle_speed).c_str());
			HUD::END_TEXT_COMMAND_DISPLAY_TEXT(g.vehicle.speedo_meter.x + (g.vehicle.speedo_meter.left_side ? 0 : .003f),
			    g.vehicle.speedo_meter.y + .04f,
			    1);

			if (g.vehicle.speedo_meter.show_current_gear)
			{
				const auto& current_gear = g_local_player->m_vehicle->m_current_gear;
				std::string gear_str     = std::to_string(current_gear);
				if (!current_gear)
					gear_str = "R";

				HUD::SET_TEXT_FONT(2);
				HUD::SET_TEXT_SCALE(.9f, .9f);
				HUD::SET_TEXT_OUTLINE();
				HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(std::format("{1:>{0}}", char_width, gear_str).c_str());
				HUD::END_TEXT_COMMAND_DISPLAY_TEXT(g.vehicle.speedo_meter.x + (g.vehicle.speedo_meter.left_side ? 0 : .003f),
				    g.vehicle.speedo_meter.y + .08f,
				    1);
			}
		}
	};

	speedo_meter
	    g_speedo_meter("speedometer", "Speedometer", "Enable/disable the speedo meter for vehicles.", g.vehicle.speedo_meter.enabled);
	bool_command g_speedo_meter_gears("speedometergears", "Show current gear", "Adds the current gear the vehicle is in to the speedo meter.",
	    g.vehicle.speedo_meter.show_current_gear);
	bool_command g_speedo_meter_left_side("speedometerleftside", "Align to left", "Aligns the speedo meter text to the left instead of to the right.",
	    g.vehicle.speedo_meter.left_side);
}