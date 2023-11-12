#pragma once
#include "entity.hpp"
#include "gta/enums.hpp"
#include "math.hpp"
#include "natives.hpp"
#include "outfit.hpp"
#include "pointers.hpp"
#include "services/players/player_service.hpp"

namespace big::ped
{
	inline void steal_outfit(const Ped target)
	{
		if (ENTITY::GET_ENTITY_MODEL(target) != ENTITY::GET_ENTITY_MODEL(self::ped))
			return;

		for (auto item : outfit::components_t().items)
			if (item.id != 2) // dont apply hair
			{
				auto draw    = PED::GET_PED_DRAWABLE_VARIATION(target, item.id);
				auto texture = PED::GET_PED_TEXTURE_VARIATION(target, item.id);
				auto palette = PED::GET_PED_PALETTE_VARIATION(target, item.id);

				PED::SET_PED_COMPONENT_VARIATION(self::ped, item.id, draw, texture, palette);
			}

		PED::CLEAR_ALL_PED_PROPS(self::ped, 0);

		for (auto& item : outfit::props_t().items)
			PED::SET_PED_PROP_INDEX(self::ped, item.id, PED::GET_PED_PROP_INDEX(target, item.id, 1), PED::GET_PED_PROP_TEXTURE_INDEX(target, item.id), TRUE, 1);
	}

	inline void kill_ped(const Ped ped)
	{
		if (entity::take_control_of(ped, 0))
			ENTITY::SET_ENTITY_HEALTH(ped, 0, self::ped);
		else
		{
			auto ptr = g_pointers->m_gta.m_handle_to_ptr(ped);
			if (!ptr)
				return;

			g_pointers->m_gta.m_send_network_damage(g_player_service->get_self()->get_ped(), ptr, ptr->get_position(), 0, true, RAGE_JOAAT("weapon_explosion"), 10000.0f, 2, 0, (1 << 4), 0, 0, 0, false, false, true, true, nullptr);
		}
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

		auto ped = PED::CREATE_PED(pedType, hash, location.x, location.y, location.z, heading, is_networked, false);

		script::get_current()->yield();

		if (clone)
		{
			PED::CLONE_PED_TO_TARGET(clone, ped);
		}

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

		return ped;
	}

	inline void set_ped_random_component_variation(Ped ped)
	{
		constexpr auto range = [](int lower_bound, int upper_bound) -> int {
			return std::rand() % (upper_bound - lower_bound + 1) + lower_bound;
		};

		outfit::components_t components;

		for (auto& item : components.items)
		{
			int drawable_id_max = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, item.id) - 1;
			if (drawable_id_max == -1)
				continue;
			int drawable_id    = range(0, drawable_id_max);
			int texture_id_max = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, item.id, drawable_id) - 1;
			if (texture_id_max == -1)
				continue;
			int texture_id = range(0, texture_id_max);
			PED::SET_PED_COMPONENT_VARIATION(ped, item.id, drawable_id, texture_id, PED::GET_PED_PALETTE_VARIATION(ped, item.id));
		}
	}

	inline player_ptr get_player_from_ped(Ped ped)
	{
		for (auto& p : g_player_service->players())
		{
			if (p.second->get_ped())
			{
				if (p.second->get_ped() == g_pointers->m_gta.m_handle_to_ptr(ped))
					return p.second;
			}
		}
		return nullptr;
	}

	inline bool load_animation_dict(const char* dict)
	{
		if (STREAMING::HAS_ANIM_DICT_LOADED(dict))
			return true;

		for (uint8_t i = 0; !STREAMING::HAS_ANIM_DICT_LOADED(dict) && i < 35; i++)
		{
			STREAMING::REQUEST_ANIM_DICT(dict);
			script::get_current()->yield();
		}

		return STREAMING::HAS_ANIM_DICT_LOADED(dict);
	}

	inline void ped_play_animation(Ped ped, const std::string_view& animDict, const std::string_view& animName, float speed = 4.f, float speedMultiplier = -4.f, int duration = -1, int flag = 0, float playbackRate = 0, bool lockPos = false, Vector3 pos = {}, Vector3 rot = {}, int ik_flags = 0)
	{
		if (load_animation_dict(animDict.data()))
			if (pos.x == 0 && pos.y == 0 && pos.z == 0)
				TASK::TASK_PLAY_ANIM(ped, animDict.data(), animName.data(), speed, speedMultiplier, duration, flag, playbackRate, lockPos, lockPos, lockPos);
			else
				TASK::TASK_PLAY_ANIM_ADVANCED(ped, animDict.data(), animName.data(), pos.x, pos.y, pos.z, rot.x, rot.y, rot.z, speed, speedMultiplier, duration, flag, playbackRate, lockPos, ik_flags);
	}
}
