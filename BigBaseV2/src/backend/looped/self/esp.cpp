#include "backend/looped/looped.hpp"
#include "pointers.hpp"
#include "natives.hpp"
#include "script_global.hpp"

namespace big
{
	void esp(Ped ped, bool boolean)
	{
		if (boolean)
		{
			for (int index = 0; index < 32; index++)
			{
				Player playerOnline = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(index);
				BOOL bPlayerOnlineExists = ENTITY::DOES_ENTITY_EXIST(playerOnline);
				Vector3 playerOnlineCoords = ENTITY::GET_ENTITY_COORDS(playerOnline, FALSE);
				Vehicle currentOnlineVeh = PED::GET_VEHICLE_PED_IS_USING(playerOnline);
				Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(ped, FALSE);
				if (playerOnline == ped) continue;
				const char* name = PLAYER::GET_PLAYER_NAME(PLAYER::INT_TO_PLAYERINDEX(index));
				int health = ENTITY::GET_ENTITY_HEALTH(playerOnline);
				float distance = MISC::GET_DISTANCE_BETWEEN_COORDS(playerCoords.x, playerCoords.y, playerCoords.z, playerOnlineCoords.x, playerOnlineCoords.y, playerOnlineCoords.z, TRUE);
				int armor = PED::GET_PED_ARMOUR(playerOnline);
				char text[250];
				if (distance < 5000.0f && bPlayerOnlineExists)
				{
					float xa;
					float ya;
					BOOL screenCoords = GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(playerOnlineCoords.x, playerOnlineCoords.y, playerOnlineCoords.z, &xa, &ya);
					if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(ped, playerOnline, 17) && bPlayerOnlineExists)
					{
						sprintf_s(text, "%s ~y~%.02f\n~g~%d ~b~%d", name, distance, health, armor);
						HUD::SET_TEXT_FONT(0);
						HUD::SET_TEXT_OUTLINE();
						HUD::SET_TEXT_SCALE(0.23f, 0.23f);
						HUD::SET_TEXT_COLOUR(0, 255, 0, 255);
						HUD::SET_TEXT_WRAP(0.0f, 1.0f);
						HUD::SET_TEXT_CENTRE(TRUE);
						HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
						HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
					}
					else
					{
						sprintf_s(text, "%s\n ~y~%.02f", name, distance);
						HUD::SET_TEXT_FONT(0);
						HUD::SET_TEXT_OUTLINE();
						HUD::SET_TEXT_SCALE(0.15f, 0.15f);
						HUD::SET_TEXT_COLOUR(255, 0, 0, 75);
						HUD::SET_TEXT_WRAP(0.0f, 1.0f);
						HUD::SET_TEXT_CENTRE(TRUE);
						HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
						HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
					}
					HUD::END_TEXT_COMMAND_DISPLAY_TEXT(xa, ya, 0);
				}
			}




			for (int index = 0; index < 32; index++)
			{
				Player playerOnline = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(index);
				BOOL bPlayerOnlineExists = ENTITY::DOES_ENTITY_EXIST(playerOnline);
				Vector3 playerOnlineCoords = ENTITY::GET_ENTITY_COORDS(playerOnline, FALSE);
				const char* name = PLAYER::GET_PLAYER_NAME(PLAYER::INT_TO_PLAYERINDEX(index));
				if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(ped, playerOnline, 17) && bPlayerOnlineExists)
				{
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x + 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z + 0.75f, playerOnlineCoords.x + 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z + 0.75f, 0, 255, 0, 255);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x + 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z + 0.75f, playerOnlineCoords.x - 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z + 0.75f, 0, 255, 0, 255);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x - 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z + 0.75f, playerOnlineCoords.x - 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z + 0.75f, 0, 255, 0, 255);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x - 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z + 0.75f, playerOnlineCoords.x + 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z + 0.75f, 0, 255, 0, 255);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x + 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x + 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z - 0.75f, 0, 255, 0, 255);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x + 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x - 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z - 0.75f, 0, 255, 0, 255);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x - 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x - 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z - 0.75f, 0, 255, 0, 255);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x - 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x + 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z - 0.75f, 0, 255, 0, 255);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x + 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x + 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z + 0.75f, 0, 255, 0, 255);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x + 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x + 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z + 0.75f, 0, 255, 0, 255);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x - 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x - 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z + 0.75f, 0, 255, 0, 255);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x - 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x - 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z + 0.75f, 0, 255, 0, 255);
				}
				else
				{
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x + 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z + 0.75f, playerOnlineCoords.x + 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z + 0.75f, 255, 0, 0, 75);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x + 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z + 0.75f, playerOnlineCoords.x - 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z + 0.75f, 255, 0, 0, 75);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x - 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z + 0.75f, playerOnlineCoords.x - 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z + 0.75f, 255, 0, 0, 75);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x - 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z + 0.75f, playerOnlineCoords.x + 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z + 0.75f, 255, 0, 0, 75);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x + 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x + 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z - 0.75f, 255, 0, 0, 75);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x + 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x - 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z - 0.75f, 255, 0, 0, 75);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x - 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x - 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z - 0.75f, 255, 0, 0, 75);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x - 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x + 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z - 0.75f, 255, 0, 0, 75);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x + 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x + 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z + 0.75f, 255, 0, 0, 75);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x + 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x + 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z + 0.75f, 255, 0, 0, 75);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x - 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x - 0.5f, playerOnlineCoords.y - 0.5f, playerOnlineCoords.z + 0.75f, 255, 0, 0, 75);
					GRAPHICS::DRAW_LINE(playerOnlineCoords.x - 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z - 0.75f, playerOnlineCoords.x - 0.5f, playerOnlineCoords.y + 0.5f, playerOnlineCoords.z + 0.75f, 255, 0, 0, 75);
				}
			}

		}

	}
	bool bEsp = false;
	void looped::self_esp()
	{
		if (g_local_player == nullptr || g_local_player->m_player_info == nullptr) return;
		bool bchek = g.self.esp;
		if (bchek || (!bchek && bchek != bEsp))
		{
			Ped self = PLAYER::PLAYER_PED_ID();

			esp(self, g.self.esp);
			bchek = g.self.esp;



		}


	}
}