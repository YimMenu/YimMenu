#include "backend/looped/looped.hpp"
#include "core/data/speedo_meters.hpp"
#include "natives.hpp"

namespace big
{
	void looped::vehicle_speedo_meter()
	{
		SpeedoMeter speedo_type = g->vehicle.speedo_meter.type;

		if (speedo_type == SpeedoMeter::DISABLED || HUD::IS_PAUSE_MENU_ACTIVE() || HUD::IS_WARNING_MESSAGE_ACTIVE() || CAM::IS_SCREEN_FADED_OUT() || CAM::IS_SCREEN_FADING_OUT() || CAM::IS_SCREEN_FADING_IN()) return;

		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

		if (veh == 0) return;

		char speed_type[16], speed[16];
		float veh_speed = ENTITY::GET_ENTITY_SPEED(veh);
		switch (speedo_type)
		{
		case SpeedoMeter::KMH:
			veh_speed *= 3.6;
			strcpy(speed_type, "kph");
			break;
		case SpeedoMeter::MPH:
			veh_speed *= 2.2369;
			strcpy(speed_type, "mph");
			break;
		}

		sprintf(speed, "%*d", g->vehicle.speedo_meter.left_side ? 0 : 3, (int)veh_speed);

		HUD::SET_TEXT_FONT(2);
		HUD::SET_TEXT_SCALE(.9f, .9f);
		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(speed);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(g->vehicle.speedo_meter.x, g->vehicle.speedo_meter.y + .04f, 1);

		HUD::SET_TEXT_FONT(2);
		HUD::SET_TEXT_SCALE(.91f, .91f);
		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(speed_type);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(g->vehicle.speedo_meter.x, g->vehicle.speedo_meter.y, 1);
	}
}