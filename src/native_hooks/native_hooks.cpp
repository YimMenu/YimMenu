#include "native_hooks.hpp"

#include "all_scripts.hpp"
#include "am_launcher.hpp"
#include "carmod_shop.hpp"
#include "creator.hpp"
#include "crossmap.hpp"
#include "freemode.hpp"
#include "gta_util.hpp"
#include "network_session_host.hpp"
#include "shop_controller.hpp"
#include "tunables.hpp"

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
		m_program  = program;
		m_vmt_hook = std::make_unique<vmt_hook>(m_program, 9);
		m_vmt_hook->hook(6, &scrprogram_dtor);
		m_vmt_hook->enable();

		m_handler_hook = std::make_unique<vmt_hook>(&m_program->m_native_entrypoints, m_program->m_native_count);
		m_handler_hook->enable();

		std::unordered_map<rage::scrNativeHandler, rage::scrNativeHandler> handler_replacements;

		for (auto& [replacement_hash, replacement_handler] : native_replacements)
		{
			auto native = replacement_hash;
			map_native(&native);

			auto og_handler = g_pointers->m_gta.m_get_native_handler(g_pointers->m_gta.m_native_registration_table, native);
			if (!og_handler)
				continue;

			handler_replacements[og_handler] = replacement_handler;
		}

		for (int i = 0; i < m_program->m_native_count; i++)
		{
			if (auto it = handler_replacements.find((rage::scrNativeHandler)program->m_native_entrypoints[i]);
			    it != handler_replacements.end())
			{
				m_handler_hook->hook(i, it->second);
			}
		}
	}

	void native_hook::scrprogram_dtor(rage::scrProgram* this_, char free_memory)
	{
		if (auto it = g_native_hooks->m_native_hooks.find(this_); it != g_native_hooks->m_native_hooks.end())
		{
			auto og_func = it->second->m_vmt_hook->get_original<decltype(&native_hook::scrprogram_dtor)>(6);
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
		add_native_detour(0x1CA59E306ECB80A5, all_scripts::NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT);
		add_native_detour(0xD1110739EEADB592, all_scripts::NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT);
		add_native_detour(0xADF692B254977C0C, all_scripts::SET_CURRENT_PED_WEAPON);
		add_native_detour(0xFE99B66D079CF6BC, all_scripts::DISABLE_CONTROL_ACTION);
		add_native_detour(0xEB354E5376BC81A7, all_scripts::HUD_FORCE_WEAPON_WHEEL);
		add_native_detour(0x158C16F5E4CF41F8, all_scripts::RETURN_TRUE); // bypass casino country restrictions
		add_native_detour(0xE679E3E06E363892, all_scripts::NETWORK_OVERRIDE_CLOCK_TIME);
		add_native_detour(0x6B76DC1F3AE6E6A3, all_scripts::SET_ENTITY_HEALTH);
		add_native_detour(0x697157CED63F18D4, all_scripts::APPLY_DAMAGE_TO_PED);
		add_native_detour(0x40EB1EFD921822BC, all_scripts::DO_NOTHING); // SECURITY::REGISTER_SCRIPT_VARIABLE
		add_native_detour(0x340A36A700E99699, all_scripts::DO_NOTHING); // SECURITY::UNREGISTER_SCRIPT_VARIABLE
		add_native_detour(0x8E580AB902917360, all_scripts::DO_NOTHING); // SECURITY::FORCE_CHECK_SCRIPT_VARIABLES

		add_native_detour(RAGE_JOAAT("shop_controller"), 0x34616828CD07F1A1, all_scripts::RETURN_FALSE); // prevent exploit reports
		add_native_detour(RAGE_JOAAT("shop_controller"), 0xDC38CC1E35B6A5D7, shop_controller::SET_WARNING_MESSAGE_WITH_HEADER);

		add_native_detour(RAGE_JOAAT("carmod_shop"), 0x06843DA7060A026B, carmod_shop::SET_ENTITY_COORDS);
		add_native_detour(RAGE_JOAAT("carmod_shop"), 0x8E2530AA8ADA980E, carmod_shop::SET_ENTITY_HEADING);
		add_native_detour(RAGE_JOAAT("carmod_shop"), 0x34E710FF01247C5A, carmod_shop::SET_VEHICLE_LIGHTS);
		add_native_detour(RAGE_JOAAT("carmod_shop"), 0x767FBC2AC802EF3D, carmod_shop::STAT_GET_INT);
		add_native_detour(RAGE_JOAAT("carmod_shop"), 0xB3271D7AB655B441, carmod_shop::STAT_SET_INT);
		add_native_detour(RAGE_JOAAT("carmod_shop"), 0x5F4B6931816E599B, carmod_shop::DISABLE_ALL_CONTROL_ACTIONS);

		add_native_detour(RAGE_JOAAT("freemode"), 0x2C83A9DA6BFFC4F9, freemode::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);
		add_native_detour(RAGE_JOAAT("freemode"), 0x767FBC2AC802EF3D, freemode::STAT_GET_INT);
		add_native_detour(RAGE_JOAAT("freemode"), 0x5E9564D8246B909A, freemode::IS_PLAYER_PLAYING);
		add_native_detour(RAGE_JOAAT("freemode"), 0xEA1C610A04DB6BBB, freemode::SET_ENTITY_VISIBLE);
		add_native_detour(RAGE_JOAAT("freemode"), 0x231C8F89D0539D8F, freemode::SET_BIGMAP_ACTIVE);
		add_native_detour(RAGE_JOAAT("freemode"), 0x9029B2F3DA924928, freemode::SET_BLIP_DISPLAY);
		add_native_detour(RAGE_JOAAT("freemode"), 0x5D10B3795F3FC886, freemode::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA);

		add_native_detour(RAGE_JOAAT("fmmc_launcher"), 0x5D10B3795F3FC886, freemode::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA);
		add_native_detour(RAGE_JOAAT("maintransition"), 0x6F3D4ED9BEE4E61D, network::NETWORK_SESSION_HOST);

		add_native_detour(RAGE_JOAAT("am_launcher"), 0xB8BA7F44DF1575E1, am_launcher::START_NEW_SCRIPT_WITH_ARGS);
		add_native_detour(RAGE_JOAAT("am_launcher"), 0x5D10B3795F3FC886, freemode::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA);

		add_native_detour(RAGE_JOAAT("fm_race_creator"), 0x2C83A9DA6BFFC4F9, creator::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);
		add_native_detour(RAGE_JOAAT("fm_capture_creator"), 0x2C83A9DA6BFFC4F9, creator::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);
		add_native_detour(RAGE_JOAAT("fm_deathmatch_creator"), 0x2C83A9DA6BFFC4F9, creator::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);
		add_native_detour(RAGE_JOAAT("fm_lts_creator"), 0x2C83A9DA6BFFC4F9, creator::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);

		add_native_detour(RAGE_JOAAT("fm_race_creator"), 0x9F47B058362C84B5, creator::GET_ENTITY_MODEL);
		add_native_detour(RAGE_JOAAT("fm_capture_creator"), 0x9F47B058362C84B5, creator::GET_ENTITY_MODEL);
		add_native_detour(RAGE_JOAAT("fm_deathmatch_creator"), 0x9F47B058362C84B5, creator::GET_ENTITY_MODEL);
		add_native_detour(RAGE_JOAAT("fm_lts_creator"), 0x9F47B058362C84B5, creator::GET_ENTITY_MODEL);

		// Infinite Model Memory
		add_native_detour(RAGE_JOAAT("fm_race_creator"), 0x3D3D8B3BE5A83D35, creator::GET_USED_CREATOR_BUDGET);
		add_native_detour(RAGE_JOAAT("fm_capture_creator"), 0x3D3D8B3BE5A83D35, creator::GET_USED_CREATOR_BUDGET);
		add_native_detour(RAGE_JOAAT("fm_deathmatch_creator"), 0x3D3D8B3BE5A83D35, creator::GET_USED_CREATOR_BUDGET);
		add_native_detour(RAGE_JOAAT("fm_lts_creator"), 0x3D3D8B3BE5A83D35, creator::GET_USED_CREATOR_BUDGET);
		add_native_detour(RAGE_JOAAT("fm_survival_creator"), 0x3D3D8B3BE5A83D35, creator::GET_USED_CREATOR_BUDGET);

		add_native_detour(RAGE_JOAAT("tuneables_processing"), 0x4EDE34FBADD967A6, tunables::WAIT);
		add_native_detour(RAGE_JOAAT("tuneables_processing"), 0x40FCE03E50E8DBE8, tunables::NETWORK_ACCESS_TUNABLE_INT_HASH);
		add_native_detour(RAGE_JOAAT("tuneables_processing"), 0x697F508861875B42, tunables::NETWORK_ACCESS_TUNABLE_BOOL_MODIFICATION_DETECTION_REGISTRATION_HASH);
		add_native_detour(RAGE_JOAAT("tuneables_processing"), 0x972BC203BBC4C4D5, tunables::NETWORK_ACCESS_TUNABLE_FLOAT_HASH);

		add_native_detour(RAGE_JOAAT("arena_carmod"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("armory_aircraft_carmod"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("base_carmod"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("business_hub_carmod"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("car_meet_carmod"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("carmod_shop"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("fixer_hq_carmod"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("hacker_truck_carmod"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("hangar_carmod"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("juggalo_hideout_carmod"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("personal_carmod_shop"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("tuner_property_carmod"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("clothes_shop_mp"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("gunclub_shop"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("hairdo_shop_mp"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("tattoo_shop"), 0x2208438012482A1A, all_scripts::DO_NOTHING); //Fix jittering weapons.

		for (auto& entry : *g_pointers->m_gta.m_script_program_table)
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

		m_native_registrations.emplace(script_hash, std::vector<native_detour>({{hash, detour}}));
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
			m_native_hooks.emplace(program, std::make_unique<native_hook>(program, native_replacements));
		}
	}
}
