#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "natives.hpp"
#include "vehicle/CVehicleModelInfo.hpp"

namespace big
{
	void looped::vehicle_ability()
	{
		if (g_local_player && g_local_player->m_vehicle)
		{
			CVehicleModelInfo* modelinfo = (CVehicleModelInfo*)g_local_player->m_vehicle->m_model_info;

			if (PED::IS_PED_DEAD_OR_DYING(self::ped, 0)) //FIGURE OUT HOW TO GET LAST VEHICLE
			{
				g.vehicle.ability_chosen = VehicleAbility::NONE;
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
		}
	}
}