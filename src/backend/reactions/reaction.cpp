#include "reaction.hpp"

#include "backend/player_command.hpp"
#include "core/data/infractions.hpp"
#include "core/data/network.hpp"
#include "core/settings/session.hpp"
#include "fiber_pool.hpp"
#include "gui.hpp"
#include "script.hpp"
#include "services/bad_players/bad_players.hpp"
#include "services/gui/gui_service.hpp"
#include "services/players/player_service.hpp"
#include "util/notify.hpp"

namespace big
{
	reaction::reaction(const char* event_name, const char* notify_message) :
	    m_event_name(event_name),
	    m_notify_message(notify_message)
	{
	}

	void reaction::process(player_ptr player, bool kick_player, Infraction infraction, bool is_modder, bool is_toxic)
	{
		rage::rlGamerInfo* net_data;

		if (player && player->is_valid() && (net_data = player->get_net_data()))
		{
			auto rockstar_id = net_data->m_gamer_handle.m_rockstar_id;
			auto name        = net_data->m_name;

			if (infraction != Infraction::NONE)
			{
				if (!player->infractions.contains((int)infraction))
					player->infractions.insert((int)infraction);
				// infraction must have been logged/notified before so return. Exception - crash & kick
				else if (infraction != Infraction::TRIED_CRASH_PLAYER && infraction != Infraction::TRIED_KICK_PLAYER)
					return;
			}

			if (infraction == Infraction::TRIED_CRASH_PLAYER)
				++player->crash_count;

			auto str = std::vformat(m_notify_message, std::make_format_args(name));

			if (log)
				LOG(WARNING) << str;

			if (notify)
				g_notification_service->push_warning("Protections", str);

			if (is_modder)
			{
				player->is_modder = true;

				if (!bad_players_nm::does_exist(rockstar_id))
					bad_players_nm::add_player({name, rockstar_id, false, player->is_spammer});
			}
			else if (is_toxic)
				player->is_toxic = true;

			// open player info of attacker
			if (infraction == Infraction::TRIED_CRASH_PLAYER || infraction == Infraction::TRIED_KICK_PLAYER)
			{
				g_gui_service->set_selected(tabs::PLAYER);
				g_player_service->set_selected(player);
			}

			if (kick_player)
			{
				player->timeout();

				// block join
				if (!player->is_blocked)
				{
					player->is_blocked = true;
					bad_players_nm::add_player({name, rockstar_id, true, player->is_spammer});
				}

				if (is_modder)
				{
					if (g_player_service->get_self()->is_host())
					{
						dynamic_cast<player_command*>(command::get(RAGE_JOAAT("hostkick")))->call(player, {});
						return;
					}
					else
						g_fiber_pool->queue_job([player, name] {
							// // man this is heavy!
							// dynamic_cast<player_command*>(command::get(RAGE_JOAAT("multikick")))->call(player, {});

							// try to become host
							if (g_session.force_session_host && g_network.auto_kick_host_when_attacked)
							{
								g_notification_service->push_success("Auto kicking host", std::format(".. to tackle {}", name), true);

								// kick current host
								for (auto& plyr : g_player_service->players())
									if (plyr.second->is_host())
									{
										if (plyr.second->id() != self::id)
											dynamic_cast<player_command*>(command::get(RAGE_JOAAT("multikick")))->call(plyr.second, {});
										return;
									}

								// try to host kick attacker if possible
								dynamic_cast<player_command*>(command::get(RAGE_JOAAT("hostkick")))->call(player, {});
								for (int i = 0; i < 19; i++)
								{
									dynamic_cast<player_command*>(command::get(RAGE_JOAAT("hostkick")))->call(player, {});
									script::get_current()->yield(50ms);
								}
							}
						});
				}
				else
					dynamic_cast<player_command*>(command::get(RAGE_JOAAT("oomkick")))->call(player, {});
			}
		}
	}
}
