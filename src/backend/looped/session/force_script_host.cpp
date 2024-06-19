#include "backend/looped/looped.hpp"
#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "gta_util.hpp"
#include "gta/script_handler.hpp"
#include "gta/net_array.hpp"
#include "packet.hpp"

namespace big
{
	void looped::session_force_script_host()
	{
		if (!g.session.force_script_host)
			return;

		static bool loaded_into_session = false;

		if (!*g_pointers->m_gta.m_is_session_started)
		{
			loaded_into_session = false;
			return;
		}

		if (!loaded_into_session)
		{
			if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("maintransition"_J) == 0) [[unlikely]]
			{
				if (auto freemode = gta_util::find_script_thread("freemode"_J); freemode && freemode->m_net_component)
				{
					auto net_component = reinterpret_cast<CGameScriptHandlerNetComponent*>(freemode->m_net_component);
					int num_synced_arrays = 0;

					for (int i = 0; i < net_component->m_host_array_count; i++)
					{
						if ((g_pointers->m_gta.m_get_host_array_handler_by_index(net_component, i)->m_flags & 1) != 0)
							num_synced_arrays++;
					}

					if (num_synced_arrays == net_component->m_host_array_count)
					{
						net_component->do_host_migration(g_player_service->get_self()->get_net_game_player(), 0xFFFF, true);

						packet pack;
						pack.write_message(rage::eNetMessage::MsgScriptVerifyHostAck);
						net_component->m_script_handler->get_id()->serialize(&pack.m_buffer);
						pack.write<bool>(true, 1);
						pack.write<bool>(true, 1);
						pack.write<std::uint16_t>(0xFFFF, 16);

						for (auto& player : g_player_service->players())
						{
							if (player.second->get_net_game_player())
								pack.send(player.second->get_net_game_player()->m_msg_id);
						}

						loaded_into_session = true;
					}
				}
			}
		}
	}
}
