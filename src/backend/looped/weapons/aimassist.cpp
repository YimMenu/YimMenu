#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "gta/enums.hpp"

namespace big
{

	class aim_assist_looped : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			Ped targetped;
			Hash hash = MISC::GET_HASH_KEY("weapon_assaultrifle_mk2");
			Vector3 pedcoords = ENTITY::GET_ENTITY_COORDS(targetped, true);
			Vector3 target = PED::GET_PED_BONE_COORDS(targetped, (int)PedBones::SKEL_Head, target.x, target.y, target.z);
			PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(self::ped, &targetped);
			if (!PED::IS_PED_A_PLAYER(targetped) && PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK) && PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(self::pos.x, self::pos.y, self::pos.z, target.x, target.y, target.z, 10, 1, hash, self::ped, true, false, 100.0f);
			}
		}
	};

	aim_assist_looped g_aim_assist_looped("aimassist", "Aim Assist", "Allows You To Jump As If You Were The Beast Like In The Beast Event", g.weapons.aim_assist);
}
