#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "core/enums.hpp"

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
				Ped target = NULL;
				int bone = g.weapons.aimbot.aimbone;
				Vector3 bonec = PED::GET_PED_BONE_COORDS(target, bone, 0, 0, 0);
				float weaponrange = WEAPON::GET_MAX_RANGE_OF_CURRENT_PED_WEAPON(self::ped);
				float targetdist = SYSTEM::VDIST(bonec.x, bonec.y, bonec.z, self::pos.x, self::pos.y, self::pos.z);

				if (g.weapons.aimbot.aimall && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist)
				{
					PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
				}
				if (g.weapons.aimbot.aimplayers && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist)
				{
					PED::IS_PED_A_PLAYER(target);
					if(true)
					{
						PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
					}
				}
				if (g.weapons.aimbot.aimanimals && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist)
				{
					PED::IS_PED_HUMAN(target);
					if (false)
					{
						PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
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
				if (g.weapons.aimbot.aimnpconly && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist)
				{
					PED::IS_PED_A_PLAYER(target);
					if (false)
					{
						PED::IS_PED_HUMAN(target);
						if(true)
						{
							PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
						}
					}
				}
				if (g.weapons.aimbot.aimcop && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist)
				{
					PED::GET_PED_TYPE(target);
					if (ePedType::PED_TYPE_COP)
					{				
						PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);					
					}
				}
				if (g.weapons.aimbot.aimswat && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist)
				{
					PED::GET_PED_TYPE(target);
					if (ePedType::PED_TYPE_SWAT)
					{
						PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
					}
				}
				if (g.weapons.aimbot.aimarmy && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist)
				{
					PED::GET_PED_TYPE(target);
					if (ePedType::PED_TYPE_ARMY)
					{
						PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
					}
				}
				if (g.weapons.aimbot.aimallcops && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist)
				{
					PED::GET_PED_TYPE(target);
					if (ePedType::PED_TYPE_ARMY | ePedType::PED_TYPE_SWAT | ePedType::PED_TYPE_COP)
					{
						PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
					}
				}
			}
		}

	}; //todo in gui put into a combo somehow

	aimassist g_aimassist("aimbot", "Aimbot", "Aim At Any Target With Perfect Accuracy.", g.weapons.aimbot.aimbottg);
	bool_command g_aimall("aimall", "Aim All", "Sets the aimbot to aim at all ped types.", g.weapons.aimbot.aimall);
	bool_command g_aimplayers("aimplayers", "Aim Players", "Sets the aimbot to aim at players.", g.weapons.aimbot.aimplayers);
	bool_command g_aimanimals("aimanimals", "Aim Animals", "Sets the aimbot to aim at animals", g.weapons.aimbot.aimanimals);
	bool_command g_aimenemies("aimenemies", "Aim Enemies", "Sets the aimbot to aim at enemies", g.weapons.aimbot.aimenemies);
	bool_command g_aimnpconly("aimnpc", "Aim Npc", "Sets the aimbot to aim at npcs", g.weapons.aimbot.aimnpconly);
	bool_command g_aimcop("aimcop", "Aim Cop", "Sets the aimbot to aim at cops", g.weapons.aimbot.aimcop);
	bool_command g_aimall("aimswat", "Aim Swat", "Sets the aimbot to aim at the swat", g.weapons.aimbot.aimswat);
	bool_command g_aimall("aimarmy", "Aim Army", "Sets the aimbot to aim at the army", g.weapons.aimbot.aimarmy);
	bool_command g_aimall("aimallcop", "Aim All Cop Types", "Sets the aimbot to aim at cops, swat, and army", g.weapons.aimbot.aimallcops);
}
