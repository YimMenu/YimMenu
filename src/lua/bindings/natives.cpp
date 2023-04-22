#include "natives.hpp"

#include "lua/natives/natives_data.hpp"

// causes include name collision
//#include "util/toxic.hpp"

#include "pointers.hpp"

namespace lua::natives
{
	uint64_t end_call(uint64_t native_hash)
	{
#if 0
		if (native_hash == 0x172AA1B624FA1013)
		{
			big::toxic::explosion_anti_cheat_bypass::m_can_blame_others->apply();
			big::toxic::explosion_anti_cheat_bypass::m_can_use_blocked_explosions->apply();
		}
#endif

		big::g_native_invoker.end_call(native_hash);

#if 0
		if (native_hash == 0x172AA1B624FA1013)
		{
			big::toxic::explosion_anti_cheat_bypass::m_can_blame_others->restore();
			big::toxic::explosion_anti_cheat_bypass::m_can_use_blocked_explosions->restore();
		}
#endif

		if (native_hash == 0xAAA34F8A7CB32098)
		{
			if (auto ped = big::g_pointers->m_gta.m_handle_to_ptr(big::g_native_invoker.m_call_context.get_arg<int>(0)))
				big::g_pointers->m_gta.m_clear_ped_tasks_network((CPed*)ped, true);
		}

		return big::g_native_invoker.get_return_value<uint64_t>();
	}

	void bind(sol::state& state)
	{
		auto ns                 = state["_natives"].get_or_create<sol::table>();
		ns["begin_call"]        = begin_call;
		ns["push_arg"]          = push_arg;
		ns["push_string"]       = push_string;
		ns["push_pointer"]      = push_pointer;
		ns["end_call"]          = end_call;
		ns["get_pointer_value"] = get_pointer_value;

		auto result = state.load_buffer(natives_data, sizeof(natives_data) - 1);
		if (!result.valid())
			LOG(FATAL) << "Failed to load natives data: " << result.get<sol::error>().what();

		result();
	}
}