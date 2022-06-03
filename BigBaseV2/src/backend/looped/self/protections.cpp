#include "backend/looped/looped.hpp"
#include "gta/replay.hpp"
#include "pointers.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	void looped::protections_replay_interface()
	{
		Ped player = PLAYER::PLAYER_PED_ID();
		Vector3 players = ENTITY::GET_ENTITY_COORDS(player, true);
		Hash crashModels[] = { 3107991431, 1327834842, 17258065, 213036232, 386259036, 450174759, 618696223, 849975660, 863710036, 875648136, 987584502, 1173321732, 1221915621, 1481697203, 1567950121, 1727217687, 1734157390, 1759812941, 1775565172, 1781006001, 1793920587, 1936183844, 1982224326, 2015249693, 2040219850, 2041844081, -2114240528, -1884146780, -1511795599, -1231365640, -1065905452, -1026778664, -1025025503, -1010825119, -993438434, -990984874, -964059938, -889446717, -818431457, -814048611, -783590493, -681705050, -646857810, -638302388, -568850501, -508643576, -440885967, -429997852, -412821612, 959275690 };
		for each (Hash h in crashModels) {
			if (OBJECT::IS_OBJECT_NEAR_POINT(h, players.x, players.y, players.z, 2.0f)) {
				Object a = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(players.x, players.y, players.z, 2.0f, h, false, true, true);
				if (ENTITY::DOES_ENTITY_EXIST(a))
				{
					if (entity::take_control_of(a))
					{
						entity::delete_entity(a);
					}
				}
			}
		}
		script::get_current()->yield();
	}
}