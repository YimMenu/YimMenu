#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "natives.hpp"
#include "vehicle/CVehicleModelInfo.hpp"
#include "gta/enums.hpp"


#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class ability_selector : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (g_local_player && g_local_player->m_vehicle && self::veh)
			{
				CVehicleModelInfo* modelinfo = (CVehicleModelInfo*)g_local_player->m_vehicle->m_model_info;

				switch (g.vehicle.ability_chosen)
				{
				case VehicleAbility::BOOST: modelinfo->m_ability_flag = 0; break;
				}
				if (PED::IS_PED_DEAD_OR_DYING(self::ped, 0) || PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_VEH_EXIT))
				{
					g.vehicle.ability_chosen  = VehicleAbility::NONE;
					modelinfo->m_ability_flag = 0;
				}

				if (g.vehicle.ability_chosen == VehicleAbility::BOOST)
				{
					modelinfo->m_ability_flag = 64;
				}
				if (g.vehicle.ability_chosen == VehicleAbility::BOOSTJUMP)
				{
					modelinfo->m_ability_flag = 96;
				}
				if (g.vehicle.ability_chosen == VehicleAbility::BOOSTJUMPPARACHUTE)
				{
					modelinfo->m_ability_flag = 352;
				}
				if (g.vehicle.ability_chosen == VehicleAbility::BOOSTJUMPRRAMPBUGGYPARACHUTE)
				{
					modelinfo->m_ability_flag = 864;
				}
				if (g.vehicle.ability_chosen == VehicleAbility::BOOSTPARACHUTE)
				{
					modelinfo->m_ability_flag = 320;
				}
				if (g.vehicle.ability_chosen == VehicleAbility::BOOSTPARACHUTERAMPBUGGY)
				{
					modelinfo->m_ability_flag = 832;
				}
				if (g.vehicle.ability_chosen == VehicleAbility::DRIFTJUMP)
				{
					modelinfo->m_ability_flag = 228;
				}
				if (g.vehicle.ability_chosen == VehicleAbility::JUMP)
				{
					modelinfo->m_ability_flag = 32;
				}
				if (g.vehicle.ability_chosen == VehicleAbility::JUMPPARACHUTE)
				{
					modelinfo->m_ability_flag = 288;
				}
				if (g.vehicle.ability_chosen == VehicleAbility::PARACHUTE)
				{
					modelinfo->m_ability_flag = 256;
				}
				if (g.vehicle.ability_chosen == VehicleAbility::RAMPBUGGY)
				{
					modelinfo->m_ability_flag = 512;
				}
				if (g.vehicle.ability_chosen == VehicleAbility::CUSTOM)
				{
					modelinfo->m_ability_flag = g.vehicle.customvalue;
				}

			}
			else
			{
				g_notification_service->push_warning("Warning", "Please be in a vehicle before overriding vehicle abilities.");
				g.vehicle.ability_toggle = false;
				return;
			}
		}

	};

	ability_selector g_ability_selector("vehabilities", "Override Ability", "Allows you to override your vehicle's ability with whatever you choose!",
	    g.vehicle.ability_toggle);
}