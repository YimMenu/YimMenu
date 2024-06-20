#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "pointers.hpp"
#include "gta_util.hpp"
#include "util/math.hpp"
#include <network/Network.hpp>
#include <network/CCommunications.hpp>

namespace big
{
	void set_peer_id_upper(std::uint64_t upper)
	{
		*g_pointers->m_gta.m_peer_id &= 0xFFFFFFFF;
		*g_pointers->m_gta.m_peer_id |= (upper << 32);

		if (gta_util::get_network()->m_game_session_ptr)
			gta_util::get_network()->m_game_session_ptr->m_local_player.m_player_data.m_peer_id = *g_pointers->m_gta.m_peer_id;
		if (gta_util::get_network()->m_transition_session_ptr)
			gta_util::get_network()->m_transition_session_ptr->m_local_player.m_player_data.m_peer_id = *g_pointers->m_gta.m_peer_id;

		g_pointers->m_gta.m_profile_gamer_info->m_peer_id                                          = *g_pointers->m_gta.m_peer_id;
		g_pointers->m_gta.m_player_info_gamer_info->m_peer_id = *g_pointers->m_gta.m_peer_id;
		(*g_pointers->m_gta.m_communications)->m_voice.m_connections[0]->m_gamer_info.m_peer_id = *g_pointers->m_gta.m_peer_id;

		if (g_local_player && g_local_player->m_player_info)
			g_local_player->m_player_info->m_net_player_data.m_peer_id = *g_pointers->m_gta.m_peer_id;
	}

	void set_host_token(std::uint64_t token)
	{
		*g_pointers->m_gta.m_host_token = token;

		if (gta_util::get_network()->m_game_session_ptr)
			gta_util::get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token = token;
		if (gta_util::get_network()->m_transition_session_ptr)
			gta_util::get_network()->m_transition_session_ptr->m_local_player.m_player_data.m_host_token = token;

		g_pointers->m_gta.m_profile_gamer_info->m_host_token                                       = token;
		g_pointers->m_gta.m_player_info_gamer_info->m_host_token                                   = token;
		(*g_pointers->m_gta.m_communications)->m_voice.m_connections[0]->m_gamer_info.m_host_token = token;

		if (g_local_player && g_local_player->m_player_info)
			g_local_player->m_player_info->m_net_player_data.m_host_token = token;


		set_peer_id_upper(token >> 32);
	}

	class spoof_host_token_internal : looped_command
	{ 
		using looped_command::looped_command;

		virtual void on_enable() override
		{
			g.session.original_host_token = *g_pointers->m_gta.m_host_token;
		}

		virtual void on_tick() override
		{
			if (g.session.spoof_host_token_dirty && gta_util::get_network()->m_game_session_state == 0)
			{
				switch (g.session.spoof_host_token_type)
				{
				case 0: // Disabled
				{
					set_host_token(g.session.original_host_token);
					break;
				}
				case 1: // Legit
				{
					std::uint64_t rand_upper = math::rand(20, 230);
					set_host_token(((g.session.original_host_token) & 0xFFFFFFFF) | (rand_upper << 32));
					break;
				}
				case 2: // Aggressive
				{
					set_host_token(math::rand(10, 1000));
					break;
				}
				case 3: // Very aggressive
				{
					set_host_token(0);
					break;
				}
				case 4: // Custom
				{
					set_host_token(g.session.custom_host_token);
					break;
				}
				}
				g.session.spoof_host_token_dirty = false;
			}
		}

		virtual void on_disable() override
		{
			if (g.session.original_host_token)
				set_host_token(g.session.original_host_token);
		}
	};

	static bool true_ref = true;
	spoof_host_token_internal g_spoof_host_token_internal("$$spoofhosttoken", "", "", true_ref);
}