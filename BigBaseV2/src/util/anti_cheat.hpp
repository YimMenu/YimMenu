#pragma once
#include <regex>
#include "core/data/levels.hpp"
#include "gta/joaat.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "services/players/player_service.hpp"
#include "services/notifications/notification_service.hpp"

namespace big::anti_cheat
{
	// Godmode Check (skidded)
	inline bool is_in_godmode(Ped player_ped, CPed* player_cped)
	{
		if (player_cped->m_damage_bits & (uint32_t)eEntityProofs::GOD
			&& !INTERIOR::GET_INTERIOR_FROM_ENTITY(player_ped))
		{
			return true;
		}

		return false;
	}

	// Vehicle Godmode Check
	inline bool is_in_godmode_vehicle(CPed* player_cped)
	{
		if (player_cped->m_vehicle != nullptr
			&& player_cped->m_vehicle->m_damage_bits & (uint32_t)eEntityProofs::GOD)
		{
			return true;
		}

		return false;
	}

	// Health Check
	inline bool is_health_normal(Ped player_ped, CPed* player_cped)
	{
		if (player_cped->m_health > 300 || player_cped->m_armor > 300 && PED::GET_PED_DRAWABLE_VARIATION(player_ped, 11) != 186)
			return false;

		return true;
	}

	// Name Check (skidded)
	inline bool is_name_normal(Player player)
	{
		auto cplayer = g_player_service->get_by_id(player);
		const char* name = cplayer->get_name();

		if (sizeof(name) < 6 || sizeof(name) > 16 && !(std::regex_match(name, std::regex("^([a-zA-Z0-9_-]+)$"))))
			return false;

		return true;
	}

	// Frame Flags Check (skidded)
	inline bool is_using_frame_flags(CPlayerInfo* player_info)
	{
		if (player_info->m_frame_flags == (uint32_t)eFrameFlags::eFrameFlagExplosiveAmmo
			|| player_info->m_frame_flags == (uint32_t)eFrameFlags::eFrameFlagExplosiveMelee
			|| player_info->m_frame_flags == (uint32_t)eFrameFlags::eFrameFlagFireAmmo
			|| player_info->m_frame_flags == (uint32_t)eFrameFlags::eFrameFlagSuperJump)
		{
			return true;
		}

		return false;
	}

	// Damage Modifiers Check (skidded)
	inline bool is_using_damage_mods(CPlayerInfo* player_info)
	{
		if (player_info->m_melee_damage_mult > 1.f
			|| player_info->m_melee_weapon_damage_mult > 1.f
			|| player_info->m_weapon_damage_mult != 0.72f)
		{
			return true;
		}

		return false;
	}

	// Movement Modifiers Check (skidded)
	inline bool is_using_movement_mods(CPlayerInfo* player_info)
	{
		if (player_info->m_run_speed > 1.f
			|| player_info->m_swim_speed > 1.f)
		{
			return true;
		}

		return false;
	}

	// Total Cash Check (skidded)
	inline bool is_using_money_mods(Player player)
	{
		int max_legit_cash = 150000000;
		int64_t total_cash = *script_global(1853348).at(player, 834).at(205).at(56).as<int64_t*>();
		if (total_cash >= max_legit_cash) 
		{
			return true;
		}

		return false;
	}
}