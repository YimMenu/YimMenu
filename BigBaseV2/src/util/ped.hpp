#pragma once
#include "natives.hpp"

namespace big::ped
{
	inline void steal_outfit(const Ped target)
	{
		if (ENTITY::GET_ENTITY_MODEL(PLAYER::PLAYER_PED_ID()) != ENTITY::GET_ENTITY_MODEL(target)) {
			g_notification_service->push("Error", "Model mismatch, use steal identity instead.");
			return;
		}
		for (int i = 0; i < 12; i++) {
			PED::SET_PED_COMPONENT_VARIATION
			(
				PLAYER::PLAYER_PED_ID(),
				i,
				PED::GET_PED_DRAWABLE_VARIATION(target, i),
				PED::GET_PED_TEXTURE_VARIATION(target, i),
				PED::GET_PED_PALETTE_VARIATION(target, i)
			);
		}
	}

	inline void steal_identity(const Ped target)
	{
		const int max_health = ENTITY::GET_ENTITY_MAX_HEALTH(PLAYER::PLAYER_PED_ID());
		const int current_health = ENTITY::GET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID());
		const int current_armor = PED::GET_PED_ARMOUR(PLAYER::PLAYER_PED_ID());

		PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), ENTITY::GET_ENTITY_MODEL(target));
		PED::CLONE_PED_TO_TARGET(target, PLAYER::PLAYER_PED_ID());
		ENTITY::SET_ENTITY_MAX_HEALTH(PLAYER::PLAYER_PED_ID(), max_health);
		ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), current_health, 0);
		PED::SET_PED_ARMOUR(PLAYER::PLAYER_PED_ID(), current_armor);
	}
}