#include "hooking.hpp"
#include "gta/enums.hpp"
#include "util/notify.hpp"

namespace big
{
	bool hooks::scripted_game_event(CScriptedGameEvent* scripted_game_event, CNetGamePlayer* player)
	{
		auto args = scripted_game_event->m_args;

		eRemoteEvent hash = (eRemoteEvent)args[0];

		char type[32] = "";


		switch (hash)
		{
		case eRemoteEvent::Bounty:
			if (g.protections.script_events.bounty)
				strcpy(type, "Bounty");

			break;
		case eRemoteEvent::CeoBan:
			if (g.protections.script_events.ceo_ban)
				strcpy(type, "Ceo Ban");

			break;
		case eRemoteEvent::CeoKick:
			if (g.protections.script_events.ceo_kick)
				strcpy(type, "Ceo Kick");

			break;
		case eRemoteEvent::CeoMoney:
			if (g.protections.script_events.ceo_money)
				strcpy(type, "Ceo Money");

			break;
		case eRemoteEvent::ClearWantedLevel:
			if (g.protections.script_events.clear_wanted_level)
				strcpy(type, "Clear Wanted Level");

			break;
		case eRemoteEvent::FakeDeposit:
			if (g.protections.script_events.fake_deposit)
				strcpy(type, "Deposit");

			break;
		case eRemoteEvent::ForceMission:
			if (g.protections.script_events.force_mission)
				strcpy(type, "Force Mission");

			break;
		case eRemoteEvent::GtaBanner:
			if (g.protections.script_events.gta_banner)
				strcpy(type, "GTA Banner");

			break;
		case eRemoteEvent::NetworkBail:
			if (g.protections.script_events.network_bail)
				strcpy(type, "Network Bail");

			break;
		case eRemoteEvent::PersonalVehicleDestroyed:
			if (g.protections.script_events.personal_vehicle_destroyed)
				strcpy(type, "Personal Vehicle Destroyed");

			break;
		case eRemoteEvent::RemoteOffradar:
			if (g.protections.script_events.remote_off_radar)
				strcpy(type, "Remote Off Radar");

			break;
		case eRemoteEvent::RotateCam:
			if (g.protections.script_events.rotate_cam)
				strcpy(type, "Rotate Cam");

			break;
		case eRemoteEvent::SendToCutscene:
			if (g.protections.script_events.send_to_cutscene)
				strcpy(type, "Send To Cutscene");

			break;
		case eRemoteEvent::SendToIsland:
			if (g.protections.script_events.send_to_island)
				strcpy(type, "Send To Island");

			break;
		case eRemoteEvent::SoundSpam:
			if (g.protections.script_events.sound_spam)
				strcpy(type, "Sound Spam");

			break;
		case eRemoteEvent::Spectate:
			if (g.protections.script_events.spectate)
				strcpy(type, "Specate");

			break;
		case eRemoteEvent::Teleport:
			if (g.protections.script_events.force_teleport)
				strcpy(type, "Force Teleport");

			break;
		case eRemoteEvent::TransactionError:
			if (g.protections.script_events.transaction_error)
				strcpy(type, "Transaction Error");

			break;
		case eRemoteEvent::VehicleKick:
			if (g.protections.script_events.vehicle_kick)
				strcpy(type, "Vehicle Kick");

			break;
		}

		if (strlen(type) != 0)
		{
			notify::above_map(
				fmt::format("~g~BLOCKED SCRIPT EVENT~s~\nFrom: <C>{}</C>\nEvent Type: ~b~{}", player->get_name(), type)
			);

			return true;
		}

		if (g.debug.script_event_logging)
		{
			LOG(INFO) << "== Begin of Script Event ==";
			LOG(INFO) << "Player: " << player->get_name();
			LOG(INFO) << "Hash/Arg #0: " << (int)hash;

			for (int i = 1; i < sizeof(args); i++)
				LOG(INFO) << "Arg #" << i << ": " << args[i];

			LOG(INFO) << "== End of Script Event ==";
		}

		return g_hooking->m_scripted_game_event_hook.get_original<decltype(&hooks::scripted_game_event)>()(scripted_game_event, player);
	}
}