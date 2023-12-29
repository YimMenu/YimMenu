#include "native_hooks.hpp"

#include "invoker/crossmap.hpp"

#include "all_scripts.hpp"
#include "am_launcher.hpp"
#include "carmod_shop.hpp"
#include "creator.hpp"
#include "freemode.hpp"
#include "gta_util.hpp"
#include "network_session_host.hpp"
#include "shop_controller.hpp"
#include "tunables.hpp"

#include <script/scrProgram.hpp>
#include <script/scrProgramTable.hpp>

namespace big
{
	native_hook::native_hook(rage::scrProgram* program, const std::unordered_map<NativeIndex, rage::scrNativeHandler>& native_replacements)
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

	void native_hook::hook_instance(rage::scrProgram* program, const std::unordered_map<NativeIndex, rage::scrNativeHandler>& native_replacements)
	{
		m_program  = program;
		m_vmt_hook = std::make_unique<vmt_hook>(m_program, 9);
		m_vmt_hook->hook(6, &scrprogram_dtor);
		m_vmt_hook->enable();

		m_handler_hook = std::make_unique<vmt_hook>(&m_program->m_native_entrypoints, m_program->m_native_count);
		m_handler_hook->enable();

		std::unordered_map<rage::scrNativeHandler, rage::scrNativeHandler> handler_replacements;

		for (auto& [replacement_index, replacement_handler] : native_replacements)
		{
			auto og_handler = native_invoker::get_handlers()[static_cast<int>(replacement_index)];
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
		add_native_detour(NativeIndex::IS_DLC_PRESENT, all_scripts::IS_DLC_PRESENT);
		add_native_detour(NativeIndex::NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT, all_scripts::NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT);
		add_native_detour(NativeIndex::NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT, all_scripts::NETWORK_TRY_TO_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT);
		add_native_detour(NativeIndex::SET_CURRENT_PED_WEAPON, all_scripts::SET_CURRENT_PED_WEAPON);
		add_native_detour(NativeIndex::DISABLE_CONTROL_ACTION, all_scripts::DISABLE_CONTROL_ACTION);
		add_native_detour(NativeIndex::HUD_FORCE_WEAPON_WHEEL, all_scripts::HUD_FORCE_WEAPON_WHEEL);
		add_native_detour(NativeIndex::NETWORK_CASINO_CAN_BET, all_scripts::RETURN_TRUE); // bypass casino country restrictions
		add_native_detour(NativeIndex::NETWORK_OVERRIDE_CLOCK_TIME, all_scripts::NETWORK_OVERRIDE_CLOCK_TIME);
		add_native_detour(NativeIndex::SET_ENTITY_HEALTH, all_scripts::SET_ENTITY_HEALTH);
		add_native_detour(NativeIndex::APPLY_DAMAGE_TO_PED, all_scripts::APPLY_DAMAGE_TO_PED);
		add_native_detour(NativeIndex::REGISTER_SCRIPT_VARIABLE, all_scripts::DO_NOTHING);
		add_native_detour(NativeIndex::UNREGISTER_SCRIPT_VARIABLE, all_scripts::DO_NOTHING);
		add_native_detour(NativeIndex::FORCE_CHECK_SCRIPT_VARIABLES, all_scripts::DO_NOTHING);

		add_native_detour(RAGE_JOAAT("shop_controller"), NativeIndex::IS_PED_SHOOTING, all_scripts::RETURN_FALSE); // prevent exploit reports
		add_native_detour(RAGE_JOAAT("shop_controller"), NativeIndex::SET_WARNING_MESSAGE_WITH_HEADER, shop_controller::SET_WARNING_MESSAGE_WITH_HEADER);

		add_native_detour(RAGE_JOAAT("carmod_shop"), NativeIndex::SET_ENTITY_COORDS, carmod_shop::SET_ENTITY_COORDS);
		add_native_detour(RAGE_JOAAT("carmod_shop"), NativeIndex::SET_ENTITY_HEADING, carmod_shop::SET_ENTITY_HEADING);
		add_native_detour(RAGE_JOAAT("carmod_shop"), NativeIndex::SET_VEHICLE_LIGHTS, carmod_shop::SET_VEHICLE_LIGHTS);
		add_native_detour(RAGE_JOAAT("carmod_shop"), NativeIndex::STAT_GET_INT, carmod_shop::STAT_GET_INT);
		add_native_detour(RAGE_JOAAT("carmod_shop"), NativeIndex::STAT_SET_INT, carmod_shop::STAT_SET_INT);
		add_native_detour(RAGE_JOAAT("carmod_shop"), NativeIndex::DISABLE_ALL_CONTROL_ACTIONS, carmod_shop::DISABLE_ALL_CONTROL_ACTIONS);

		add_native_detour(RAGE_JOAAT("freemode"), NativeIndex::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH, freemode::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);
		add_native_detour(RAGE_JOAAT("freemode"), NativeIndex::STAT_GET_INT, freemode::STAT_GET_INT);
		add_native_detour(RAGE_JOAAT("freemode"), NativeIndex::IS_PLAYER_PLAYING, freemode::IS_PLAYER_PLAYING);
		add_native_detour(RAGE_JOAAT("freemode"), NativeIndex::SET_ENTITY_VISIBLE, freemode::SET_ENTITY_VISIBLE);
		add_native_detour(RAGE_JOAAT("freemode"), NativeIndex::SET_BIGMAP_ACTIVE, freemode::SET_BIGMAP_ACTIVE);
		add_native_detour(RAGE_JOAAT("freemode"), NativeIndex::SET_BLIP_DISPLAY, freemode::SET_BLIP_DISPLAY);
		add_native_detour(RAGE_JOAAT("freemode"), NativeIndex::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA, freemode::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA);

		add_native_detour(RAGE_JOAAT("fmmc_launcher"), NativeIndex::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA, freemode::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA);
		add_native_detour(RAGE_JOAAT("maintransition"), NativeIndex::NETWORK_SESSION_HOST, network::NETWORK_SESSION_HOST);

		add_native_detour(RAGE_JOAAT("am_launcher"), NativeIndex::START_NEW_SCRIPT_WITH_ARGS, am_launcher::START_NEW_SCRIPT_WITH_ARGS);
		add_native_detour(RAGE_JOAAT("am_launcher"), NativeIndex::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA, freemode::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA);

		add_native_detour(RAGE_JOAAT("fm_race_creator"), NativeIndex::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH, creator::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);
		add_native_detour(RAGE_JOAAT("fm_capture_creator"), NativeIndex::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH, creator::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);
		add_native_detour(RAGE_JOAAT("fm_deathmatch_creator"), NativeIndex::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH, creator::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);
		add_native_detour(RAGE_JOAAT("fm_lts_creator"), NativeIndex::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH, creator::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH);

		add_native_detour(RAGE_JOAAT("fm_race_creator"), NativeIndex::GET_ENTITY_MODEL, creator::GET_ENTITY_MODEL);
		add_native_detour(RAGE_JOAAT("fm_capture_creator"), NativeIndex::GET_ENTITY_MODEL, creator::GET_ENTITY_MODEL);
		add_native_detour(RAGE_JOAAT("fm_deathmatch_creator"), NativeIndex::GET_ENTITY_MODEL, creator::GET_ENTITY_MODEL);
		add_native_detour(RAGE_JOAAT("fm_lts_creator"), NativeIndex::GET_ENTITY_MODEL, creator::GET_ENTITY_MODEL);

		// Infinite Model Memory
		add_native_detour(RAGE_JOAAT("fm_race_creator"), NativeIndex::GET_USED_CREATOR_BUDGET, creator::GET_USED_CREATOR_BUDGET);
		add_native_detour(RAGE_JOAAT("fm_capture_creator"), NativeIndex::GET_USED_CREATOR_BUDGET, creator::GET_USED_CREATOR_BUDGET);
		add_native_detour(RAGE_JOAAT("fm_deathmatch_creator"), NativeIndex::GET_USED_CREATOR_BUDGET, creator::GET_USED_CREATOR_BUDGET);
		add_native_detour(RAGE_JOAAT("fm_lts_creator"), NativeIndex::GET_USED_CREATOR_BUDGET, creator::GET_USED_CREATOR_BUDGET);
		add_native_detour(RAGE_JOAAT("fm_survival_creator"), NativeIndex::GET_USED_CREATOR_BUDGET, creator::GET_USED_CREATOR_BUDGET);

		add_native_detour(RAGE_JOAAT("tuneables_processing"), NativeIndex::WAIT, tunables::WAIT);
		add_native_detour(RAGE_JOAAT("tuneables_processing"), NativeIndex::NETWORK_ACCESS_TUNABLE_INT_HASH, tunables::NETWORK_ACCESS_TUNABLE_INT_HASH);
		add_native_detour(RAGE_JOAAT("tuneables_processing"), NativeIndex::NETWORK_ACCESS_TUNABLE_BOOL_MODIFICATION_DETECTION_REGISTRATION_HASH, tunables::NETWORK_ACCESS_TUNABLE_BOOL_MODIFICATION_DETECTION_REGISTRATION_HASH);
		add_native_detour(RAGE_JOAAT("tuneables_processing"), NativeIndex::NETWORK_ACCESS_TUNABLE_FLOAT_HASH, tunables::NETWORK_ACCESS_TUNABLE_FLOAT_HASH);

		// TODO: is this safe?
		add_native_detour(RAGE_JOAAT("arena_carmod"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("armory_aircraft_carmod"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("base_carmod"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("business_hub_carmod"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("car_meet_carmod"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("carmod_shop"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("fixer_hq_carmod"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("hacker_truck_carmod"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("hangar_carmod"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("juggalo_hideout_carmod"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("personal_carmod_shop"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("tuner_property_carmod"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("clothes_shop_mp"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("gunclub_shop"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("hairdo_shop_mp"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.
		add_native_detour(RAGE_JOAAT("tattoo_shop"), NativeIndex::FORCE_PED_AI_AND_ANIMATION_UPDATE, all_scripts::DO_NOTHING); //Fix jittering weapons.

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

	void native_hooks::add_native_detour(NativeIndex index, rage::scrNativeHandler detour)
	{
		add_native_detour(ALL_SCRIPT_HASH, index, detour);
	}

	void native_hooks::add_native_detour(rage::joaat_t script_hash, NativeIndex index, rage::scrNativeHandler detour)
	{
		if (const auto& it = m_native_registrations.find(script_hash); it != m_native_registrations.end())
		{
			it->second.emplace_back(index, detour);
			return;
		}

		m_native_registrations.emplace(script_hash, std::vector<native_detour>({{index, detour}}));
	}

	void native_hooks::hook_program(rage::scrProgram* program)
	{
		std::unordered_map<NativeIndex, rage::scrNativeHandler> native_replacements;
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
