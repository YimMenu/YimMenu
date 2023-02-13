#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "pointers.hpp"

namespace big
{	
	class aimassist : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			for (auto replay_interface = *g_pointers->m_replay_interface; g.window.ingame_overlay.show_replay_interface;)
			{
				int current = replay_interface->m_ped_interface->m_cur_peds;
				Ped target = replay_interface->m_ped_interface->m_ped_list->m_peds->m_handle;
				g.weapons.aimbot.aimbone = (int)PedBones::SKEL_Head;
				int bone = g.weapons.aimbot.aimbone; //need to make option to change it
				Vector3 bonec = PED::GET_PED_BONE_COORDS(target, bone, 0, 0, 0);
				bonec = g.weapons.aimbot.bonec;
				float weaponrange = WEAPON::GET_MAX_RANGE_OF_CURRENT_PED_WEAPON(self::ped);
				float targetdist = SYSTEM::VDIST(bonec.x, bonec.y, bonec.z, self::pos.x, self::pos.y, self::pos.z);
				bool os = ENTITY::IS_ENTITY_ON_SCREEN(target);
				bool requirement = PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && weaponrange >= targetdist;
				if (os)
				{
					if (g.weapons.aimbot.aimall && requirement)
					{
						PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
					}
					if (g.weapons.aimbot.aimplayers && requirement)
					{
						bool p = PED::IS_PED_A_PLAYER(target);
						if (p)
						{
							if (g.weapons.aimbot.excludefriends)
							{
								int r = PED::GET_RELATIONSHIP_BETWEEN_PEDS(self::ped, target);
								if (r == 0)
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
					if (g.weapons.aimbot.aimenemies && requirement)
					{
						int r = PED::GET_RELATIONSHIP_BETWEEN_PEDS(self::ped, target);
						if (r == 4 || 5)
						{
							PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
						}
					}
					if (g.weapons.aimbot.aimnpc && requirement)
					{
						bool p = PED::IS_PED_A_PLAYER(target);
						if (!p)
						{
							bool h = PED::IS_PED_HUMAN(target);
							if (h)
							{
								PED::SET_PED_SHOOTS_AT_COORD(self::ped, bonec.x, bonec.y, bonec.z, true);
							}
						}
						if (g.weapons.aimbot.aimcops && requirement)
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
