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
			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK) && PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				Ped targetped = NULL;
				Vector3 target = {0, 0, 0};
				PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(self::ped, &targetped);
				target = PED::GET_PED_BONE_COORDS(targetped, (int)PedBones::SKEL_Head, 0, 0, 0);
				PED::SET_PED_SHOOTS_AT_COORD(self::ped, target.x, target.y, target.z, true);
			}
		}
	};

	aim_assist_looped g_aim_assist_looped("aimassist", "Aim Assist", "Kill any npc with perfect accuracy.", g.weapons.aim_assist);
}
