#include "native_hooks.hpp"
#include "all_scripts.hpp"
#include "carmod_shop.hpp"
#include "freemode.hpp"
#include "maintransition.hpp"
#include "gta_util.hpp"
#include "shop_controller.hpp"
#include "am_launcher.hpp"
#include "creator.hpp"
#include "crossmap.hpp"

#include <script/scrProgram.hpp>
#include <script/scrProgramTable.hpp>

namespace big
{
	static bool map_native(rage::scrNativeHash* hash)
	{
		for (auto const& mapping : g_crossmap)
		{
			if (mapping.first == *hash)
			{
				*hash = mapping.second;
				return true;
			}
		}

		return false;
	}

	native_hook::native_hook(rage::scrProgram* program, const std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler>& native_replacements)
	{
		hook_instance(program, native_replacements);
	}

	native_hook::~native_hook()
	{
		if (m_handler_hook)
		{
			m_handler_hook->disable();
			m_handler_hook.reset();
		}

		if (m_vmt_hook)
		{
			m_vmt_hook->disable();
			m_vmt_hook.reset();
		}
	}

	void native_hook::hook_instance(rage::scrProgram* program, const std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler>& native_replacements)
	{
		m_program = program;
		m_vmt_hook = std::make_unique<vmt_hook>(m_program, 3);
		m_vmt_hook->hook(0, &scrprogram_dtor);
		m_vmt_hook->enable();

		m_handler_hook = std::make_unique<vmt_hook>(&m_program->m_native_entrypoints, m_program->m_native_count);
		m_handler_hook->enable();

		std::unordered_map<rage::scrNativeHandler, rage::scrNativeHandler> handler_replacements;

		for (auto& [replacement_hash, replacement_handler] : native_replacements)
		{
			auto native = replacement_hash;
			map_native(&native);

			auto og_handler = g_pointers->m_get_native_handler(g_pointers->m_native_registration_table, native);
			if (!og_handler)
				continue;

			handler_replacements[og_handler] = replacement_handler;
		}

		for (int i = 0; i < m_program->m_native_count; i++)
		{
			if (auto it = handler_replacements.find((rage::scrNativeHandler)program->m_native_entrypoints[i]); it != handler_replacements.end())
			{
				m_handler_hook->hook(i, it->second);
			}
		}
	}

	void native_hook::scrprogram_dtor(rage::scrProgram* this_, char free_memory)
	{
		if (auto it = g_native_hooks->m_native_hooks.find(this_); it != g_native_hooks->m_native_hooks.end())
		{
			auto og_func = it->second->m_vmt_hook->get_original<decltype(&native_hook::scrprogram_dtor)>(0);
			it->second->m_vmt_hook->disable();
			it->second->m_vmt_hook.reset();
			it->second->m_handler_hook->disable();
			it->second->m_handler_hook.reset();
			g_native_hooks->m_native_hooks.erase(it);
			og_func(this_, free_memory);
		}
		else
		{
			LOG(FATAL) << "Cannot find hook for program";
		}
	}

	constexpr auto ALL_SCRIPT_HASH = RAGE_JOAAT("ALL_SCRIPTS");

