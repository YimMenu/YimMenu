#pragma once
#include "core/scr_globals.hpp"
#include "fiber_pool.hpp"
#include "gta/script_handler.hpp"
#include "gta_util.hpp"
#include "misc.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "script_local.hpp"
#include "services/notifications/notification_service.hpp"
#include "services/players/player_service.hpp"

#include <memory/pattern.hpp>

namespace big::scripts
{
	inline bool is_loaded(int hash)
	{
		return SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(hash);
	}

	inline bool is_running(int hash)
	{
		return SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(hash) > 0;
	}

	inline void request_script(int hash)
	{
		SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(hash);
	}

	inline int start_script_with_args(int hash, int* args, int arg_size, int stack_size)
	{
		int thread_id = SYSTEM::START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(hash, args, arg_size, stack_size);
		SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(hash);
		return thread_id;
	}

	inline bool wait_till_loaded(int hash)
	{
		if (is_loaded(hash))
			return true;
		for (int i = 0; i < 150 && !is_loaded(hash); i++)
			script::get_current()->yield(10ms);
		if (is_loaded(hash))
			return true;
		return false;
	}

	inline bool wait_till_running(int hash)
	{
		if (is_running(hash))
			return true;
		for (int i = 0; i < 150 && !is_running(hash); i++)
			script::get_current()->yield(10ms);
		if (is_running(hash))
			return true;
		return false;
	}

	inline bool force_migration(rage::joaat_t hash)
	{
		if (auto launcher = gta_util::find_script_thread(hash); launcher && launcher->m_net_component)
		{
			for (int i = 0; !((CGameScriptHandlerNetComponent*)launcher->m_net_component)->is_local_player_host(); i++)
			{
				if (i > 200)
					return false;

				((CGameScriptHandlerNetComponent*)launcher->m_net_component)
				    ->send_host_migration_event(g_player_service->get_self()->get_net_game_player());
				script::get_current()->yield(10ms);

				if (!launcher->m_stack || !launcher->m_net_component)
					return false;
			}
		}

		return true;
	}

	inline void force_script_host(bool toggle)
	{
		if (toggle)
			force_migration(RAGE_JOAAT("freemode"));

		if (auto script = gta_util::find_script_thread(RAGE_JOAAT("freemode")); script && script->m_net_component)
			((CGameScriptHandlerNetComponent*)script->m_net_component)->block_host_migration(toggle);
	}

	inline const std::optional<uint32_t> get_code_location_by_pattern(rage::scrProgram* program, const memory::pattern& pattern)
	{
		uint32_t code_size = program->m_code_size;
		for (uint32_t i = 0; i < (code_size - pattern.m_bytes.size()); i++)
		{
			for (uint32_t j = 0; j < pattern.m_bytes.size(); j++)
				if (pattern.m_bytes[j].has_value())
					if (pattern.m_bytes[j].value() != *program->get_code_address(i + j))
						goto incorrect;

			return i;
		incorrect:
			continue;
		}

		return std::nullopt;
	}
}