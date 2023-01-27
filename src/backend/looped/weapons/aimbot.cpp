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
			float weaponrange = WEAPON::GET_MAX_RANGE_OF_CURRENT_PED_WEAPON(self::ped);
			float targetdist = SYSTEM::VDIST(bonec.x, bonec.y, bonec.z, self::pos.x, self::pos.y, self::pos.z);

			if (g.weapons.aimbot.aimall)
			{
				PED::GET_CLOSEST_PED(self::pos.x, self::pos.y, self::pos.z, rad, 0, 0, &target, 0, 0, -1); //do is cop check when aiming/shooting
			}

			if (g.weapons.aimbot.aimanimals)
			{
				PED::GET_CLOSEST_PED(self::pos.x, self::pos.y, self::pos.z, rad, 0, 0, &target, 0, 0, 28);
			}

			if (g.weapons.aimbot.aimswat)
			{
				PED::GET_CLOSEST_PED(self::pos.x, self::pos.y, self::pos.z, rad, 0, 0, &target, 0, 0, 27);
			}

			if (g.weapons.aimbot.aimcop)
			{
				PED::GET_CLOSEST_PED(self::pos.x, self::pos.y, self::pos.z, rad, 0, 0, &target, 0, 0, 6);
			}

			if (g.weapons.aimbot.aimarmy)
			{
				PED::GET_CLOSEST_PED(self::pos.x, self::pos.y, self::pos.z, rad, 0, 0, &target, 0, 0, 29);
			}

			if (g.weapons.aimbot.aimnpconly)
			{
				PED::GET_CLOSEST_PED(self::pos.x, self::pos.y, self::pos.z, rad, 0, 0, &target, 0, 0, 26);
			}

			if (g.weapons.aimbot.aimplayers)
			{
				PED::GET_CLOSEST_PED(self::pos.x, self::pos.y, self::pos.z, rad, 0, 0, &target, 0, 0, 1);
			}

			if (g.weapons.aimbot.aimplayers && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(self::ped, target, 17) && targetdist <= weaponrange)
			{
				if (PED::IS_PED_A_PLAYER(target))
				{
					TASK::TASK_AIM_GUN_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, 500, true, false);
					if (g.weapons.aimbot.triggerbot)
					{
						PED::IS_PED_DEAD_OR_DYING(target, 1) ? false : true;
						if (false);
						{
							MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(self::pos.x, self::pos.y, self::pos.z, bonec.x, bonec.y, bonec.z, 1, 0, weapon, self::ped, true, false, 10.0f);
						}
					}
				}
			}
			if (!g.weapons.infinite_range)
			{
				if (g.weapons.aimbot.aimall || g.weapons.aimbot.aimnpconly || g.weapons.aimbot.aimanimals || g.weapons.aimbot.aimarmy || g.weapons.aimbot.aimswat || g.weapons.aimbot.aimcop && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(self::ped, target, 17) && targetdist <= weaponrange)
				{
					TASK::TASK_AIM_GUN_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, 500, true, false);
					if (g.weapons.aimbot.triggerbot)
					{
						PED::IS_PED_DEAD_OR_DYING(target, 1) ? false : true;
						if (false);
						{
							MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(self::pos.x, self::pos.y, self::pos.z, bonec.x, bonec.y, bonec.z, 1, 0, weapon, self::ped, true, false, 10.0f);
						}
					}
				}
			}
			if (g.weapons.infinite_range)
			{
				if (g.weapons.aimbot.aimall || g.weapons.aimbot.aimnpconly || g.weapons.aimbot.aimanimals || g.weapons.aimbot.aimarmy || g.weapons.aimbot.aimswat || g.weapons.aimbot.aimcop && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(self::ped, target, 17))
				{
					TASK::TASK_AIM_GUN_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, 500, true, false);
					if (g.weapons.aimbot.triggerbot)
					{
						PED::IS_PED_DEAD_OR_DYING(target, 1) ? false : true;
						if (false);
						{
							MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(self::pos.x, self::pos.y, self::pos.z, bonec.x, bonec.y, bonec.z, 1, 0, weapon, self::ped, true, false, 10.0f);
						}
					}
				}
			}
		}

	};

	//This function only works if the ped is walking normally or wanting to cross a road apparently, need to implement better way of getting them


	aimassist g_aimassist("aimbot", "Aimbot", "Aim At Any Target With Perfect Accuracy", g.weapons.aimbot.aimbottog);
	bool_command g_aimnpc("aimnpc", "Aim At Npc", "Sets the aimbot to aim at npcs only.", g.weapons.aimbot.aimnpconly);
	bool_command g_aimall("aimall", "Aim At All", "Sets the aimbot to aim at all peds, including animals.", g.weapons.aimbot.aimall);
	bool_command aimanimal("aimanimal", "Aim At Animals", "Sets the aimbot to aim at all animals.", g.weapons.aimbot.aimanimals);
	bool_command aimarmy("aimarmy", "Aim At All", "Sets the aimbot to aim at all military peds.", g.weapons.aimbot.aimarmy);
	bool_command aimswat("aimswat", "Aim At All", "Sets the aimbot to aim at all swat peds.", g.weapons.aimbot.aimswat);
	bool_command aimcop("aimcop", "Aim At Cop", "Sets the aimbot to aim at all peds, including animals.", g.weapons.aimbot.aimall);
	bool_command g_aimplayers("aimplayers", "Aim At Players", "Sets the aimbot to aim at players only.", g.weapons.aimbot.aimplayers);
	bool_command g_triggerbot("triggerbot", "Triggerbot", "Sets aimbot to shoot along with aiming.", g.weapons.aimbot.triggerbot);
}