	native_hooks::native_hooks()
	{
		add_native_detour(0x812595A0644CE1DE, all_scripts::IS_DLC_PRESENT);
		add_native_detour(0x95914459A87EBA28, all_scripts::NETWORK_BAIL);
		add_native_detour(0x6BFB12CE158E3DD4, all_scripts::SC_TRANSITION_NEWS_SHOW); // Stops news.
		add_native_detour(0xFE4C1D0D3B9CC17E, all_scripts::SC_TRANSITION_NEWS_SHOW_TIMED); // Stops news.
		add_native_detour(0x5D10B3795F3FC886, all_scripts::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA); // Fast join
		add_native_detour(0xAAA34F8A7CB32098, all_scripts::CLEAR_PED_TASKS_IMMEDIATELY); // Clear tasks log.

		add_native_detour(0x1CA59E306ECB80A5, all_scripts::NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT);
		add_native_detour(0xD1110739EEADB592, all_scripts::NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT);

		add_native_detour(RAGE_JOAAT("carmod_shop"), 0x06843DA7060A026B, carmod_shop::SET_ENTITY_COORDS);
		add_native_detour(RAGE_JOAAT("carmod_shop"), 0x8E2530AA8ADA980E, carmod_shop::SET_ENTITY_HEADING);
		add_native_detour(RAGE_JOAAT("carmod_shop"), 0x34E710FF01247C5A, carmod_shop::SET_VEHICLE_LIGHTS);
		add_native_detour(RAGE_JOAAT("carmod_shop"), 0x767FBC2AC802EF3D, carmod_shop::STAT_GET_INT);
		add_native_detour(RAGE_JOAAT("maintransition"), 0x6F3D4ED9BEE4E61D, maintransition::NETWORK_SESSION_HOST); // RID Joiner from https://github.com/YimMenu/YimMenu/issues/172
		add_native_detour(RAGE_JOAAT("maintransition"), 0x933BBEEB8C61B5F4, maintransition::IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED); // This hook lets you stop player-switch in "Pre-HUD Checks"
		add_native_detour(RAGE_JOAAT("maintransition"), 0x06843DA7060A026B, maintransition::SET_ENTITY_COORDS);  // Prevents the game from teleporting you
		add_native_detour(RAGE_JOAAT("maintransition"), 0x1A9205C1B9EE827F, maintransition::SET_ENTITY_COLLISION); // Prevents you from falling
		add_native_detour(RAGE_JOAAT("maintransition"), 0xEA1C610A04DB6BBB, maintransition::SET_ENTITY_VISIBLE);  // Makes you visible
		add_native_detour(RAGE_JOAAT("maintransition"), 0x8D32347D6D4C40A2, maintransition::SET_PLAYER_CONTROL); // Allows controll in session switch
		add_native_detour(RAGE_JOAAT("maintransition"), 0x428CA6DBD1094446, maintransition::FREEZE_ENTITY_POSITION); // Allows controll in session switch
		add_native_detour(RAGE_JOAAT("maintransition"), 0x198F77705FA0931D, maintransition::SET_FOCUS_ENTITY); // Prevets map from unloading.
		add_native_detour(RAGE_JOAAT("maintransition"), 0x719FF505F097FD20, maintransition::HIDE_HUD_AND_RADAR_THIS_FRAME); // Draw hud and radar in transition. (Doesn't work.)
		add_native_detour(RAGE_JOAAT("maintransition"), 0xEF01D36B9C9D0C7B, maintransition::ACTIVATE_FRONTEND_MENU); // Let's you controll your ped when going sp to mp.
		add_native_detour(RAGE_JOAAT("maintransition"), 0x10706DC6AD2D49C0, maintransition::RESTART_FRONTEND_MENU); // Let's you controll your ped when going sp to mp.
		add_native_detour(RAGE_JOAAT("maintransition"), 0xDFC252D8A3E15AB7, maintransition::TOGGLE_PAUSED_RENDERPHASES); // Prevents the game from freezing your screen.
		add_native_detour(RAGE_JOAAT("maintransition"), 0xEA23C49EAA83ACFB, maintransition::NETWORK_RESURRECT_LOCAL_PLAYER); // Prevents player from teleporting after switch.
		add_native_detour(RAGE_JOAAT("freemode"), 0x5E9564D8246B909A, freemode::IS_PLAYER_PLAYING);
		add_native_detour(RAGE_JOAAT("freemode"), 0xEA1C610A04DB6BBB, freemode::SET_ENTITY_VISIBLE);
		add_native_detour(RAGE_JOAAT("freemode"), 0x231C8F89D0539D8F, freemode::SET_BIGMAP_ACTIVE);
		add_native_detour(RAGE_JOAAT("freemode"), 0x9029B2F3DA924928, freemode::SET_BLIP_DISPLAY);
		add_native_detour(RAGE_JOAAT("shop_controller"), 0xDC38CC1E35B6A5D7, shop_controller::SET_WARNING_MESSAGE_WITH_HEADER);
		add_native_detour(RAGE_JOAAT("am_launcher"), 0xB8BA7F44DF1575E1, am_launcher::START_NEW_SCRIPT_WITH_ARGS);

		add_native_detour(RAGE_JOAAT("fm_race_creator"), 0x2C83A9DA6BFFC4F9, creator::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);
		add_native_detour(RAGE_JOAAT("fm_capture_creator"), 0x2C83A9DA6BFFC4F9, creator::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);
		add_native_detour(RAGE_JOAAT("fm_deathmatch_creator"), 0x2C83A9DA6BFFC4F9, creator::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);
		add_native_detour(RAGE_JOAAT("fm_lts_creator"), 0x2C83A9DA6BFFC4F9, creator::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);

		add_native_detour(RAGE_JOAAT("fm_race_creator"), 0x9F47B058362C84B5, creator::GET_ENTITY_MODEL);
		add_native_detour(RAGE_JOAAT("fm_capture_creator"), 0x9F47B058362C84B5, creator::GET_ENTITY_MODEL);
		add_native_detour(RAGE_JOAAT("fm_deathmatch_creator"), 0x9F47B058362C84B5, creator::GET_ENTITY_MODEL);
		add_native_detour(RAGE_JOAAT("fm_lts_creator"), 0x9F47B058362C84B5, creator::GET_ENTITY_MODEL);

		for (auto& entry : *g_pointers->m_script_program_table)
			if (entry.m_program)
				hook_program(entry.m_program);

		g_native_hooks = this;
	}

	native_hooks::~native_hooks()
	{
		m_native_hooks.clear();
		g_native_hooks = nullptr;
	}

	void native_hooks::add_native_detour(rage::scrNativeHash hash, rage::scrNativeHandler detour)
	{
		add_native_detour(ALL_SCRIPT_HASH, hash, detour);
	}

	void native_hooks::add_native_detour(rage::joaat_t script_hash, rage::scrNativeHash hash, rage::scrNativeHandler detour)
	{
		if (const auto& it = m_native_registrations.find(script_hash); it != m_native_registrations.end())
		{
			it->second.emplace_back(hash, detour);
			return;
		}

		m_native_registrations.emplace(script_hash, std::vector<native_detour>({ { hash, detour } }));
	}

	void native_hooks::hook_program(rage::scrProgram* program)
	{
		std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> native_replacements;
		const auto script_hash = program->m_name_hash;

		// Functions that need to be detoured for all scripts
		if (const auto& pair = m_native_registrations.find(ALL_SCRIPT_HASH); pair != m_native_registrations.end())
			for (const auto& native_hook_reg : pair->second)
				native_replacements.insert(native_hook_reg);

		// Functions that only need to be detoured for a specific script
		if (const auto& pair = m_native_registrations.find(script_hash); pair != m_native_registrations.end())
			for (const auto& native_hook_reg : pair->second)
				native_replacements.insert(native_hook_reg);

		if (!native_replacements.empty())
		{
			m_native_hooks.emplace(
				program,
				std::make_unique<native_hook>(program, native_replacements)
			);
		}
	}
}
