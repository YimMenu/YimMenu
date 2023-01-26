#include "backend/looped/looped.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class aimassist : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			Ped target;
			float rad = g.weapons.aimbot.aimradius;
			int bone = g.weapons.aimbot.aimbone;
			Hash weapon; WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weapon, 0);
			Vector3 bonec = PED::GET_PED_BONE_COORDS(target, bone, 0, 0, 0);

			if (g.weapons.aimbot.aimall)
			{
				PED::GET_CLOSEST_PED(self::pos.x, self::pos.y, self::pos.z, rad, 0, 0, &target, 0, 0, -1);
			}

			if (g.weapons.aimbot.aimnpconly || g.weapons.aimbot.aimplayers)
			{
				PED::GET_CLOSEST_PED(self::pos.x, self::pos.y, self::pos.z, rad, 0, 0, &target, 0, 0, 26);
			}

			if (g.weapons.aimbot.aimplayers)
			{
				if (PED::IS_PED_A_PLAYER(target))
				{
					TASK::TASK_AIM_GUN_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, 500, true, false);
					if (g.weapons.aimbot.triggerbot)
					{
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(self::pos.x, self::pos.y, self::pos.z, bonec.x, bonec.y, bonec.z, 1, 0, weapon, self::ped, true, false, 10.0f);
					}
				}
			}

			if (g.weapons.aimbot.aimall || g.weapons.aimbot.aimnpconly)
			{
				TASK::TASK_AIM_GUN_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, 500, true, false);
				if (g.weapons.aimbot.triggerbot)
				{
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(self::pos.x, self::pos.y, self::pos.z, bonec.x, bonec.y, bonec.z, 1, 0, weapon, self::ped, true, false, 10.0f);
				}
			}
		}

	};

	aimassist g_aimassist("aimbot", "Aimbot", "Aim At Any Target With Perfect Accuracy", g.weapons.aimbot.aimbottog);
	bool_command g_aimnpcs("aimnpcs", "Aim Npc", "Sets the aimbot to aim at npcs only.", g.weapons.aimbot.aimnpconly);
	bool_command g_aimall("aimall", "Aim All", "Sets the aimbot to aim at all peds, including animals.", g.weapons.aimbot.aimall);
	bool_command g_aimplayers("aimplayers", "Aim Players", "Sets the aimbot to aim at players only.", g.weapons.aimbot.aimplayers);
	bool_command g_triggerbot("triggerbot", "Triggerbot", "Sets aimbot to shoot.", g.weapons.aimbot.triggerbot);
}
