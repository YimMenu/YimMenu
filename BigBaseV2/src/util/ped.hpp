#pragma once
#include "natives.hpp"
#include "script.hpp"

namespace big::ped
{
	inline void steal_outfit(const Ped target)
	{
		Ped ped = self::ped;
		
		if (ENTITY::GET_ENTITY_MODEL(ped) != ENTITY::GET_ENTITY_MODEL(target)) {
			g_notification_service->push("Error", "Model mismatch, use steal identity instead.");
			return;
		}
		for (int i = 0; i < 12; i++) {
			PED::SET_PED_COMPONENT_VARIATION
			(
				ped,
				i,
				PED::GET_PED_DRAWABLE_VARIATION(target, i),
				PED::GET_PED_TEXTURE_VARIATION(target, i),
				PED::GET_PED_PALETTE_VARIATION(target, i)
			);
		}
	}

	inline void steal_identity(const Ped target)
	{
		const int max_health = ENTITY::GET_ENTITY_MAX_HEALTH(self::ped);
		const int current_health = ENTITY::GET_ENTITY_HEALTH(self::ped);
		const int current_armor = PED::GET_PED_ARMOUR(self::ped);

		PLAYER::SET_PLAYER_MODEL(self::id , ENTITY::GET_ENTITY_MODEL(target));
		script::get_current()->yield();
		PED::CLONE_PED_TO_TARGET(target, self::ped);
		ENTITY::SET_ENTITY_MAX_HEALTH(self::ped, max_health);
		ENTITY::SET_ENTITY_HEALTH(self::ped, current_health, 0);
		PED::SET_PED_ARMOUR(self::ped, current_armor);
	}
}