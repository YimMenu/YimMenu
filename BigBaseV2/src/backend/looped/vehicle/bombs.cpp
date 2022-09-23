#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "gta/joaat.hpp"
#include "script.hpp"
#include "natives.hpp"

namespace big
{
	void looped::vehicle_bombs()
	{
		if (!g->vehicle.bombs) return;

		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_CREATOR_ACCEPT) && VEHICLE::GET_ARE_BOMB_BAY_DOORS_OPEN(self::veh))
		{
			Hash hash = rage::joaat(g->vehicle.bomb_type);
			STREAMING::REQUEST_MODEL(hash);
			WEAPON::REQUEST_WEAPON_ASSET(hash, 31, 26);
			Vector3 offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::veh, 0.0, 0.0, -10.0);
			AUDIO::PLAY_SOUND_FROM_ENTITY(-1, "bomb_deployed", self::veh, "DLC_SM_Bomb_Bay_Bombs_Sounds", true, 0);
			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS_IGNORE_ENTITY_NEW(self::pos.x, self::pos.y, self::pos.z, offset.x, offset.y, offset.z, 0, true, hash, self::ped, true, true, -1.f, self::veh, false, false, false, true, true, false, 0);
			script::get_current()->yield(100ms); //this is stupid
		}
	} // this shitty code does not work
}