#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "gta/enums.hpp"

namespace big
{	
	class aimassist : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			const int maxPeds = 32;
			Ped nearbypeds[maxPeds];
			PED::GET_PED_NEARBY_PEDS(self::ped, nearbypeds, -1);
			for (int i = 0; i < maxPeds; i++)
			{
				Ped target = nearbypeds[i];
				g.weapons.aimbot.aimbone = (int)PedBones::SKEL_Head;
				int bone = g.weapons.aimbot.aimbone; //need to make option to change it
				Vector3 bonec = PED::GET_PED_BONE_COORDS(target, bone, 0, 0, 0);
				g.weapons.aimbot.bonec = bonec;
				float weaponrange = WEAPON::GET_MAX_RANGE_OF_CURRENT_PED_WEAPON(self::ped);
				float targetdist = SYSTEM::VDIST(bonec.x, bonec.y, bonec.z, self::pos.x, self::pos.y, self::pos.z);
				ENTITY::IS_ENTITY_ON_SCREEN(target);
				if (true)
				{
					int offsettedID = i * 2 + 2;
					if (nearbypeds[offsettedID] && offsettedID != NULL)
					{
						if (g.weapons.aimbot.aimall && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist)
						{
							PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
						}
						if (g.weapons.aimbot.aimplayers && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist)
						{
							PED::IS_PED_A_PLAYER(target);
							if (true)
							{
								if(g.weapons.aimbot.excludefriends)
								{
									PED::GET_RELATIONSHIP_BETWEEN_PEDS(self::ped, target);
									if (0)
									{
										PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
									}
								}
								else
								{
									PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
								}
							}
						}
						if (g.weapons.aimbot.aimenemies && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist)
						{
							PED::GET_RELATIONSHIP_BETWEEN_PEDS(self::ped, target);
							if (4 | 5)
							{
								PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
							}
						}
						if (g.weapons.aimbot.aimnpc && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist)
						{
							PED::IS_PED_A_PLAYER(target);
							if (false)
							{
								PED::IS_PED_HUMAN(target);
								if (true)
								{
									PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
								}
							}
							if (g.weapons.aimbot.aimcops && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist)
							{
								PED::GET_PED_TYPE(target);
								if (ePedType::PED_TYPE_ARMY | ePedType::PED_TYPE_SWAT | ePedType::PED_TYPE_COP)
								{
									PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
								}
							}
						}
					}
				}
			}
		}
		virtual void on_disable() override
		{
			PED::SET_PED_SHOOTS_AT_COORD(self::ped, g.weapons.aimbot.bonec.x, g.weapons.aimbot.bonec.y, g.weapons.aimbot.bonec.z, false);
		}
	};

	aimassist g_aimassist("aimbot", "Aimbot", "Aim At Any Target With Perfect Accuracy.", g.weapons.aimbot.aimbottg);
	bool_command g_aimall("aimall", "Aim All", "Sets the aimbot to aim at all ped types.", g.weapons.aimbot.aimall);
	bool_command g_aimplayers("aimplayers", "Aim Players", "Sets the aimbot to aim at players.", g.weapons.aimbot.aimplayers);
	bool_command g_aimenemies("aimenemies", "Aim Enemies", "Sets the aimbot to aim at enemies.", g.weapons.aimbot.aimenemies);
	bool_command g_aimnpc("aimnpc", "Aim Npc", "Sets the aimbot to aim at npcs.", g.weapons.aimbot.aimnpc);
	bool_command g_aimcops("aimcops", "Aim All Cop Types", "Sets the aimbot to aim at cops, swat, and army.", g.weapons.aimbot.aimcops);
	bool_command g_exlcude("exfriend", "Exclude Friends", "Sets the aimbot to ignore your friends.", g.weapons.aimbot.excludefriends);
}
