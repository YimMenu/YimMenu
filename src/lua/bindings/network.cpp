#include "network.hpp"

#include "hooking.hpp"
#include "pointers.hpp"
#include "services/player_database/player_database_service.hpp"
#include "util/notify.hpp"
#include "util/scripts.hpp"
#include "util/system.hpp"
#include "util/teleport.hpp"

namespace lua::network
{
	void trigger_script_event(int bitset, sol::table _args)
	{
		auto args = convert_sequence<int32_t>(_args);

		if (args.size() >= 1)
			args[1] = self::id;

		std::vector<std::int64_t> actual_args;

		for (auto arg : args)
			actual_args.push_back((uint32_t)arg);

		big::g_pointers->m_gta.m_trigger_script_event(1, actual_args.data(), actual_args.size(), bitset);
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

	void set_all_player_coords(float x, float y, float z)
	{
		for (auto& player : big::g_player_service->players())
			big::g_fiber_pool->queue_job([player, x, y, z]() {
				big::teleport::teleport_player_to_coords(player.second, {x, y, z});
			});
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

	void force_script_host(const std::string& script_name)
	{
		big::scripts::force_host(rage::joaat(script_name));
	}

	void send_chat_message(const std::string& msg, bool team_only)
	{
		big::g_fiber_pool->queue_job([msg, team_only] {
			if (big::g_hooking->get_original<big::hooks::send_chat_message>()(*big::g_pointers->m_gta.m_send_chat_ptr,
			        big::g_player_service->get_self()->get_net_data(),
			        (char*)msg.c_str(),
			        team_only))
				big::notify::draw_chat((char*)msg.data(), big::g_player_service->get_self()->get_name(), team_only);
		});
	}
}