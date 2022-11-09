#pragma once
#include <regex>
#include "core/data/levels.hpp"
#include "gta/joaat.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "services/players/player_service.hpp"
#include "services/notifications/notification_service.hpp"
#include "util/player.hpp"

namespace big::anti_cheat
{
	// Godmode Check (skidded)
	inline bool is_in_godmode(Ped player_ped, CPed* player_cped)
	{
		if (player_cped->m_damage_bits & (uint32_t)eEntityProofs::GOD
			&& !INTERIOR::GET_INTERIOR_FROM_ENTITY(player_ped)
			&& player_cped->m_player_info->m_game_state == eGameState::Playing)
		{
			return true;
		}

		return false;
	}

	// Vehicle Godmode Check
	inline bool is_in_godmode_vehicle(Ped player_ped, CPed* player_cped)
	{
		if (player_cped->m_vehicle != nullptr
			&& player_cped->m_vehicle->m_damage_bits & (uint32_t)eEntityProofs::GOD
			&& !INTERIOR::GET_INTERIOR_FROM_ENTITY(player_ped)
			&& player_cped->m_player_info->m_game_state == eGameState::Playing)
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
	inline bool is_name_normal(CPlayerInfo* cplayer_info)
	{
		const char* name = cplayer_info->m_net_player_data.m_name;

		if (sizeof(name) < 6 || sizeof(name) > 16 || !(std::regex_match(name, std::regex("^([a-zA-Z0-9_-]+)$"))))
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
		int max_legit_cash = 100'000'000;
		uint64_t money_bank = util::player::get_player_stat<uint64_t>(player, ePlayerStatType::MoneyAll);
		if (money_bank >= max_legit_cash)
		{
			return true;
		}

		return false;
	}

	// Model Check
	inline bool is_model_normal(CPed* player_cped)
	{
		if (player_cped->m_model_info->m_hash == RAGE_JOAAT("mp_f_freemode_01") || player_cped->m_model_info->m_hash == RAGE_JOAAT("mp_m_freemode_01"))
			return true;

		return false;
	}
}