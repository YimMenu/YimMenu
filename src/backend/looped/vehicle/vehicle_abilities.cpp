#include "backend/looped_command.hpp"
#include "core/enums.hpp"
#include "natives.hpp"
#include "vehicle/CVehicleModelInfo.hpp"
#include "gta/enums.hpp"

namespace big
{
	class ability_selector : looped_command
	{
		using looped_command::looped_command;

		uint16_t og_ability = 0;
		bool edited		    = false;

		virtual void on_tick() override
		{
			if (g_local_player && g_local_player->m_vehicle && self::veh)
			{
				CVehicleModelInfo* modelinfo = (CVehicleModelInfo*)g_local_player->m_vehicle->m_model_info;

				if (!edited && g.vehicle.ability_chosen == VehicleAbility::NONE)
					og_ability = modelinfo->m_ability_flag;

				if (PED::IS_PED_DEAD_OR_DYING(self::ped, 0) || PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_VEH_EXIT))
				{
					g.vehicle.ability_chosen  = VehicleAbility::NONE;
					modelinfo->m_ability_flag = og_ability;
					edited                    = false;
				}

				switch (g.vehicle.ability_chosen)
				{
				case VehicleAbility::BOOST:
					edited                    = true;
					modelinfo->m_ability_flag = 64;
					break;
				case VehicleAbility::BOOSTJUMP:
					edited                    = true;
					modelinfo->m_ability_flag = 96;
					break;
				case VehicleAbility::BOOSTJUMPPARACHUTE:
					edited                    = true;
					modelinfo->m_ability_flag = 352;
					break;
				case VehicleAbility::BOOSTJUMPRRAMPBUGGYPARACHUTE:
					edited                    = true;
					modelinfo->m_ability_flag = 864;
					break;
				case VehicleAbility::BOOSTPARACHUTE:
					edited                    = true;
					modelinfo->m_ability_flag = 320;
					break;
				case VehicleAbility::BOOSTPARACHUTERAMPBUGGY:
					edited                    = true;
					modelinfo->m_ability_flag = 832;
					break;
				case VehicleAbility::JUMP:
					edited                    = true;
					modelinfo->m_ability_flag = 32;
					break;
				case VehicleAbility::JUMPPARACHUTE:
					edited                    = true;
					modelinfo->m_ability_flag = 288;
					break;
				case VehicleAbility::PARACHUTE:
					edited                    = true;
					modelinfo->m_ability_flag = 256;
					break;
				case VehicleAbility::RAMPBUGGY:
					edited                    = true;
					modelinfo->m_ability_flag = 512;
					break;
				case VehicleAbility::CUSTOM:
					edited                    = true;
					modelinfo->m_ability_flag = g.vehicle.customvalue;
					break;
				}
			}
		}
	};

	ability_selector g_ability_selector("vehabilities", "Override Ability", "Allows you to override your vehicle's ability with whatever you've choosen.",
	    g.vehicle.ability_toggle);
}