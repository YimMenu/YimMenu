#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void looped::vehicle_speedo_meter()
	{
		if (!g.vehicle.speedo_meter.enabled || self::veh == 0 || HUD::IS_PAUSE_MENU_ACTIVE() || HUD::IS_WARNING_MESSAGE_ACTIVE() || CAM::IS_SCREEN_FADED_OUT() || CAM::IS_SCREEN_FADING_OUT() || CAM::IS_SCREEN_FADING_IN())
		{
			return;
		}


		char speed_type[16], speed[16];
		int char_width = 3;

		float veh_speed = vehicle::mps_to_speed(ENTITY::GET_ENTITY_SPEED(self::veh), g.vehicle.speed_unit);

		switch (g.vehicle.speed_unit)
		{
		case SpeedUnit::KMPH:
			strcpy(speed_type, "kmph");
			char_width = 4;
			break;
		case SpeedUnit::MIPH: strcpy(speed_type, "mph"); break;
		case SpeedUnit::MPS: strcpy(speed_type, "mps"); break;
		}

		sprintf(speed, "%*d", g.vehicle.speedo_meter.left_side ? 0 : char_width, (int)veh_speed);

		HUD::SET_TEXT_FONT(2);
		HUD::SET_TEXT_SCALE(.9f, .9f);
		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(speed_type);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(g.vehicle.speedo_meter.x, g.vehicle.speedo_meter.y, 1);

		HUD::SET_TEXT_FONT(2);
		HUD::SET_TEXT_SCALE(.9f, .9f);
		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(speed);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(g.vehicle.speedo_meter.x + (g.vehicle.speedo_meter.left_side ? 0 : .003f),
		    g.vehicle.speedo_meter.y + .04f,
		    1);
	}
}