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
			if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK) && PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				Ped targetped;
				Vector3 target;
				Hash hash = MISC::GET_HASH_KEY("weapon_assaultrifle_mk2");
				PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(self::ped, &targetped);
				target = PED::GET_PED_BONE_COORDS(targetped, (int)PedBones::SKEL_Head, 0, 0, 0);
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(self::pos.x, self::pos.y, self::pos.z, target.x, target.y, target.z, 10, 1, hash, self::ped, true, false, 10.0f);
			}
		}
	};

	aim_assist_looped g_aim_assist_looped("aimassist", "Aim Assist", "Kill any npc with perfect accuracy.", g.weapons.aim_assist);
}
