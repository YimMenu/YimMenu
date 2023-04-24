#include "network.hpp"

#include "pointers.hpp"
#include "services/player_database/player_database_service.hpp"
#include "util/teleport.hpp"

namespace lua::network
{
	void trigger_script_event(int bitset, sol::table _args)
	{
		auto args = convert_sequence<int64_t>(_args);

		if (args.size() >= 1)
			args[1] = self::id;

		big::g_pointers->m_gta.m_trigger_script_event(1, args.data(), args.size(), bitset);
	}

	void give_pickup_rewards(int player, int reward)
	{
		big::g_pointers->m_gta.m_give_pickup_rewards(1 << player, reward);
	}

	void set_player_coords(int player_idx, float x, float y, float z)
	{
		if (auto player = big::g_player_service->get_by_id(player_idx))
			big::teleport::teleport_player_to_coords(player, {x, y, z});
	}

	int get_selected_player()
	{
		if (big::g_player_service->get_selected()->is_valid())
			return big::g_player_service->get_selected()->id();

		return -1;
	}

	int get_selected_database_player_rockstar_id()
	{
		if (auto pers = big::g_player_database_service->get_selected())
			return pers->rockstar_id;

		return -1;
	}

	void flag_player_as_modder(int player_idx)
	{
		if (auto player = big::g_player_service->get_by_id(player_idx))
		{
			auto pers       = big::g_player_database_service->get_or_create_player(player);
			pers->is_modder = true;
			big::g_player_database_service->save();
			player->is_modder = true;
		}
	}

	bool is_player_flagged_as_modder(int player_idx)
	{
		if (auto player = big::g_player_service->get_by_id(player_idx))
			return player->is_modder;

		return false;
	}
}