#pragma once
#include "natives.hpp"
#include "script.hpp"
#include "pointers.hpp"
#include "entity.hpp"

namespace big::ped
{
	inline bool change_player_model(const Hash hash)
	{
		for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
		{
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}
		if (!STREAMING::HAS_MODEL_LOADED(hash))
		{
			return false;
		}
		PLAYER::SET_PLAYER_MODEL(self::id, hash);
		script::get_current()->yield();
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

		return true;
	}

	inline bool steal_outfit(const Ped target)
	{
		Ped ped = self::ped;
		
		if (ENTITY::GET_ENTITY_MODEL(ped) != ENTITY::GET_ENTITY_MODEL(target)) {
			return false;
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

		return true;
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

	inline Ped spawn(ePedType pedType, Hash hash, Hash clone, Vector3 location, float heading, bool is_networked = true)
	{
		for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
		{
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}

		if (!STREAMING::HAS_MODEL_LOADED(hash))
		{
			return 0;
		}

		*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
		auto ped = PED::CREATE_PED(pedType, hash, location.x, location.y, location.z, heading, is_networked, false);
		*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

		script::get_current()->yield();

		if (clone)
		{
			PED::CLONE_PED_TO_TARGET(clone, ped);
		}

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

		return ped;
	}

	inline void play_animation(Ped target, const char* anim_dictionary, const char* anim_name, int flag = ANIM_FLAG_NORMAL)
	{
		if (!entity::take_control_of(target))
		{
			g_notification_service->push_warning("Animation", "Failed to take control of target.");
			return;
		}
		size_t count = 0;
		do {
			STREAMING::REQUEST_ANIM_DICT(anim_dictionary);
			if (count++ == 100)
			{
				g_notification_service->push_warning("Animation", "Failed to request anim dict.");
				return;
			}
			script::get_current()->yield();
		} while (!STREAMING::HAS_ANIM_DICT_LOADED(anim_dictionary));
		TASK::TASK_PLAY_ANIM(target, anim_dictionary, anim_name, 8.0f, 0.0f, -1, flag, 0, false, false, false);
		g_notification_service->push("Animation", "Play animation success.");
	}
}