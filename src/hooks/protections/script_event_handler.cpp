#include "hooking.hpp"
#include "gta_util.hpp"
#include "util/session.hpp"
#include "gta/net_game_event.hpp"
#include <network/CNetGamePlayer.hpp>

namespace big
{
	void format_string(std::string_view player_name, std::string_view protection_type, bool should_log, bool should_notify)
	{
		if (should_log)
			LOG(WARNING) << "BLOCKED_SCRIPT_EVENT From: " << player_name << " Event Type: " << protection_type;

		if (should_notify)
			g_notification_service->push_warning("Script Event Protection",
				std::format("From: {}\nEvent Type: {}", player_name.data(), protection_type.data())
			);
	}

	bool hooks::scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player)
	{
		const auto args = scripted_game_event->m_args;

		const auto hash = static_cast<eRemoteEvent>(args[0]);
		const auto player_name = player->get_name();

		const auto& notify = g.notifications.script_event_handler;

		switch (hash)
		{
		case eRemoteEvent::Bounty:
			if (g.protections.script_events.bounty)
			{
				format_string(player_name, "Bounty", notify.bounty.log, notify.bounty.notify);

				return true;
			}
			break;
		case eRemoteEvent::CeoBan:
			if (g.protections.script_events.ceo_ban)
			{
				format_string(player_name, "Ceo Ban", notify.ceo_ban.log, notify.ceo_ban.notify);

				return true;
			}
			break;
		case eRemoteEvent::CeoKick:
			if (g.protections.script_events.ceo_kick)
			{
				format_string(player_name, "Ceo Kick", notify.ceo_kick.log, notify.ceo_kick.notify);

				return true;
			}
			break;
		case eRemoteEvent::CeoMoney:
			if (g.protections.script_events.ceo_money)
			{
				format_string(player_name, "Ceo Money", notify.ceo_money.log, notify.ceo_money.notify);

				return true;
			}
			break;
		case eRemoteEvent::ClearWantedLevel:
			if (g.protections.script_events.clear_wanted_level)
			{
				format_string(player_name, "Clear Wanted Level", notify.clear_wanted_level.log, notify.clear_wanted_level.notify);

				return true;
			}
			break;
		case eRemoteEvent::Crash:
		case eRemoteEvent::Crash2:
			if (g.protections.script_events.crash)
			{
				format_string(player_name, "TSE Crash", notify.crash.log, notify.crash.notify);

				return true;
			}
			break;
		case eRemoteEvent::Notification:
			switch (static_cast<eRemoteEvent>(args[2]))
			{
			case eRemoteEvent::NotificationMoneyBanked:
			case eRemoteEvent::NotificationMoneyRemoved:
			case eRemoteEvent::NotificationMoneyStolen:
				if (g.protections.script_events.fake_deposit)
				{
					format_string(player_name, "Fake Deposit", notify.fake_deposit.log, notify.fake_deposit.notify);

					return true;
				}
				break;
			}
			break;
		case eRemoteEvent::ForceMission:
			if (g.protections.script_events.force_mission)
			{
				format_string(player_name, "Force Mission", notify.force_mission.log, notify.force_mission.notify);

				return true;
			}
			break;
		case eRemoteEvent::GiveCollectible:
			if (g.protections.script_events.switch_player_model)
			{
				if (args[2] == 8)
				{
					format_string(player_name, "Switch Player Model", notify.switch_player_model.log, notify.switch_player_model.notify);

					return true;
				}
			}
			break;
		case eRemoteEvent::GtaBanner:
			if (g.protections.script_events.gta_banner)
			{
				format_string(player_name, "GTA Banner", notify.gta_banner.log, notify.gta_banner.notify);

				return true;
			}
			break;
		case eRemoteEvent::MCTeleport:
			if (g.protections.script_events.mc_teleport && args[3] <= 32)
			{
				format_string(player_name, "Remote Teleport", notify.mc_teleport.log, notify.mc_teleport.notify);

				return true;
			}
			else if (g.protections.script_events.crash && args[3] > 32)
			{
				format_string(player_name, "TSE Crash", notify.crash.log, notify.crash.notify);

				return true;
			}
			break;
		case eRemoteEvent::PersonalVehicleDestroyed:
			if (g.protections.script_events.personal_vehicle_destroyed)
			{
				format_string(player_name, "Personal Vehicle Destroyed", notify.personal_vehicle_destroyed.log, notify.personal_vehicle_destroyed.notify);

				return true;
			}
			break;
		case eRemoteEvent::RemoteOffradar:
			if (g.protections.script_events.remote_off_radar)
			{
				format_string(player_name, "Off Radar", notify.remote_off_radar.log, notify.remote_off_radar.notify);

				return true;
			}
			break;
		case eRemoteEvent::TSECommand:
			if (g.protections.script_events.rotate_cam && static_cast<eRemoteEvent>(args[2]) == eRemoteEvent::TSECommandRotateCam)
			{
				format_string(player_name, "Rotate Cam", notify.rotate_cam.log, notify.rotate_cam.notify);

				return true;
			}
			break;
		case eRemoteEvent::SendToCayoPerico:
			if (g.protections.script_events.send_to_location)
			{
				format_string(player_name, "Send to Cayo Perico", notify.send_to_location.log, notify.send_to_location.notify);

				return true;
			}
			break;
		case eRemoteEvent::SendToCutscene:
			if (g.protections.script_events.send_to_cutscene)
			{
				format_string(player_name, "Send to Cutscene", notify.send_to_cutscene.log, notify.send_to_cutscene.notify);

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
						format_string(player_name, "Send to Beach", notify.send_to_location.log, notify.send_to_location.notify);

						return true;
					}
				}
				else if ((args[4] == 3 || args[4] == 4) && args[5] == 1)
				{
					known_location = true;

					if (g.protections.script_events.send_to_location)
					{
						format_string(player_name, "Send to Cayo Perico", notify.send_to_location.log, notify.send_to_location.notify);

						return true;
					}
				}
			}

			if (!known_location)
			{
				format_string(player_name, "TSE Freeze", notify.tse_freeze.log, notify.tse_freeze.notify);

				return true;
			}
			break;
		}
		case eRemoteEvent::SoundSpam:
			if (g.protections.script_events.sound_spam)
			{
				format_string(player_name, "Sound Spamn", notify.sound_spam.log, notify.sound_spam.notify);

				return true;
			}
			break;
		case eRemoteEvent::Spectate:
			if (g.protections.script_events.spectate)
			{
				format_string(player_name, "Spectate", notify.spectate.log, notify.spectate.notify);

				return true;
			}
			break;
		case eRemoteEvent::Teleport:
			if (g.protections.script_events.force_teleport)
			{
				format_string(player_name, "Apartment Invite", notify.force_teleport.log, notify.force_teleport.notify);

				return true;
			}
			break;
		case eRemoteEvent::TransactionError:
			if (g.protections.script_events.transaction_error)
			{
				format_string(player_name, "Transaction Error", notify.transaction_error.log, notify.transaction_error.notify);

				return true;
			}
			break;
		case eRemoteEvent::VehicleKick:
			if (g.protections.script_events.vehicle_kick)
			{
				format_string(player_name, "Vehicle Kick", notify.vehicle_kick.log, notify.vehicle_kick.notify);

				return true;
			}
			break;
		case eRemoteEvent::ForceMission2:
			if (g.protections.script_events.force_mission)
			{
				format_string(player_name, "Force Mission", notify.force_mission.log, notify.force_mission.notify);

				return true;
			}
			break;
		case eRemoteEvent::NetworkBail:
			if (g.protections.script_events.network_bail)
			{
				if (auto plyr = g_player_service->get_by_id(player->m_player_id))
					session::add_infraction(plyr, Infraction::TRIED_KICK_PLAYER);
				format_string(player_name, "Network Bail", notify.network_bail.log, notify.network_bail.notify);
				return true;
			}
			break;
		case eRemoteEvent::TeleportToWarehouse:
			if (g.protections.script_events.teleport_to_warehouse)
			{
				format_string(player_name, "Teleport To Warehouse", notify.teleport_to_warehouse.log, notify.teleport_to_warehouse.notify);

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
					format_string(player_name, "Softlock Game", notify.start_activity.log, notify.start_activity.notify);

					return true;
				}
				else if (activity == eActivityType::Darts)
				{
					format_string(player_name, "Send To Darts", notify.start_activity.log, notify.start_activity.notify);

					return true;
				}
				else if (activity == eActivityType::PilotSchool)
				{
					format_string(player_name, "Send To Flight School", notify.start_activity.log, notify.start_activity.notify);

					return true;
				}
				else if (activity == eActivityType::ImpromptuDeathmatch)
				{
					format_string(player_name, "Start Impromptu Deathmatch", notify.start_activity.log, notify.start_activity.notify);

					return true;
				}
				else if (activity == eActivityType::DefendSpecialCargo || activity == eActivityType::GunrunningDefend || activity == eActivityType::BikerDefend)
				{
					format_string(player_name, "Trigger Business Raid", notify.start_activity.log, notify.start_activity.notify);

					return true;
				}
				// there are MANY more
			}
			else if (g.protections.script_events.crash && activity == eActivityType::Tennis)
			{
				format_string(player_name, "TSE Crash (Start Tennis)", notify.crash.log, notify.crash.notify);

				return true;
			}
			break;
		}
		case eRemoteEvent::InteriorControl:
		{
			int interior = (int)args[2];
			if (interior < 0 || interior > 161) // the upper bound will change after an update
			{
				if (auto plyr = g_player_service->get_by_id(player->m_player_id))
					session::add_infraction(plyr, Infraction::TRIED_KICK_PLAYER);

				format_string(player_name, "Null Function Kick", notify.null_function_kick.log, notify.null_function_kick.notify);

				return true;
			}
			break;
		}
		case eRemoteEvent::SMS:
			if (g.protections.script_events.send_sms)
			{
				format_string(player_name, "Send SMS", notify.send_sms.log, notify.send_sms.notify);

				return true;
			}
			break;
		}

		// detect pasted menus setting args[1] to something other than PLAYER_ID()
		if (*(int*)&args[1] != player->m_player_id && player->m_player_id != -1)
		{
			LOG(INFO) << "Hash = " << (int)args[0];
			format_string(player_name, "TSE sender mismatch", notify.tse_sender_mismatch.log, notify.tse_sender_mismatch.notify);
			return true;
		}

		if (g.debug.logs.script_event.logs && (!g.debug.logs.script_event.filter_player || g.debug.logs.script_event.player_id == player->m_player_id))
		{
			std::string script_args = "{ ";
			for (std::size_t i = 0; i < scripted_game_event->m_args_size; i++)
			{
				if (i)
					script_args += ", ";

				script_args += std::to_string(args[i]);
			}
			script_args += " };";

			LOG(G3LOG_DEBUG) << "Script Event:\n"
				<< "\tPlayer: " << player->get_name() << "\n"
				<< "\tArgs: " << script_args;
		}

		return false;
	}
}
