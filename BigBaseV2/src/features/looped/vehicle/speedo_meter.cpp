#include "features/vehicle.hpp"
#include "natives.hpp"

namespace big
{
	void vehicle::speedo_meter()
	{
		static const float x = .9f;
		static const float y = .72f;

		int64_t speedo_type = g_settings.options["speedo_type"].get<int64_t>();

		if (speedo_type == 0 || HUD::IS_PAUSE_MENU_ACTIVE()) return;

		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id), false);

		if (veh == 0) return;

		char speed_type[16], speed[32];
		float veh_speed = ENTITY::GET_ENTITY_SPEED(veh);
		switch (speedo_type)
		{
		case 1:
			veh_speed *= 3.6;
			strcpy(speed_type, "kph");
			break;
		case 2:
			veh_speed *= 2.2369;
			strcpy(speed_type, "mph");
			break;
		}

		sprintf(speed, "%d", (int)veh_speed);

		HUD::SET_TEXT_FONT(2);
		HUD::SET_TEXT_SCALE(.9f, .9f);
		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(speed);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y + .04f, 1);

		HUD::SET_TEXT_FONT(2);
		HUD::SET_TEXT_SCALE(.91f, .91f);
		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(speed_type);
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, 1);
	}
}