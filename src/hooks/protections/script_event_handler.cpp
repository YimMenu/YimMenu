#include "backend/player_command.hpp"
#include "gta/net_game_event.hpp"
#include "gta/script_handler.hpp"
#include "gta_util.hpp"
#include "hooking.hpp"
#include "util/session.hpp"

#include <network/CNetGamePlayer.hpp>
#include <network/Network.hpp>
#include <script/globals/GPBD_FM_3.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	void format_string(std::string_view player_name, std::string_view protection_type, bool should_log, bool should_notify)
	{
		if (should_log)
			LOG(WARNING) << "BLOCKED_SCRIPT_EVENT From: " << player_name << " Event Type: " << protection_type;

		if (should_notify)
			g_notification_service->push_warning("Script Event Protection",
			    std::format("From: {}\nEvent Type: {}", player_name.data(), protection_type.data()));
	}

	inline bool is_player_driver_of_local_vehicle(Player sender)
	{
		auto plyr = g_player_service->get_by_id(sender);

		if (!plyr || !plyr->get_current_vehicle() || !g_player_service->get_self()->get_current_vehicle())
			return false;

		return g_player_service->get_self()->get_current_vehicle()->m_driver == plyr->get_ped();
	}

	inline bool is_player_our_goon(Player sender)
	{
		auto& boss_goon = scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[self::id].BossGoon;

		if (boss_goon.Boss != self::id)
			return false;

		for (int i = 0; i < boss_goon.Goons.Size; i++)
		{
			if (boss_goon.Goons[i] == sender)
			{
				return true;
			}
		}

		return false;
	}

	bool hooks::scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player)
	{
		const auto args = scripted_game_event->m_args;

		const auto hash        = static_cast<eRemoteEvent>(args[0]);
		const auto player_name = player->get_name();

		auto plyr = g_player_service->get_by_id(player->m_player_id);

		switch (hash)
		{
		case eRemoteEvent::Bounty:
			if (g.protections.script_events.bounty && args[2] == self::id)
			{
				g.reactions.bounty.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::CeoKick:
			if (player->m_player_id != scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[self::id].BossGoon.Boss)
			{
				g.reactions.ceo_kick.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::CeoMoney:
			if (g.protections.script_events.ceo_money
			    && player->m_player_id != scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[self::id].BossGoon.Boss)
			{
				g.reactions.ceo_money.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::ClearWantedLevel:
			if (g.protections.script_events.clear_wanted_level && !is_player_driver_of_local_vehicle(player->m_player_id))
			{
				g.reactions.clear_wanted_level.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::Crash: g.reactions.crash.process(plyr); return true;
		case eRemoteEvent::Crash2:
			if (args[2] > 32)// actual crash condition is if args[2] is above 255
			{
				g.reactions.crash.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::Crash3:
		{
			if (isnan(*(float*)&args[3]) || isnan(*(float*)&args[4]))
			{
				g.reactions.crash.process(plyr);
				return true;
			}
			break;
		}
		case eRemoteEvent::Notification:
			switch (static_cast<eRemoteEvent>(args[2]))
			{
			case eRemoteEvent::NotificationMoneyBanked:
			case eRemoteEvent::NotificationMoneyRemoved:
			case eRemoteEvent::NotificationMoneyStolen:
				if (g.protections.script_events.fake_deposit)
				{
					g.reactions.fake_deposit.process(plyr);
					return true;
				}
				break;
			}
			break;
		case eRemoteEvent::ForceMission:
			if (g.protections.script_events.force_mission)
			{
				g.reactions.force_mission.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::GiveCollectible:
			if (g.protections.script_events.give_collectible)
			{
				g.reactions.give_collectible.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::GtaBanner:
			if (g.protections.script_events.gta_banner)
			{
				g.reactions.gta_banner.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::MCTeleport:
			if (g.protections.script_events.mc_teleport && args[3] <= 32)
			{
				g.reactions.mc_teleport.process(plyr);
				return true;
			}
			else if (args[3] > 32)
			{
				g.reactions.crash.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::PersonalVehicleDestroyed:
			if (g.protections.script_events.personal_vehicle_destroyed)
			{
				g.reactions.personal_vehicle_destroyed.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::RemoteOffradar:
			if (g.protections.script_events.remote_off_radar
			    && player->m_player_id != scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[self::id].BossGoon.Boss)
			{
				g.reactions.remote_off_radar.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::TSECommand:
			if (g.protections.script_events.rotate_cam && static_cast<eRemoteEvent>(args[2]) == eRemoteEvent::TSECommandRotateCam
			    && !gta_util::get_network()->m_is_activity_session)
			{
				g.reactions.rotate_cam.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::SendToCayoPerico:
			if (g.protections.script_events.send_to_location && args[3] == 0)
			{
				g.reactions.send_to_location.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::SendToCutscene:
			if (g.protections.script_events.send_to_cutscene
			    && player->m_player_id != scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[self::id].BossGoon.Boss)
			{
				g.reactions.send_to_cutscene.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::SendToLocation:
		{
			bool known_location = false;

			if (args[2] == 0 && args[3] == 0)
			{
				if (args[4] == 4 && args[5] == 0)
				{
					known_location = true;

					if (g.protections.script_events.send_to_location)
					{
						g.reactions.send_to_location.process(plyr);
						return true;
					}
				}
				else if ((args[4] == 3 || args[4] == 4) && args[5] == 1)
				{
					known_location = true;

					if (g.protections.script_events.send_to_location)
					{
						g.reactions.send_to_location.process(plyr);
						return true;
					}
				}
			}

			if (!known_location)
			{
				g.reactions.tse_freeze.process(plyr);
				return true;
			}
			break;
		}
		case eRemoteEvent::SoundSpam:
		{
			auto plyr = g_player_service->get_by_id(player->m_player_id);

			if (g.protections.script_events.sound_spam && (!plyr || plyr->m_invites_rate_limit.process()))
			{
				if (plyr && plyr->m_invites_rate_limit.exceeded_last_process())
					g.reactions.sound_spam.process(plyr);
				return true;
			}
			break;
		}
		case eRemoteEvent::Spectate:
			if (g.protections.script_events.spectate)
			{
				g.reactions.spectate_notification.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::Teleport:
			if (g.protections.script_events.force_teleport && !is_player_driver_of_local_vehicle(player->m_player_id))
			{
				g.reactions.force_teleport.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::TransactionError: g.reactions.transaction_error.process(plyr); return true;
		case eRemoteEvent::VehicleKick:
			if (g.protections.script_events.vehicle_kick)
			{
				g.reactions.vehicle_kick.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::NetworkBail:
			if (auto plyr = g_player_service->get_by_id(player->m_player_id))
				session::add_infraction(plyr, Infraction::TRIED_KICK_PLAYER);
			g.reactions.network_bail.process(plyr);
			return true;
		case eRemoteEvent::TeleportToWarehouse:
			if (g.protections.script_events.teleport_to_warehouse && !is_player_driver_of_local_vehicle(player->m_player_id))
			{
				g.reactions.teleport_to_warehouse.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::StartActivity:
		{
			eActivityType activity = static_cast<eActivityType>(args[2]);
			if (g.protections.script_events.start_activity)
			{
				if (activity == eActivityType::Survival || activity == eActivityType::Mission || activity == eActivityType::Deathmatch || activity == eActivityType::BaseJump || activity == eActivityType::Race)
				{
					g.reactions.tse_freeze.process(plyr);
					return true;
				}
				else if (activity == eActivityType::Darts)
				{
					g.reactions.start_activity.process(plyr);
					return true;
				}
				else if (activity == eActivityType::PilotSchool)
				{
					g.reactions.start_activity.process(plyr);
					return true;
				}
				else if (activity == eActivityType::ImpromptuDeathmatch)
				{
					g.reactions.start_activity.process(plyr);
					return true;
				}
				else if (activity == eActivityType::DefendSpecialCargo || activity == eActivityType::GunrunningDefend || activity == eActivityType::BikerDefend || args[2] == 238)
				{
					g.reactions.trigger_business_raid.process(plyr);
					return true;
				}
			}
			else if (activity == eActivityType::Tennis)
			{
				g.reactions.crash.process(plyr);
				return true;
			}

			if (g.protections.script_events.start_activity && !is_player_our_goon(player->m_player_id))
			{
				g.reactions.start_activity.process(plyr);
				return true;
			}

			break;
		}
		case eRemoteEvent::InteriorControl:
		{
			int interior = (int)args[2];
			if (interior < 0 || interior > 161)// the upper bound will change after an update
			{
				if (auto plyr = g_player_service->get_by_id(player->m_player_id))
					session::add_infraction(plyr, Infraction::TRIED_KICK_PLAYER);
				g.reactions.null_function_kick.process(plyr);
				return true;
			}
			break;
		}
		case eRemoteEvent::SMS:
			if (g.protections.script_events.send_sms)
			{
				if (g.session.kick_chat_spammers)
				{
					if (auto plyr = g_player_service->get_by_id(player->m_player_id))
					{
						((player_command*)command::get(RAGE_JOAAT("breakup")))->call(plyr, {});
					}
				}

				return true;
			}
			break;
		case eRemoteEvent::DestroyPersonalVehicle: g.reactions.destroy_personal_vehicle.process(plyr); return true;
		case eRemoteEvent::KickFromInterior:
			if (scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].SimpleInteriorData.Owner != plyr->id())
			{
				g.reactions.kick_from_interior.process(plyr);
				return true;
			}
			break;
		case eRemoteEvent::TriggerCEORaid:
		{
			if (auto script = gta_util::find_script_thread(RAGE_JOAAT("freemode")))
			{
				if (script->m_net_component && script->m_net_component->m_host && script->m_net_component->m_host->m_net_game_player != player)
				{
					g.reactions.trigger_business_raid.process(plyr);
				}
			}

			return true;
		}
		case eRemoteEvent::StartScriptProceed:
		{
			// TODO: Breaks stuff
			if (auto script = gta_util::find_script_thread(RAGE_JOAAT("freemode")))
			{
				if (script->m_net_component && script->m_net_component->m_host && script->m_net_component->m_host->m_net_game_player != player)
				{
					g.reactions.start_script.process(plyr);
					return true;
				}
			}
			break;
		}
		}

		// detect pasted menus setting args[1] to something other than PLAYER_ID()
		if (*(int*)&args[1] != player->m_player_id && player->m_player_id != -1)
		{
			LOG(INFO) << "Hash = " << (int)args[0];
			LOG(INFO) << "Sender = " << args[1];
			g.reactions.tse_sender_mismatch.process(plyr);
			return true;
		}

		if (g.debug.logs.script_event.logs
		    && (!g.debug.logs.script_event.filter_player || g.debug.logs.script_event.player_id == player->m_player_id))
		{
			std::string script_args = "{ ";
			for (std::size_t i = 0; i < scripted_game_event->m_args_size; i++)
			{
				if (i)
					script_args += ", ";

				script_args += std::to_string((int)args[i]);
			}
			script_args += " };";

			LOG(VERBOSE) << "Script Event:\n"
			             << "\tPlayer: " << player->get_name() << "\n"
			             << "\tArgs: " << script_args;
		}

		if (g.debug.logs.script_event.block_all)
			return true;

		return false;
	}
}
