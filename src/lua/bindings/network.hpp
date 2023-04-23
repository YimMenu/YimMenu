#pragma once
#include "pointers.hpp"
#include "util/teleport.hpp"

namespace lua::network
{
	// https://stackoverflow.com/a/40777268
	/**
	* Convert a Lua sequence into a C++ vector
	* Throw exception on errors or wrong types
	*/
	template<typename elementType>
	inline std::vector<elementType> convert_sequence(sol::table t)
	{
		std::size_t sz = t.size();
		std::vector<elementType> res(sz);
		for (int i = 1; i <= sz; i++)
		{
			res[i - 1] = t[i];
		}
		return res;
	}

	static void trigger_script_event(int bitset, sol::table _args)
	{
		auto args = convert_sequence<int64_t>(_args);

		if (args.size() >= 1)
			args[1] = self::id;

		big::g_pointers->m_gta.m_trigger_script_event(1, args.data(), args.size(), bitset);
	}

	static void give_pickup_rewards(int player, int reward)
	{
		big::g_pointers->m_gta.m_give_pickup_rewards(1 << player, reward);
	}

	static void set_player_coords(int player, float x, float y, float z)
	{
		big::teleport::teleport_player_to_coords(big::g_player_service->get_by_id(player), {x, y, z});
	}

	static int get_selected_player()
	{
		if (big::g_player_service->get_selected()->is_valid())
			return big::g_player_service->get_selected()->id();

		return -1;
	}

	static void bind(sol::state& state)
	{
		auto ns                    = state["network"].get_or_create<sol::table>();
		ns["trigger_script_event"] = trigger_script_event;
		ns["give_pickup_rewards"]  = give_pickup_rewards;
		ns["set_player_coords"]    = set_player_coords;
		ns["get_selected_player"]  = get_selected_player;
	}
}